//  **************************************************************************
//
//       Copyright (c) 1992-2006 Professonal Computer Technology Co., Ltd
//
//      All rights are reserved. Reproduction in whole or in parts is
//  prohibited without the prior written consent of the copyright owner.
//  --------------------------------------------------------------------------
//
//  Module: CommandSell.H
//
//  Purpose: Implementation of CommandSell.
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

//	------------------------------------
//			Type Definitions
//	------------------------------------


//	------------------------------------
//			Variables Definitions
//	------------------------------------
extern SYS_DATA sysdat;
extern SYS_MESSAGE msg;

#define SYSTYPE  	sysdat.system_type
#define SYSMODE 	sysdat.system_mode
#define SYSVDOSGL	sysdat.video_signal
#define MSGVDOSGL 	msg.video_signal
#define SYSWINLK	sysdat.channel_link
#define SYSWINATTR	sysdat.windows_attr
#define SYSCHATTR	sysdat.channel_attr
#define SYSMIXTYP	sysdat.video_mix_type


//	------------------------------------
//			Function Prototypes
//	------------------------------------


// ===========================================================================
//			Hardware-dependent ( Physical) primitives
// ===========================================================================
	extern U8 	PCT_GetFirstStr(char **tagStr, char **sourceStr);
	extern U16 	PCT_StrToCommCode(char *Srt);
	extern void PCT_SendACK(void);
	// ********** Command Shell **********
	extern void MoniWriteAsicByte(PCHAR szParam);
	extern void MoniReadAsicByte(PCHAR szParam);
	extern void MoniAudioMixing(PCHAR szParam);
	extern void MoniAudioGain(PCHAR szParam);
	extern void MoniAudioLive(PCHAR szParam);
	extern void MoniRegisterDump(void);
	extern void	MoniVideoMixWin(PCHAR szParam);
	extern void MoniVideoMixAttr(PCHAR szParam);
	extern void PCT_AudioActionForHS(void);
	extern void MoniHSComm(PCHAR szParam);
	extern bit PCT_CheckSystem(void);//Kane modified
	
	extern U8 PCT_RunCommShell(char *strptr);
	// ***********************************

// ===========================================================================
//			Hardware-independent ( Logical) primitives
// ===========================================================================

// ===========================================================================
// END of File
// ===========================================================================
