//  **************************************************************************
//
//       Copyright (c) 1992-2006 Professonal Computer Technology Co., Ltd
//
//      All rights are reserved. Reproduction in whole or in parts is
//  prohibited without the prior written consent of the copyright owner.
//  --------------------------------------------------------------------------
//
//  Module: Types.H
//
//  Purpose: Implementation of Types.
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
#include <String.h>
#include <stdio.h>
#include <stdlib.h>
#include <INTRINS.h>
#include "SST89x5xxRD2.H"

#define TW2837 			ON 
#define TW2837TABLE 		ON
#define TW2837_DEBUG	OFF

//	------------------------------------
//		Macro Definitions
//	------------------------------------ 

//	------------------------------------ 
#define GETHBYTE(x)	(unsigned char)(x>>8)&0xFF
#define GETLBYTE(x)	(unsigned char)x&0xFF

extern unsigned short _delay;

#define	DELAY_FOR(x) for(_delay=0; _delay<(x); _delay++)

//
//	functions
//
#define	BIT0		(0x0001)
#define	BIT1		(0x0002)
#define	BIT2		(0x0004)
#define	BIT3		(0x0008)
#define	BIT4		(0x0010)
#define	BIT5		(0x0020)
#define	BIT6		(0x0040)
#define	BIT7		(0x0080)
#define	BIT8		(0x0100)
#define	BIT9		(0x0200)
#define	BIT10		(0x0400)
#define	BIT11		(0x0800)
#define	BIT12		(0x1000)
#define	BIT13		(0x2000)
#define	BIT14		(0x4000)
#define	BIT15		(0x8000)

//
#define MASTER 		0
#define DVC_PG0  	0
#define DVC_PG1  	1
#define DVC_PG2  	2
#define VDO_NTSC 	0

#define NTSC 		0
#define PAL   		1
#define NONE_SYSTEM 2

#if 1
#define DEF_SYSTEM	NTSC
#else
#define DEF_SYSTEM	PAL///For Holger 
#endif

//
#define	SetBit(x,y) 		((x) |= (y))
#define	ClearBit(x,y) 		((x) &= ~(y))
#if 1 //def TW2835_FUNC_DEFINE  //Pinchi 20150324 add
#define	_ifBitSet(x,y)  	if(((x)&(y)) == (y))
#define	_ifBitClear(x,y) 	if(((x)&(y)) == 0)
#else
#define	ifBitSet(x,y) 		if(((x)&(y)) == (y))
#define	ifBitClear(x,y) 	if(((x)&(y)) == 0)
#endif
#define FALSE   	0
#define TRUE 		1

#define I2C_FAST
//	#define TW28_I2CBUS
#ifdef TW28_I2CBUS
	#define TW2835_DVCADDR	0xFC
#endif

//	
//	terminals
//	

//	------------------------------------
//			Type Definitions
//	------------------------------------
	#define true 	1
	#define false   0
	#define ON  	1
	#define OFF 	0
	
	typedef char* PCHAR;
	typedef char** PPCHAR;
	typedef unsigned char BYTE;
	typedef unsigned char U8;
	typedef unsigned char* PU8;
	typedef unsigned short U16;
	typedef unsigned short* PU16;
	typedef unsigned long U32;
	typedef unsigned long* PU32;
	
	typedef struct _RW_REG_DATA {
		U16	addr;
		U8	mask;
		U8	offset;
	}RW_REG_DATA, *PRW_REG_DATA;
	
	typedef struct _WRITE_REG_DATA {
		U16	addr;
		U8	dat;
	}WRITE_REG_DATA, *PWRITE_REG_DATA;
	
	typedef struct _SYS_DATA {
		U8 system_type;		// PAL or NTSC
		U8 system_mode;		// System J or S Mode
		U8 video_signal;	
		U8 video_mix_type;	// Window Mix
		U8 channel_link[4];
		U8 link_type;
		U8 windows_attr[4];
		U8 channel_attr[4];
	}SYS_DATA, *PSYS_DATA;

	#define TIMER_NUM	3
	typedef struct _SYS_MESSAGE {
		U8 video_signal;
		U8 video_mix_type;
		U8 osd_falsh;
		U8 osd_onoff;
		U8 sysmsec;
		U8 user_timer[TIMER_NUM];
	}SYS_MESSAGE, *PSYS_MESSAGE;

//	------------------------------------
//			Variables Definitions
//	------------------------------------


//	------------------------------------
//			Function Prototypes
//	------------------------------------


// ===========================================================================
//			Hardware-dependent ( Physical) primitives
// ===========================================================================



// ===========================================================================
//			Hardware-independent ( Logical) primitives
// ===========================================================================
	
	
// ===========================================================================
// END of File
// ===========================================================================
