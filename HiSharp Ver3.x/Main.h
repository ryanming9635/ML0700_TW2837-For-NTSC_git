//  **************************************************************************
//
//       Copyright (c) 1992-2006 Professonal Computer Technology Co., Ltd
//
//      All rights are reserved. Reproduction in whole or in parts is
//  prohibited without the prior written consent of the copyright owner.
//  --------------------------------------------------------------------------
//
//  Module: Main.H
//
//  Purpose: Implementation of Main.
//
//  Version: 0.01                                   2006/10/22 09:26¤U¤È
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
//	R0.01 2006/10/22 10:39¤U¤È Phoenix Chuang
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
#define TW8816_MODEL_MEGAWIN 	0  //Pinchi 20150323 add for MCU type of TW2835
#define TW8806_MODEL_WINBOND 	1  //Pinchi 20150323 add for MCU type of TW2835

#define HS   ///disable show vloss funtion  //ryan@20180109
#define UTC 

#define TW2835_MCU 				TW8816_MODEL_MEGAWIN  //Pinchi 20150323 add for MCU type of TW2835
//#define TW2835_MCU 				TW8806_MODEL_WINBOND  //Pinchi 20150323 add for MCU type of TW2835

#ifdef HS
#else
#define AWT_NO_SIGNAL_MSG  //Pinchi 20150323 add for to display "NO VIDEO SIGNAL" by AWT request of 20150302
#endif

#define TW2835_FUNC_DEFINE  //Pinchi 20150324 modify define name to avoid un-active
#define AWT_DRAW_T_ICON  //Pinchi 20150415 add to draw T icon when CAM C trigger


#if (TW2835_MCU == TW8816_MODEL_MEGAWIN)  //Pinchi 20150323 add
#undef XTAL40
#endif


//	------------------------------------
//			Type Definitions
//	------------------------------------
	#define COMM_MAX_BUF 40
	#define TWCMD	1
	typedef struct _COMMAND_BUFFER {
		BYTE commBuf[COMM_MAX_BUF];
		BYTE ReadPtr;
		BYTE WritePtr;
		BYTE commFlage;
//		char *commStr;
//		char *paramStr;
	} COMMAND_BUFFER,* PCOMMAND_BUFFER;

//	------------------------------------
//			Variables Definitions
//	------------------------------------
	extern U16 _delay;

	extern COMMAND_BUFFER RScommand;
	extern bit VlossFlag;
	
//	------------------------------------
//			Function Prototypes
//	------------------------------------


// ===========================================================================
//			Hardware-dependent ( Physical) primitives
// ===========================================================================
	extern void ResetCommSell (void);
	extern void InitialCommShell (void);
	extern void chkStartCommShell (char *ptr);
	extern void CommandShell (void);
	extern void NewLine (void);
	extern void PutsP (BYTE *);

	extern void InitialMPU (void);
	extern void PCT_SetChanelScale (U8 _ch, WRITE_REG_DATA *datptr);
	extern void PCT_FlashOSDCtrl(U8 _on);
	extern void Wait_ms(U16 Tms);
	
	
// ===========================================================================
//			Hardware-independent ( Logical) primitives
// ===========================================================================
	
	
// ===========================================================================
// END of File
// ===========================================================================
