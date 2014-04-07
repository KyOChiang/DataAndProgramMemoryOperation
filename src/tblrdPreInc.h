/**
 * Author: Chiang Choon Yong
 * Email: yong931231@hotmail.com
 * Date: 07 - 04 - 2014
 * Project name: PIC18 simulator
 * Programme: Microelectronic with Embedded Technology
 * Institution: Tunku Abdul Rahman University College
 * Copyright: GPLv3
 */

#ifndef TBLDRPREINC_H
#define TBLDRPREINC_H

extern char FSR[];
extern unsigned char TABLE[];

#define WREG 0xFE8
#define BSR 0xFE0
#define STATUS 0xFD8
#define TBLPTRU 0xFF8
#define TBLPTRH 0xFF7
#define TBLPTRL 0xFF6
#define TABLAT 0xFF5

int tblrd_PreInc(Bytecode *code);

#endif // TBLDRPREINC_H