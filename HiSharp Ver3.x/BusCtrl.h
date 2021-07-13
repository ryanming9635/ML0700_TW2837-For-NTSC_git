//  **************************************************************************
//
//       Copyright (c) 1992-2006 Professonal Computer Technology Co., Ltd
//
//      All rights are reserved. Reproduction in whole or in parts is
//  prohibited without the prior written consent of the copyright owner.
//  --------------------------------------------------------------------------
//
//  Module: PRTCL.H
//
//  Purpose: Implementation of PRTCL.
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
//
//	Prtcl functions
//

//	
//	Prtcl terminals
//	

//	------------------------------------
//			Type Definitions
//	------------------------------------

//	------------------------------------
//			Variables Definitions
//	------------------------------------
#define	MCTRL		P1
#define	MDATA		P0

sbit	HSPB	=	P1 ^ 0;
sbit	HWRB	=	P1 ^ 1;
sbit	HRDB	=	P1 ^ 2;
sbit	HALE	=	P1 ^ 3;

sbit	HCSB0	=	P3 ^ 6;
sbit	HCSB1	=	P3 ^ 7;


//	------------------------------------
//			Function Prototypes
//	------------------------------------

// ===========================================================================
//			Hardware-dependent ( Physical) primitives
// ===========================================================================
	extern void PCT_WriteAsicByte(U8 _dvc, U8 _pg, U8 _addr, U8 _wdat);
	extern void PCT_WriteAsicTable(U8 _dvc, U8 _pg, U8 _addr, U8 *_tbl_ptr, U8 _tbl_cnt);
	extern U8	PCT_ReadAsicByte(U8 _dvc, U8 _pg, U8 _addr);
	extern void PCT_WriteSTable(U8 _dvc, WRITE_REG_DATA *_tbl_ptr);
	extern void PTC_SwitchToI2CMode (void);
void PCT_PageChange(U8 _pg);
void	SetAsicFlgType(U8 _dvc, U8 _pg, U8 _addr, U8 _flg, U8 _data);


// ===========================================================================
//			Hardware-independent ( Logical) primitives
// ===========================================================================
#ifndef TW28_I2CBUS
	#define TW28_WriteByte(b, c, d)			PCT_WriteAsicByte(0, b, c, d)
	#define TW28_WriteTable(b, c, d, e)		PCT_WriteAsicTable(0, b, c, d, e)
	#define TW28_WriteSTable(a, b)			PCT_WriteSTable(0, b)
	#define TW28_ReadByte(b, c)   			PCT_ReadAsicByte(0, b, c)
	#define ReadSignalSta(a,b) 				PCT_ReadAsicByte(0, a, b)
	#define TW28_SetAsicFlgType(b, c, d, e)	SetAsicFlgType(0, b, c, d, e)
#else
	#define TW28_WriteByte(b, c, d)			PCT_I2CWriteByte(TW2835_DVCADDR, b, c, d)
	#define TW28_WriteTable(b, c, d, e)		PCT_I2CWriteTable(TW2835_DVCADDR, b, c, d, e)
	#define TW28_WriteSTable(a, b)			PCT_WriteSTable(TW2835_DVCADDR, b)
	#define TW28_ReadByte(b, c)				PCT_I2CReadByte(TW2835_DVCADDR, b, c)
	#define ReadSignalSta(a,b)				PCT_I2CReadByte(TW2835_DVCADDR, a, b)
#endif
	
// ===========================================================================
// END of File
// ===========================================================================
