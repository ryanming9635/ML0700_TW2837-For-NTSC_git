//  **************************************************************************
//
//       Copyright (c) 1992-2006 Professonal Computer Technology Co., Ltd
//
//      All rights are reserved. Reproduction in whole or in parts is
//  prohibited without the prior written consent of the copyright owner.
//  --------------------------------------------------------------------------
//
//  Module: Interrupt.C
//
//  Purpose: Implementation of Soft Timer.
//
//  Version: 0.01                                   2007/4/27 04:27¤U¤È
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
//	R0.01 2007/4/27 04:27¤U¤È Phoenix Chuang
//	Reason:
//		1. Original.
//	Solution:
//	
//  **************************************************************************
// 	-----------------------------------
//			Header Files
//	----------------------------------- 
#include "Types.h"
#include "UART.h"
#include "Timer.h"


//	------------------------------------
//			Macro Definitions
//	------------------------------------ 

//	------------------------------------
//			Type Definitions
//	------------------------------------

//	------------------------------------
//			Variables Definitions
//	------------------------------------
data user_timer[TIMER_NUM];


//	------------------------------------
//			Function Prototypes
//	------------------------------------

// ===========================================================================
//                      Parallel function description
// ===========================================================================
// ===========================================================================
//
//		Interrupt Initial
//
void InitialTimer0(void){
	U8 i;
	
	PT0=1;
	ET0=1;
	TH0 = TIME0H;	// SET TIMER0 TH0
	TL0 = TIME0L;	// SET TIMER0 TL0
	TR0 = 1;		// SET ON TIMER0

	for(i=0; i<TIMER_NUM; i++)
		DisUserTimer(i);
}

// ===========================================================================
//
//		Timer/Counter 0 Interrupt
//
void Timer0_interrupt(void) interrupt 1 using 1
{
	EA = OFF;		// Disable All Interrupt
	TH0 = TIME0H;	// SET TIMER0 TH0
	TL0 = TIME0L;	// SET TIMER0 TL0
	TF0 = OFF;

	if(USERTMVAL0>1) USERTMVAL0--;
	if(USERTMVAL1>1) USERTMVAL1--;
	if(USERTMVAL2>1) USERTMVAL2--;

	EA = ON;		// Enable All Interrupt
}

// ===========================================================================
//
//		
//


// ===========================================================================
// END of File 
// ===========================================================================
