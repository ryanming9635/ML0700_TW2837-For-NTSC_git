//  **************************************************************************
//
//       Copyright (c) 1992-2006 Professonal Computer Technology Co., Ltd
//
//      All rights are reserved. Reproduction in whole or in parts is
//  prohibited without the prior written consent of the copyright owner.
//  --------------------------------------------------------------------------
//
//  Module: TW2835_Init.C
//
//  Purpose: Implementation of TW2835_Init.
//
//  Version: 0.01                                   2006/10/31 05:42�U��
//
//  Compiler: Keil 8051 C Compiler v7.2
//
//  Reference:
//
//
//
//  --------------------------------------------------------------------------
//  Modification:
//
//	R0.01 2006/10/31 05:42�U�� Phoenix Chuang
//	Reason:
//		1. Original.
//	Solution:
//	
//  **************************************************************************
// 	-----------------------------------
//			Header Files
//	----------------------------------- 
#include "Types.h"
#include "Timer.h"
#include "TW2835_Init.h"
#include "BusCtrl.h"
#include "CommandShell.h"
#include "TW28xx_Video.h"
#include "OSDAction.h"

#include "TW2835_Table.h"
#include "Main.h"


//	------------------------------------
//			Macro Definitions
//	------------------------------------ 


//	------------------------------------
//			Type Definitions
//	------------------------------------
sbit RSTn = P3 ^ 4;


//	------------------------------------
//			Variables Definitions
//	------------------------------------


//	------------------------------------
//			Function Prototypes
//	------------------------------------


// ===========================================================================
//                      Parallel function description
// ===========================================================================
//
//	TW2835 IC Reset
//
void PCT_InitialTW2835(void)
{
	PCT_TW2835ResetN();
	SYSTYPE = DEF_SYSTEM;

	// Waitting Color Lock
	EnUserTimer(USERTMID1,10);
	while(USERTMVAL1!=1) {
		if( (TW28_ReadByte(0, SENSORCHANNEL<<4)&0x0F) == 0x0F) {
			SYSTYPE = PCT_DetectVideoFormat(SENSORCHANNEL);
			break;
		}
		Wait_ms(10);
	}
	DisUserTimer(USERTMID1);
	
	PCT_TW2835_Initial();
	PCT_InitialOSD();
}

// ===========================================================================
//
//	TW2835 IC Reset
//
void PCT_TW2835ResetN(void)
{
	register U16 _delay; 
//Kane @HS 2007 0723 Ver3.4>>>>
#if 0
	// Initial RssetN for TW2835
	DELAY_FOR(5000);
	RSTn = 0;
	DELAY_FOR(10000);
	RSTn = 1;
	DELAY_FOR(5000);
	RSTn = 0;
	DELAY_FOR(10000);
	RSTn = 1;
	DELAY_FOR(5000);
#endif
	RSTn = 0;
	DELAY_FOR(100);////about 1.2ms
	RSTn = 1;
//Kane @HS 2007 0723 Ver3.4<<<<
}

// ===========================================================================
//
//	Video Initial Procedure
//
void PCT_TW2835_Initial(void)
{
	register U16 offset;
	
	offset = SYSTYPE * 256;
	TW28_WriteTable(0x00, 0x00, TW2835_Page0+offset, 192);
	TW28_WriteTable(0x01, 0x00, TW2835_Page1+offset, 160);

	TW28_WriteTable(0x01, 0x30, TW2835_Page1+offset+0x30, 32);

	TW28_WriteTable(0x01, 0xA0, TW2835_Page1+offset+0xA0, 16);
}

// ===========================================================================
//
//	Video Initial Procedure
//
void PCT_ChangeSystemType(U8 _sys)
{
	register U16 offset;
	
	offset = _sys * 256;
	TW28_WriteTable(0x00, 0x00, TW2835_Page0+offset+0x00, 64);

	TW28_WriteTable(0x01, 0x30, TW2835_Page1+offset+0x30, 32);

	TW28_WriteTable(0x01, 0x00, TW2835_Page1+offset+0x00, 1);
	TW28_WriteTable(0x01, 0xA7, TW2835_Page1+offset+0xA7, 3);
}

// ===========================================================================
//
//
//


// ===========================================================================
// END of File 
// ===========================================================================
