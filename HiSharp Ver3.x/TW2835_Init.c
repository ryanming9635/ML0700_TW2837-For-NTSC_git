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
//  Version: 0.01                                   2006/10/31 05:42¤U¤È
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
//	R0.01 2006/10/31 05:42¤U¤È Phoenix Chuang
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

BYTE TW2837IDCheck=FALSE;

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

	PCT_TW2837IDCheck();

	while(USERTMVAL1!=1) {
	
		if(TW2837IDCheck==TRUE)
			{
			Wait_ms(10);

			if( (TW28_ReadByte(0, SENSORCHANNEL<<4)&0xC0) == 0x40) {
			SYSTYPE = PCT_DetectVideoFormat(SENSORCHANNEL);
			break;
			}
		
			}
		else
			{
				if( (TW28_ReadByte(0, SENSORCHANNEL<<4)&0x0F) == 0x0F) {
				SYSTYPE = PCT_DetectVideoFormat(SENSORCHANNEL);
				break;
				}

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
//	TW2837 ID check
//
// ===========================================================================

void PCT_TW2837IDCheck(void)
{
	if( (TW28_ReadByte(0, 0xFE)&0x30) == 0x30) 
		TW2837IDCheck=TRUE;
	else 
		TW2837IDCheck=FALSE;
}

// ===========================================================================
//
//	Video Initial Procedure
//
void PCT_TW2835_Initial(void)
{
	register U16 offset;
	
	offset = SYSTYPE * 256;	
if(TW2837IDCheck==TRUE)
{

	TW28_WriteTable(0x00, 0x00, TW2837_Page0+offset, ((16*5)+8));

	TW28_WriteTable(0x00, 0x60, (TW2837_Page0+offset+0x60), (16));
	TW28_WriteTable(0x00, 0x70, (TW2837_Page0+offset+0x70), (4));
	
	TW28_WriteTable(0x00, 0x80, (TW2837_Page0+offset+0x80), (16*5));

	TW28_WriteTable(0x01, 0x00, TW2837_Page1+offset, 160);

	TW28_WriteTable(0x01, 0x30, TW2837_Page1+offset+0x30, 32);
	
	TW28_WriteTable(0x01, 0xA0, TW2837_Page1+offset+0xA0, 16);


	TW28_WriteTable(0x02, 0x10, TW2837_Page2, (16*3));
	TW28_WriteTable(0x02, 0x50, TW2837_Page2+0x30, (16*1));
	TW28_WriteTable(0x02, 0x60, TW2837_Page2+0x40, (16*4));

	if(SYSTYPE == VDO_NTSC){
		TW28_WriteTable(DVC_PG1,0x30,tbl_ntsc_pg1_pic_qd,16);		//... normal quad
		TW28_WriteTable(DVC_PG1,0x40,tbl_ntsc_pg1_pic_9_rb,16);
		TW28_WriteTable(DVC_PG1,0xa0,tbl_ntsc_pg1_enc,16);	
		TW28_WriteByte(DVC_PG1,0x00,0x00);
	}
	else{
		TW28_WriteTable(DVC_PG1,0x30,tbl_pal_pg1_pic_qd,16);			//... normal quad
		TW28_WriteTable(DVC_PG1,0x30,tbl_pal_pg1_pic_9_lt,16);		//... non-realtime
		TW28_WriteTable(DVC_PG1,0x40,tbl_pal_pg1_pic_9_rb,16);
		TW28_WriteTable(DVC_PG1,0xa0,tbl_pal_pg1_enc,16);	
		TW28_WriteByte(DVC_PG1,0x00,0x80);
	}

}
else
{
		TW28_WriteTable(0x00, 0x00, TW2835_Page0+offset, 192);
		TW28_WriteTable(0x01, 0x00, TW2835_Page1+offset, 160);
	
		TW28_WriteTable(0x01, 0x30, TW2835_Page1+offset+0x30, 32);
	
		TW28_WriteTable(0x01, 0xA0, TW2835_Page1+offset+0xA0, 16);

}



}

// ===========================================================================
//
//	Video Initial Procedure
//
void PCT_ChangeSystemType(U8 _sys)
{
	register U16 offset;
	
	offset = _sys * 256;

	if(TW2837IDCheck==TRUE)
	{	
		TW28_WriteTable(0x00, 0x00, TW2837_Page0+offset+0x00, 64);

		TW28_WriteTable(0x01, 0x30, TW2837_Page1+offset+0x30, 32);

		TW28_WriteTable(0x01, 0x00, TW2837_Page1+offset+0x00, 1);
		TW28_WriteTable(0x01, 0xA7, TW2837_Page1+offset+0xA7, 3);
	}
	else
	{
		TW28_WriteTable(0x00, 0x00, TW2835_Page0+offset+0x00, 64);
		
			TW28_WriteTable(0x01, 0x30, TW2835_Page1+offset+0x30, 32);
		
			TW28_WriteTable(0x01, 0x00, TW2835_Page1+offset+0x00, 1);
			TW28_WriteTable(0x01, 0xA7, TW2835_Page1+offset+0xA7, 3);

	}

}

// ===========================================================================
//
//
//


// ===========================================================================
// END of File 
// ===========================================================================
