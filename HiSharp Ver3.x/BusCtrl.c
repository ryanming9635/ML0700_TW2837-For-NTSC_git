//  **************************************************************************
//
//       Copyright (c) 1992-2006 Professonal Computer Technology Co., Ltd
//
//      All rights are reserved. Reproduction in whole or in parts is
//  prohibited without the prior written consent of the copyright owner.
//  --------------------------------------------------------------------------
//
//  Module: BUSCTRL.C
//
//  Purpose: Implementation of BUSCTRL.
//
//  Version: 0.01                                   2006/10/22 10:39¤U¤È
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
#include "Types.h"
#include "BusCtrl.h"


//	------------------------------------
//			Macro Definitions
//	------------------------------------ 


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
//                      Parallel function description
//==================================================================================
//	
//	
//	

extern BYTE TW2837IDCheck;

void PCT_PageChange(U8 _pg)
{
	U8 _dvc = 0;			//... temporal
	U8 _addr=0xFF;

	EA = OFF;		// Disable All Interrupt
	//... P[7:4]:INT[5:2], P1_3:HALE, P1_2:HRDB, P1_1:HWRB, P1_0:HSPB
	MCTRL = 0xf6;		//... initial state
	//if(_pg == DVC_PG0){	HCSB1=0;	HCSB0=0;}
	//else if(_pg == DVC_PG1){	HCSB1=0;	HCSB0=1;}
	//else if(_pg == DVC_PG2){	HCSB1=1;	HCSB0=0;}
	HCSB0=0;///1;
	HCSB1=0;///1;

	MDATA =	_addr;
	HALE = 1;	
	HALE = 0;
	MDATA =	_pg;
	HWRB = 0;				
	HWRB = 1;

	MCTRL = 0xf6;		//... initial state
	HCSB0=0;///1
	HCSB1=0;///1;
	MDATA =	0xff;
	EA = ON;		// Enable All Interrupt
}

void PCT_WriteAsicByte(U8 _dvc, U8 _pg, U8 _addr, U8 _wdat)
{
	_dvc = 0;			//... temporal

	EA = OFF;		// Disable All Interrupt
	//... P[7:4]:INT[5:2], P1_3:HALE, P1_2:HRDB, P1_1:HWRB, P1_0:HSPB

	if(TW2837IDCheck==TRUE)
	PCT_PageChange(_pg);

	MCTRL = 0xf6;		//... initial state

	if(TW2837IDCheck==TRUE)
	{
	HCSB0=0;///1;
	HCSB1=0;///1;
	}
	else
	{

	if(_pg == DVC_PG0){	HCSB1=0;	HCSB0=0;}
	else if(_pg == DVC_PG1){	HCSB1=0;	HCSB0=1;}
	else if(_pg == DVC_PG2){	HCSB1=1;	HCSB0=0;}
	}
	
	MDATA =	_addr;
	HALE = 1;	
	HALE = 0;
	MDATA =	_wdat;
	HWRB = 0;				
	HWRB = 1;

	MCTRL = 0xf6;		//... initial state

if(TW2837IDCheck==TRUE)
{
	HCSB0=0;///1;
	HCSB1=0;///1;
}
else
{
	HCSB0=1;
	HCSB1=1;
}
	MDATA =	0xff;
	EA = ON;		// Enable All Interrupt
}

//==================================================================================
//	
//	
//	
void PCT_WriteAsicTable(U8 _dvc, U8 _pg, U8 _addr, U8 *_tbl_ptr, U8 _tbl_cnt)
{
	_dvc = 0;			//... temporal

	EA = OFF;		// Disable All Interrupt
	//... P[7:4]:INT[5:2], P1_3:HALE, P1_2:HRDB, P1_1:HWRB, P1_0:HSPB
	//MCTRL_set();///MCTRL = 0xf6;		//... initial state

	if(TW2837IDCheck==TRUE)
	PCT_PageChange(_pg);

    MCTRL = 0xf6;		//... initial state

	if(TW2837IDCheck==TRUE)
	{
	HCSB0=0;///1;
	HCSB1=0;///1;
	}
	else
	{

	if(_pg == DVC_PG0){	HCSB1=0;	HCSB0=0;}
	else if(_pg == DVC_PG1){	HCSB1=0;	HCSB0=1;}
	else if(_pg == DVC_PG2){	HCSB1=1;	HCSB0=0;}
	}	
				
	do {
		MDATA =	_addr++;
		
		HALE = 1;         
		HALE = 0;
	
		MDATA =	*_tbl_ptr++;
		HWRB = 0;                       
		HWRB = 1;
	}while( --_tbl_cnt!=0 );

//	MCTRL_set();///MCTRL = 0xf6;		//... initial state

    MCTRL = 0xf6;		//... initial state

	if(TW2837IDCheck==TRUE)
	{
	HCSB0=0;///1;
	HCSB1=0;///1;
	}
	else
	{
	HCSB0=1;
	HCSB1=1;
	}	
	MDATA =	0xff;

	EA = ON;		// Enable All Interrupt
}


//==================================================================================
//	
//	
//	
U8 PCT_ReadAsicByte(U8 _dvc, U8 _pg, U8 _addr)
{
	register U8 _rdat_;

	EA = OFF;		// Disable All Interrupt

	if(TW2837IDCheck==TRUE)
	PCT_PageChange(_pg);
	
	//... P[7:4]:INT[5:2], P1_3:HALE, P1_2:HRDB, P1_1:HWRB, P1_0:HSPB
	MCTRL = 0xf6;		//... initial state

	_dvc = 0;			//... temporal
	
	if(TW2837IDCheck==TRUE)
	{
	HCSB0=0;///1;
	HCSB1=0;///1;
	}
	else
	{

	if(_pg == DVC_PG0){	HCSB1=0;	HCSB0=0;}
	else if(_pg == DVC_PG1){	HCSB1=0;	HCSB0=1;}
	else if(_pg == DVC_PG2){	HCSB1=1;	HCSB0=0;}
	}	
	
	MDATA =	_addr;
	HALE = 1;
	HALE = 0;
	MDATA =	0xff;		// port0(MDATA) input mode
	HRDB = 0;
	_rdat_ = MDATA;
	HRDB = 1;

	MCTRL = 0xf6;		//... initial state
	
	if(TW2837IDCheck==TRUE)
	{
	HCSB0=0;///1;
	HCSB1=0;///1;
	}
	else
	{
	HCSB0=1;
	HCSB1=1;
	}

	EA = ON;		// Enable All Interrupt
	return _rdat_;
}


//==================================================================================
//	
//	Write Register Address & Data form Table until address=0xFFFF then STOP
//	
void PCT_WriteSTable(U8 _dvc, WRITE_REG_DATA *_tbl_ptr)
{
	#define PAGE GETHBYTE(_tbl_ptr->addr)
	#define ADDR GETLBYTE(_tbl_ptr->addr)

	_dvc = 0;
	while( _tbl_ptr->addr!=0xFFFF ) {
	    if(TW28_ReadByte(PAGE, ADDR) != _tbl_ptr->dat)//William @HS 2007 0829 Ver3.4
	    	{
		TW28_WriteByte(PAGE, ADDR, _tbl_ptr->dat);
	    	}
		_tbl_ptr++;	
	}
}

//==================================================================================
//	
// Change to I2C Control Mode
//	
void PTC_SwitchToI2CMode(void)
{
#ifdef TW28_I2CBUS
	HSPB 	= 1;
	HALE 	= 1;
	MDATA 	= 0xFF;	
	HCSB0 	= 0;
	HCSB1 	= 0;
	HRDB 	= 0;
	HWRB 	= 0;
#endif
}
#if 0
void	SetAsicFlgType(U8 _dvc, U8 _pg, U8 _addr, U8 _flg, U8 _data)
{
	U8 _t1_;

	_t1_ = PCT_ReadAsicByte(_dvc,_pg,_addr);
	_t1_ = (_t1_ & ~_flg)|_data;
	PCT_WriteAsicByte(_dvc,_pg,_addr,_t1_);
}
#endif

// ===========================================================================
// END of File 
// ===========================================================================

