/**
 * Author: Chiang Choon Yong
 * Email: yong931231@hotmail.com
 * Date: 07 - 04 - 2014
 * Project name: PIC18 simulator
 * Programme: Microelectronic with Embedded Technology
 * Institution: Tunku Abdul Rahman University College
 * Copyright: GPLv3
 */

#include "unity.h"
#include "CException.h"
#include "ByteCode.h"
#include "tblrdPreInc.h"

void setUp(){}
void tearDown(){}

void test_tblrdPreInc_should_not_read_data_from_TABLE_if_table_ptr_is_invalid(){
	CEXCEPTION_T ERR;

	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = TBLRD_PREINC, .name = "tblrd_PreInc"},
					 .operand1 = -1,
					 .operand2 = -1,
					 .operand3 = -1,
					 .absoluteAddress = 0xD0
					};
					
	FSR[TABLAT] = 0x01;
	FSR[TBLPTRU] = 0x3A;
	FSR[TBLPTRH] = 0x10;
	FSR[TBLPTRL] = 0x05;
	TABLE[0x000006] = 0x95;

	Try{
		tblrd_PreInc(&code);
	} Catch(ERR){
		TEST_ASSERT_EQUAL(ERR_INVALID_TBL_PTR,ERR);
	}

	TEST_ASSERT_EQUAL(0xD0, code.absoluteAddress);
}

void test_tblrdPreInc_should_throw_invalid_if_operand1_is_non_empty(){
	CEXCEPTION_T ERR;

	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = TBLRD_PREINC, .name = "tblrd_PreInc"},
					 .operand1 = 0x01,
					 .operand2 = -1,
					 .operand3 = -1,
					 .absoluteAddress = 0xE0
					};
					
	FSR[TABLAT] = 0x01;
	FSR[TBLPTRU] = 0x00;
	FSR[TBLPTRH] = 0x10;
	FSR[TBLPTRL] = 0x05;
	TABLE[0x000006] = 0x95;

	Try{
		tblrd_PreInc(&code);
	} Catch(ERR){
		TEST_ASSERT_EQUAL(ERR_NON_EMPTY_OPERAND,ERR);
	}

	TEST_ASSERT_EQUAL(0xE0, code.absoluteAddress);
}

void test_tblrdPreInc_should_throw_invalid_if_operand2_is_non_empty(){
	CEXCEPTION_T ERR;

	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = TBLRD_PREINC, .name = "tblrd_PreInc"},
					 .operand1 = -1,
					 .operand2 = 0x01,
					 .operand3 = -1,
					 .absoluteAddress = 0xF1
					};
					
	FSR[TABLAT] = 0x01;
	FSR[TBLPTRU] = 0x00;
	FSR[TBLPTRH] = 0x10;
	FSR[TBLPTRL] = 0x05;
	TABLE[0x000006] = 0xF2;

	Try{
		tblrd_PreInc(&code);
	} Catch(ERR){
		TEST_ASSERT_EQUAL(ERR_NON_EMPTY_OPERAND,ERR);
	}

	TEST_ASSERT_EQUAL(0xF1, code.absoluteAddress);
}

void test_tblrdPreInc_should_throw_invalid_if_operand3_is_non_empty(){
	CEXCEPTION_T ERR;

	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = TBLRD_PREINC, .name = "tblrd_PreInc"},
					 .operand1 = -1,
					 .operand2 = 0x01,
					 .operand3 = BANKED,
					 .absoluteAddress = 0xF1
					};
					
	FSR[TABLAT] = 0xA1;
	FSR[TBLPTRU] = 0x00;
	FSR[TBLPTRH] = 0x10;
	FSR[TBLPTRL] = 0x05;
	TABLE[0x000006] = 0xF2;

	Try{
		tblrd_PreInc(&code);
	} Catch(ERR){
		TEST_ASSERT_EQUAL(ERR_NON_EMPTY_OPERAND,ERR);
	}

	TEST_ASSERT_EQUAL(0xF1, code.absoluteAddress);
}


void test_tblrdPreInc_should_read_data_from_TABLE_addr_0x000006_and_store_in_TABLAT_after_tblptr_increment_by_1(){
	CEXCEPTION_T operandERR;

	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = TBLRD_PREINC, .name = "tblrd_PreInc"},
					 .operand1 = -1,
					 .operand2 = -1,
					 .operand3 = -1,
					 .absoluteAddress = 0xA0
					};
					
	FSR[TABLAT] = 0x01;
	FSR[TBLPTRU] = 0x00;
	FSR[TBLPTRH] = 0x00;
	FSR[TBLPTRL] = 0x05;
	TABLE[0x000006] = 0x95;

	Try{
		tblrd_PreInc(&code);
	} Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_NON_EMPTY_OPERAND,operandERR);
	}

	TEST_ASSERT_EQUAL(0xA1, code.absoluteAddress);
	TEST_ASSERT_EQUAL_HEX8(0x95, FSR[TABLAT]);
	TEST_ASSERT_EQUAL_HEX8(0x00, FSR[TBLPTRU]);
	TEST_ASSERT_EQUAL_HEX8(0x00, FSR[TBLPTRH]);
	TEST_ASSERT_EQUAL_HEX8(0x06, FSR[TBLPTRL]);
}

void test_tblrdPreInc_should_read_data_from_TABLE_addr_0x200000_and_store_in_TABLAT_without_increment_on_tblptr(){
	CEXCEPTION_T operandERR;

	//Test fixture
	Bytecode code = {.instruction = {.mnemonic = TBLRD_PREINC, .name = "tblrd_PreInc"},
					 .operand1 = -1,
					 .operand2 = -1,
					 .operand3 = -1,
					 .absoluteAddress = 0xAA
					};
					
	FSR[TABLAT] = 0xCB;
	FSR[TBLPTRU] = 0x20;
	FSR[TBLPTRH] = 0x00;
	FSR[TBLPTRL] = 0x00;
	TABLE[0x200000] = 0xAC;

	Try{
		tblrd_PreInc(&code);
	} Catch(operandERR){
		TEST_ASSERT_EQUAL(ERR_NON_EMPTY_OPERAND,operandERR);
	}

	TEST_ASSERT_EQUAL(0xAB, code.absoluteAddress);
	TEST_ASSERT_EQUAL_HEX8(0xAC, FSR[TABLAT]);
	TEST_ASSERT_EQUAL_HEX8(0x20, FSR[TBLPTRU]);
	TEST_ASSERT_EQUAL_HEX8(0x00, FSR[TBLPTRH]);
	TEST_ASSERT_EQUAL_HEX8(0x00, FSR[TBLPTRL]);
}
