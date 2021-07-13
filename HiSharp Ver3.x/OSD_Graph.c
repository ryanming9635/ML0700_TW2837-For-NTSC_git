//  **************************************************************************
//
//       Copyright (c) 1992-2006 Professonal Computer Technology Co., Ltd
//
//      All rights are reserved. Reproduction in whole or in parts is
//  prohibited without the prior written consent of the copyright owner.
//  --------------------------------------------------------------------------
//
//  Module: OSDCtrl.C
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
//	R0.01 2007/5/7 09:04¤W¤È Phoenix Chuang
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
#include "OSD_Graph.h"
#include "OSDCtrl.h"

#include "Graph.h"
#include "Main.h"  //Pinchi 20150324 add


//	------------------------------------
//			Macro Definitions
//	------------------------------------ 
#define WriteByteOSD(b, c)			PCT_WriteAsicByte(0, DVC_PG2, b, c)
#define ReadByteOSD(a)				PCT_ReadAsicByte(0, DVC_PG2, a)
#define ReadOSDMemWr()				PCT_ReadAsicByte(0, DVC_PG2,0x0A)
#define ReadOSDBufWr()				PCT_ReadAsicByte(0, DVC_PG2,0x04)


//	------------------------------------
//			Type Definitions
//	------------------------------------

//	------------------------------------
//			Variables Definitions
//	------------------------------------
	U8 graphattr;

	extern BYTE TW2837IDCheck;

//	------------------------------------
//			Function Prototypes
//	------------------------------------


// ===========================================================================
//                      Parallel function description
// 						OSD Process by Graph Mode
// ===========================================================================
//
// Set Graph attribute BLANK & MIX
//
void PCT_ClearGraphAttr(void)
{
	graphattr = 0;
}

// ===========================================================================
//
// Set Graph attribute BLANK & MIX
//
#ifndef AWT_NO_SIGNAL_MSG  //Pinchi 20150331 add
#ifdef HS
#else
	void PCT_PreSetGraphAttr(U8 _attribute)
	{
		graphattr = _attribute;
		//printf("=== Graph Attribute = %bx === \n", graphattr);
	}
#endif
#endif

//==================================================================================
//
//
//
void PCT_OSD16x16GraphX(U8 _posx, U16 _posy, U8 _indx)
{
	register U8	row, column, cntr, cntc,posx;
	PCHAR graph;	
	
	_posx <<= 1;
	posx = _posx = _posx + BOX_OFFSET_X;    
	_posy <<= 3;
	
	if(TW2837IDCheck==TRUE)
		{
	if((_posy==0)||((_posy>>3)==7)||((_posy>>3)==13)||((_posy>>3)==21)\
			||((_posy>>3)==8)||((_posy>>3)==16)||((_posy>>3)==25))					
			_posy += BOX_OFFSET_Y+2;
		else
			_posy += BOX_OFFSET_Y-2;		
		}
	else
		{
	_posy += BOX_OFFSET_Y;
		}
	
	graph = GRAPH_TABLE + (_indx*258);
	row = *graph++;
	column = *graph++;
	
	for(cntr=0; cntr<row; cntr++) {
		for(cntc=0; cntc<column; cntc+=4) {
			WriteByteOSD(0x00, graph[0]+graphattr);		//... 1st pixel
			WriteByteOSD(0x01, graph[1]+graphattr);		//... 2nd pixel
			WriteByteOSD(0x02, graph[2]+graphattr);		//... 3rd pixel
			WriteByteOSD(0x03, graph[3]+graphattr);		//... 4th pixel
			WriteByteOSD(0x04, 0x80);					//... write to buffer
			graph+=4;
	
			WriteByteOSD(0x05, posx);
			WriteByteOSD(0x07, _posy&0xff);
	
			WriteByteOSD(0x09, ((_posy)>>8)<<2 );							//... start: OSD_POS_V_ODD, end: OSD_POS_V_ODD
			WriteByteOSD(0x0A, 0x80|(ReadByteOSD(0x0A)&0x3F));				//... x path
			while(ReadOSDMemWr()&BIT7);										//... wait finishing write for odd field
	
			WriteByteOSD(0x09, (((_posy)>>8)<<2)|0x08);						//... start: OSD_POS_V_Even, end: OSD_POS_V_Even
			WriteByteOSD(0x0A, 0x80|(ReadByteOSD(0x0A)&0x3F));				//... x path
			while(ReadOSDMemWr()&BIT7);										//... wait finishing write for odd field

			posx++;
		}
		posx = _posx;
		_posy++;
	}
}

//==================================================================================
//
//
//
void PCT_ShowGraphString(U8 _path, U8 _addrx, U8 _addry, PCHAR _strptr)
{
	register signed char slen;

	slen = strlen(_strptr);
	if(slen<0) return;
#ifdef TW2835_FUNC_DEFINE  //Pinchi 20150324 add
	_ifBitSet(_path, PTH_X)
#else
	ifBitSet(_path, PTH_X)
#endif
	{
		do{
			PCT_OSD16x16GraphX(_addrx, _addry, _strptr[0]);
			slen --;
			_strptr++;
			_addrx+=2;
		}while(slen>0);
	} else {
		do{
		}while(slen>0);
	}
	PTC_SwitchToI2CMode();

}

//==================================================================================
//
//
//


// ===========================================================================
// END of File 
// ===========================================================================
