//  **************************************************************************
//
//       Copyright (c) 1992-2006 Professonal Computer Technology Co., Ltd
//
//      All rights are reserved. Reproduction in whole or in parts is
//  prohibited without the prior written consent of the copyright owner.
//  --------------------------------------------------------------------------
//
//  Module: OSDAction.H
//
//  Purpose: Implementation of OSD Action.
//
//  Version: 0.01                                   2006/12/25 09:43¤W¤È
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
//	R0.01 2006/12/25 09:43¤W¤È Phoenix Chuang
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
#define JMODEOSD	camstr[5]
#define SEQMODEOSD	camstr[6]

#define SMODE 		0
#define JMODE 		1
#define SEQMODE 	2

//	
//	terminals
//	

//	------------------------------------
//			Type Definitions
//	------------------------------------

//	------------------------------------
//			Variables Definitions
//	------------------------------------
	
//	------------------------------------
//			Function Prototypes
//	------------------------------------

// ===========================================================================
//			Hardware-dependent ( Physical) primitives
// ===========================================================================
	extern void PCT_InitialOSD(void);
	extern void PCT_OSD_ActionPthX(PU8 _attr);
	extern void PCT_PreDrawOSD(void);
	extern void PCT_EnfalshVLoss(void);
	extern void PCT_GetVideoSignalStatus(void);
	#ifdef HS
	#else
	extern void PCT_ShowVLoss(void);
	#endif
	extern void PCT_ShowIndicateIcon(PU8 _attr);
	#ifdef UTC
	#else
	extern void PCT_ShowSpeakIcon(PU8 _attr);
	#endif
	extern void PCT_ShowMirrorIcon(PU8 _attr);
	extern void PCT_ShowModeIcon(void);
	extern void PCT_OSDActionForHS(void);
	extern void MoniHSCommSJmode(PCHAR szParam);
	
// ===========================================================================
//			Hardware-independent ( Logical) primitives
// ===========================================================================
	
	extern U8 VlossCount;
//	extern void RS_tx(BYTE tx_buf);
//	extern bit VlossState;
// ===========================================================================
// END of File
// ===========================================================================
