/**
 * Author: Chiang Choon Yong
 * Email: yong931231@hotmail.com
 * Date: 07 - 04 - 2014
 * Project name: PIC18 simulator
 * Programme: Microelectronic with Embedded Technology
 * Institution: Tunku Abdul Rahman University College
 * Copyright: GPLv3
 */
 
#include <stdio.h>
#include "CException.h"
#include "ByteCode.h"
#include "tblrdPreInc.h"

char FSR[0x1000];
unsigned char TABLE[0x200000];

/*
 *	tblrd+* = Table read after increment
 */
int tblrd_PreInc(Bytecode *code){
	int tablePointer = 0;
	int TBLPTRUp, TBLPTRHi, TBLPTRLo;

	if(code->operand1 != -1 || code->operand2 != -1 || code->operand3 != -1){
		Throw(ERR_NON_EMPTY_OPERAND);
	}

	TBLPTRUp = (FSR[TBLPTRU]<<16);
	TBLPTRHi = (FSR[TBLPTRH]<<8);
	TBLPTRLo = FSR[TBLPTRL];

	tablePointer = TBLPTRUp + TBLPTRHi + TBLPTRLo;

	if(tablePointer <= 0x00 || tablePointer >= 0x200000){
		Throw(ERR_INVALID_TBL_PTR);
	}

	if(tablePointer == 200000){
		tablePointer = tablePointer;
	}
	else{
	tablePointer++;
	}
	
	FSR[TABLAT] = TABLE[tablePointer];

	FSR[TBLPTRU] = ((tablePointer & 0xFF0000)>>16);
	FSR[TBLPTRH] = ((tablePointer & 0x00FF00)>>8);
	FSR[TBLPTRL] = (tablePointer & 0x0000FF);

	return (code->absoluteAddress = code->absoluteAddress+1);
}