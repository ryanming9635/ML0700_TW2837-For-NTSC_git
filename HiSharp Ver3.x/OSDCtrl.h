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
//  Version: 0.01                                   2006/12/13 05:12¤U¤È
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
//	R0.01 2006/12/13 05:12¤U¤È Phoenix Chuang
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
#define	PTH_X	BIT0
#define	PTH_Y	BIT1

#define BOX_OFFSET_X	8
#define BOX_OFFSET_Y	8

#define YFONT_OFFSET_X	4
#define YFONT_OFFSET_Y	4

//	------------------------------------
//			Type Definitions
//	------------------------------------
	enum ColorIndex{
		OSD_COL_BLK=0,	
		OSD_COL_RED,			
		OSD_COL_GRN,			
		OSD_COL_BLU,			
		OSD_COL_100WHT,		
		OSD_COL_75WHT,		
		OSD_COL_50WHT,		
		OSD_COL_25WHT,		
		OSD_COL_ORNG,		
		OSD_COL_CYN,			
		OSD_COL_MGN,		
		OSD_COL_OCN,			
		OSD_COL_YLW,
		OSD_COL_RED255,			
		OSD_BLINK = 0x40,
		OSD_MIX = 0x80,
		OSD_COL_CLR = 0xFF
	};			


#define FORE_COLOR
#define BACK_COLOR OSD_COL_CLR

	enum defOSDPage{
		WRPHX_PAGE0=0x00,
		WRPHX_PAGE1=0x01,
		WRPHX_PAGE2=0x02,
		WRPHX_PAGE3=0x03,
		WRPHX_PAGE4=0x04,
		WRPHX_PAGE5=0x05,
		WRPHY_PAGE0=0x08
	};		
		

#define DISOSD_PHX	BIT3	
#define DISOSD_PHY	BIT1

//	------------------------------------
//			Variables Definitions
//	------------------------------------
	extern data U8 foreColor;
	extern data U8 backColor;


	
//	------------------------------------
//			Function Prototypes
//	------------------------------------


// ===========================================================================
//			Hardware-dependent ( Physical) primitives
// ===========================================================================
	extern void PCT_PreSetForegroundColor(U8 _color);
	extern void PCT_PreSetBackgroundColor(U8 _color);
	extern void PCT_SetOSDColor(U8 _pth, U8 _col_num, U8 _y, U8 _cb, U8 _cr);
	extern void PCT_InitOSDColor(void);

	extern void PCT_SetOSDDrawPage(U8 _page);
	extern void PCT_EnShowOSDPage(U8 _page);
	extern void PCT_DisShowOSDPage(U8 _bit);

	extern void PCT_WriteOSDFntX(U8 _posx, U16 _posy, signed char _len, PU8 _indx);
	extern void PCT_FullColorOnOSD(U8 _posx, U16 _posy, U8 _wide, U16 _high);
	extern void PCT_ClearWordsPathX(U8 _posx, U16 _posy, U8 _len);
	extern void PCT_ClearOSDPageX(U8 _page);
	extern void PCT_WriteOSDFntY(U8 _posx, U16 _posy, U8 _len, PU8 _indx);
	extern void PCT_ShowOSDString(U8 _path, U8 _addrx, U8 _addry, PCHAR _strptr);
	
// ===========================================================================
//			Hardware-independent ( Logical) primitives
// ===========================================================================
	
	
// ===========================================================================
// END of File
// ===========================================================================

