//  **************************************************************************
//
//       Copyright (c) 1992-2006 Professonal Computer Technology Co., Ltd
//
//      All rights are reserved. Reproduction in whole or in parts is
//  prohibited without the prior written consent of the copyright owner.
//  --------------------------------------------------------------------------
//
//  Module: Interrupt.H
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
//	R0.01 2007/4/27 04:28¤U¤È Phoenix Chuang
//	Reason:
//		1. Original.
//	Solution:
//	
//  **************************************************************************
// 	-----------------------------------
//			Header Files
//	----------------------------------- 


//	------------------------------------
//			Macro Definitions
//	------------------------------------ 
//
//	functions
//

//	
//	terminals
//	
// 16 Bits Timer High-Order Byte          
// 16 Bits Timer Low-Order Byte           
// XTAL/12/(65536-47104(T0HT0L)) 100Hz

#ifdef XTAL
	#define TIME0H 	0xB8	
	#define TIME0L 	0x00	
#endif

#ifdef XTAL40
//	#define TIME0H	(65536-(40000000/12/100))>>8	
//	#define TIME0L  (65536-(40000000/12/100))& 0xFF
	#define TIME0H 	0x7D
	#define TIME0L 	0xCB
#endif
                		

//	------------------------------------
//			Type Definitions
//	------------------------------------


//	------------------------------------
//			Variables Definitions
//	------------------------------------
#define USERTMADDR	user_timer
#define USERTMVAL0	user_timer[0]
#define USERTMVAL1	user_timer[1]
#define USERTMVAL2	user_timer[2]

#define TIMER_NUM		3
#define USERTMID0		0
#define USERTMID1		1
#define DELAY_TIMEER	2

extern data user_timer[TIMER_NUM];

	
//	------------------------------------
//			Function Prototypes
//	------------------------------------

// Enable & Setup User Timer0-2 
#define EnUserTimer(_id, _cntval) 	USERTMADDR[_id]=_cntval
#define DisUserTimer(_id) 			USERTMADDR[_id]=0

// ===========================================================================
//			Hardware-dependent ( Physical) primitives
// ===========================================================================
	extern void InitialTimer0(void);
	
	
// ===========================================================================
//			Hardware-independent ( Logical) primitives
// ===========================================================================
	
	
// ===========================================================================
// END of File
// ===========================================================================
