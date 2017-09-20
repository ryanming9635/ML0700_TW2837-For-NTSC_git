//  **************************************************************************
//
//       Copyright (c) 1992-2006 Professonal Computer Technology Co., Ltd
//
//      All rights are reserved. Reproduction in whole or in parts is
//  prohibited without the prior written consent of the copyright owner.
//  --------------------------------------------------------------------------
//
//  Module: TW28xx_Video.H
//
//  Purpose: Implementation of TW28xx Video.
//
//  Version: 0.01                                   2006/12/11 08:22¤U¤È
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
//	R0.01 2006/12/11 08:22¤U¤È Phoenix Chuang
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
#define WIN_LEFT	0
#define WIN_RIGHT	BIT2

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
// About Video Format
#define VIDEO_ADDR	0x70

#define VIDEO_PAL_BD	0x00
#define VIDEO_PAL_M		0x10
#define VIDEO_PAL_N		0x20
#define VIDEO_PAL_60	0x30
#define VIDEO_NTSC_M	0x40
#define VIDEO_NTSC_443	0x50
#define VIDEO_NTSC_N	0x60

// About Video Mixing 
#define VMIX_TYPE_N11	0x11	// NTSC
#define VMIX_TYPE_N21	0x21    // NTSC
#define VMIX_TYPE_N22	0x22    // NTSC
#define VMIX_TYPE_N31	0x31    // NTSC
#define VMIX_TYPE_N32	0x32    // NTSC
#define VMIX_TYPE_N33	0x33    // NTSC
#define VMIX_TYPE_N34	0x34    // NTSC
#define VMIX_TYPE_N41	0x41    // NTSC

#define VMIX_TYPE_P11	0x91	// PAL
#define VMIX_TYPE_P21	0xA1    // PAL
#define VMIX_TYPE_P22	0xA2    // PAL
#define VMIX_TYPE_P31	0xB1    // PAL
#define VMIX_TYPE_P32	0xB2    // PAL
#define VMIX_TYPE_P33	0xB3    // PAL
#define VMIX_TYPE_P34	0xB4    // PAL
#define VMIX_TYPE_P41	0xC1    // PAL

#define TYPE2_OFSET		11		// Setting Data offset for Type2 of X Channel Video Mixing 
#define TYPE3_OFSET		19		// Setting Data offset for Type3 of X Channel Video Mixing 
		
#define YTYPE_OFSET		8		// Setting Data offset for Type of Y Channel Video Mixing 
	
// About X Channel Video attribute
#define WIN_RECALL_EN	0x80
#define WIN_FREEZE		0x40
#define WIN_HMIRROR 	0x20
#define WIN_VMIRROR 	0x10
#define WIN_ENHANCE 	0x08
#define WIN_BLANK		0x04
#define WIN_BOUND		0x02
#define WIN_BLINK		0x01

//	------------------------------------
//			Function Prototypes
//	------------------------------------


// ===========================================================================
//			Hardware-dependent ( Physical) primitives
// ===========================================================================
	extern U8 	PCT_DetectVideoFormat(U8 _ch);
	extern void PCT_SetVideoFormat(U8 _dvc, U8 _ch, U8 _fmat);
	extern void PCT_SetChanelScale(U8 _ch, WRITE_REG_DATA *datptr); 
	extern void PCT_SetVideoHDelay(U8 _typ, PU8 _winch, PU8 _cattr);
	extern void PCT_SetXVideoMixing(U8 _typ, PU8 _winch); 
	extern void PCT_SetYVideoMixing(U8 _typ);
	extern void PCT_RecompenseYHdelay (PU8 _chmiro);//Kane @HS 2007 0808 Ver3.4
	extern void PCT_VideoLastModify(void);
	
	extern void PCT_WinAttrCtrl(U8 _wid, U8 _attrsel, U8 _setval);
	extern void PCT_WinAttrCtrlY(U8 _wid, U8 _attrsel, U8 _setval);
	extern void PCT_WinAttrClear(U8 _attrsel);
	extern void PCT_WinPOPupCtrl(U8 _wid);


// ===========================================================================
//			Hardware-independent ( Logical) primitives
// ===========================================================================
	
	
// ===========================================================================
// END of File
// ===========================================================================
