//  **************************************************************************
//
//       Copyright (c) 1992-2006 Professonal Computer Technology Co., Ltd
//
//      All rights are reserved. Reproduction in whole or in parts is
//  prohibited without the prior written consent of the copyright owner.
//  --------------------------------------------------------------------------
//
//  Module: OSDCtrl.H
//
//  Purpose: Implementation of OSD Control.
//
//  Version: 0.01                                   2007/5/7 09:04¤W¤È
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
//	R0.01 2007/5/7 09:05¤W¤È Phoenix Chuang
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

//	------------------------------------
//			Type Definitions
//	------------------------------------

//	------------------------------------
//			Variables Definitions
//	------------------------------------
	extern U8 graphattr;

	
//	------------------------------------
//			Function Prototypes
//	------------------------------------


// ===========================================================================
//			Hardware-dependent ( Physical) primitives
// ===========================================================================
	extern void PCT_ClearGraphAttr(void);
	extern void PCT_PreSetGraphAttr(U8 _attribute);
	extern void PCT_OSD16x16GraphX(U8 _posx, U16 _posy, U8 _indx);
	extern void PCT_ShowGraphString(U8 _path, U8 _addrx, U8 _addry, PCHAR _strptr);

	
// ===========================================================================
//			Hardware-independent ( Logical) primitives
// ===========================================================================
	
	
// ===========================================================================
// END of File
// ===========================================================================

