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
#include "Types.h"
#include "OSDCtrl.h"
#include "BusCtrl.h"

#include "Font.h"
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
	U8 bdata bitdat;
	sbit DAT_BIT0 = bitdat^0;
	sbit DAT_BIT1 = bitdat^1;
	sbit DAT_BIT2 = bitdat^2;
	sbit DAT_BIT3 = bitdat^3;
	sbit DAT_BIT4 = bitdat^4;
	sbit DAT_BIT5 = bitdat^5;
	sbit DAT_BIT6 = bitdat^6;
	sbit DAT_BIT7 = bitdat^7;

	data U8 foreColor;
	data U8 backColor;

//	------------------------------------
//			Function Prototypes
//	------------------------------------

// ===========================================================================
//                      Parallel function description
// ===========================================================================
//
// Set Foreground Color range:0-63
//
void PCT_PreSetForegroundColor(U8 _color)
{
	foreColor = _color;
	//printf("=== Fore Color = %bx === \n", foreColor);
}

// ===========================================================================
//
// Set Foreground Color range:0-63
//
void PCT_PreSetBackgroundColor(U8 _color)
{
	backColor = _color;
	//printf("=== Back Color = %bx === \n", backColor);
}

// ===========================================================================
//
// Set OSD Index Color Table	
//
void PCT_SetOSDColor(U8 _pth, U8 _col_num, U8 _y, U8 _cb, U8 _cr)
{
	WriteByteOSD(0x0b, _y);						//... Y
	WriteByteOSD(0x0c, _cb);					//... Cb
	WriteByteOSD(0x0d, _cr);					//... Cr
#ifdef TW2835_FUNC_DEFINE  //Pinchi 20150324 add
	_ifBitSet(_pth,PTH_X)
#else
	ifBitSet(_pth,PTH_X)
#endif
		WriteByteOSD(0x0e, BIT7|_col_num);		//... address
	else
		WriteByteOSD(0x0e, BIT7|BIT6|_col_num);	//... address
}

// ===========================================================================
//
//		
//
void PCT_InitOSDColor(void)
{
	WriteByteOSD(0x1F, 0xC0);//<William-960820>blink DELAY2Sec
	WriteByteOSD(0x0F, 0x0C);
	PCT_SetOSDColor(PTH_Y, OSD_COL_RED, 0x4c,0x54,0xff);
	PCT_SetOSDColor(PTH_Y, OSD_COL_GRN, 76, 84, 74);
	PCT_SetOSDColor(PTH_Y, OSD_COL_BLU, 0x1d,0xff,0x6b);

	PCT_SetOSDColor(PTH_X, OSD_COL_BLK, 0x00,0x80,0x80);
	PCT_SetOSDColor(PTH_X, OSD_COL_RED, 0x4c,0x54,0xff);
	PCT_SetOSDColor(PTH_X, OSD_COL_GRN, 0x4B, 0x55, 0x4A);
	PCT_SetOSDColor(PTH_X, OSD_COL_BLU, 0x1d,0xff,0x6b);
	PCT_SetOSDColor(PTH_X, OSD_COL_100WHT,0xf0,0x80,0x80);
	PCT_SetOSDColor(PTH_X, OSD_COL_75WHT, 0xc0,0x80,0x80);
	PCT_SetOSDColor(PTH_X, OSD_COL_50WHT, 0x7f,0x80,0x80);
	PCT_SetOSDColor(PTH_X, OSD_COL_25WHT, 0x3f,0x80,0x80);
	PCT_SetOSDColor(PTH_X, OSD_COL_ORNG, 0x95,0x4f,0xb5);
	PCT_SetOSDColor(PTH_X, OSD_COL_CYN, 0xb2,0xaa,0x00);
	PCT_SetOSDColor(PTH_X, OSD_COL_MGN, 0x69,0xd4,0xea);
	PCT_SetOSDColor(PTH_X, OSD_COL_OCN, 0x61,0xb5,0x3a);
	PCT_SetOSDColor(PTH_X, OSD_COL_YLW, 0xE1, 0x00, 0x94);
	PCT_SetOSDColor(PTH_X, OSD_COL_RED255, 0x4c,0x54,0xff);

	backColor=0;
	foreColor=0;
}

// ===========================================================================
//
//	Setting Page for Draw OSD	
//
void PCT_SetOSDDrawPage(U8 _page)
{
	_page = (_page<<2) | (ReadByteOSD(0x0A)&0xC3);
	WriteByteOSD(0x0A, _page);
}

// ===========================================================================
//
//	Enable OSD Page	0:OFF 1-6:Page 1-6 ON 
//
void PCT_EnShowOSDPage(U8 _page)
{
	if(_page == WRPHY_PAGE0) {
		_page = (_page&0x07)<<4|(ReadByteOSD(0x0F)&0x0F);
		WriteByteOSD(0x0F, SetBit(_page, BIT1));
	} else {
		_page = (_page&0x07)<<4|(ReadByteOSD(0x0F)&0x0F);
		WriteByteOSD(0x0F, SetBit(_page, BIT3));
	}
}

// ===========================================================================
//
//	Disable OSD Page Path X
//
void PCT_DisShowOSDPage(U8 _bit)
{
	register dat;
	dat = (ReadByteOSD(0x0F)&0x0F);
	WriteByteOSD(0x0F, ClearBit(dat, _bit));
}

// ===========================================================================
//
// Full Color on OSD of X Channel	
// _posx  : Start point for Horizontal (unit = 8 Dots)
// _posy  : Start point for Vertical   (unit = 8 Dots)
//
void PCT_FullColorOnOSD(U8 _posx, U16 _posy, U8 _wide, U16 _high)
{
	WriteByteOSD(0x00, backColor);		//... 1st pixel
	WriteByteOSD(0x01, backColor);		//... 2nd pixel
	WriteByteOSD(0x02, backColor);		//... 3rd pixel
	WriteByteOSD(0x03, backColor);		//... 4th pixel

	_posx <<= 1;
	_posy <<= 3;
	_wide = _posx+((_wide)<<1)-1;
	_high = _posy+((_high)<<3)-1;

	WriteByteOSD(0x05, _posx);
	WriteByteOSD(0x06, _wide);
	WriteByteOSD(0x07, _posy&0xff);
	WriteByteOSD(0x08, _high&0xff);
	WriteByteOSD(0x09, 0x02|((_posy>>8)<<2)+(_high>>8));	//... ~ even field

	WriteByteOSD(0x0A, 0xc0|ReadByteOSD(0x0A));			//... acceleration|x path
	while(ReadOSDMemWr()&BIT7){}	//... wait finishing write for even field
}

void PCT_ClearOSDPageX(U8 _page)
{
	PCT_SetOSDDrawPage(_page);

	PCT_PreSetBackgroundColor(OSD_COL_CLR);
	PCT_FullColorOnOSD(0,0,90,38);
}

// ===========================================================================
//
// Draw 16 Dots to OSD Dtat Buuffer 0-15
//
void PCT_WriteOSDDataBufferX(U8 _index, PU8 _dat)
{
	bitdat = _dat[0];
	WriteByteOSD(0x00, DAT_BIT7 ? (foreColor) : (backColor));		//... 1st pixel
	WriteByteOSD(0x01, DAT_BIT6 ? (foreColor) : (backColor));		//... 2nd pixel
	WriteByteOSD(0x02, DAT_BIT5 ? (foreColor) : (backColor));		//... 3rd pixel
	WriteByteOSD(0x03, DAT_BIT4 ? (foreColor) : (backColor));		//... 4th pixel
	WriteByteOSD(0x04, 0x80|_index);			//... write to buffer
	_index++;
	
	WriteByteOSD(0x00, DAT_BIT3 ? (foreColor) : (backColor));		//... 1st pixel
	WriteByteOSD(0x01, DAT_BIT2 ? (foreColor) : (backColor));		//... 2nd pixel
	WriteByteOSD(0x02, DAT_BIT1 ? (foreColor) : (backColor));		//... 3rd pixel
	WriteByteOSD(0x03, DAT_BIT0 ? (foreColor) : (backColor));		//... 4th pixel
	WriteByteOSD(0x04, 0x80|_index);			//... write to buffer
	_index++;
	
	bitdat = _dat[1];
	WriteByteOSD(0x00, DAT_BIT7 ? (foreColor) : (backColor));		//... 1st pixel
	WriteByteOSD(0x01, DAT_BIT6 ? (foreColor) : (backColor));		//... 2nd pixel
	WriteByteOSD(0x02, DAT_BIT5 ? (foreColor) : (backColor));		//... 3rd pixel
	WriteByteOSD(0x03, DAT_BIT4 ? (foreColor) : (backColor));		//... 4th pixel
	WriteByteOSD(0x04, 0x80|_index);			//... write to buffer
	_index++;
	
	WriteByteOSD(0x00, DAT_BIT3 ? (foreColor) : (backColor));		//... 1st pixel
	WriteByteOSD(0x01, DAT_BIT2 ? (foreColor) : (backColor));		//... 2nd pixel
	WriteByteOSD(0x02, DAT_BIT1 ? (foreColor) : (backColor));		//... 3rd pixel
	WriteByteOSD(0x03, DAT_BIT0 ? (foreColor) : (backColor));		//... 4th pixel
	WriteByteOSD(0x04, 0x80|_index);			//... write to buffer
}

// ===========================================================================
//
// Draw 16x16 Dots for word, tatal 4 words is 64 x 16 Dots
// _posx  : Start point for Horizontal (unit = 8 Dots)
// _posy  : Start point for Vertical   (unit = 8 Dots)
// _len   : 1-4: 1-4 words
// _index : Ascii code for string
//
void PCT_WriteOSDFntX(U8 _posx, U16 _posy, U8 _len, PU8 _indx)	//... only one _pth at once
{
	data U8	i,j,posx;
	PCHAR charPtr[4];	
	
	_posx <<= 1;
	posx = _posx = _posx + BOX_OFFSET_X;    
	_posy <<= 3;
	_posy += BOX_OFFSET_Y;
	charPtr[0] = FONT_TABLE + (_indx[0]*32);
	charPtr[1] = FONT_TABLE + (_indx[1]*32);
	charPtr[2] = FONT_TABLE + (_indx[2]*32);
	charPtr[3] = FONT_TABLE + (_indx[3]*32);
	
	if(_len>4) _len=4;
	for(i=0; i<32; i+=2) {
		for(j=0; j<_len; j++) PCT_WriteOSDDataBufferX( j<<2, charPtr[j]+i);
		WriteByteOSD(0x05, posx);
		WriteByteOSD(0x07, _posy&0xff);

		WriteByteOSD(0x09, (((_len*4-1)<<4)|((_posy)>>8)<<2));			//... start: OSD_POS_V_ODD, end: OSD_POS_V_ODD
		WriteByteOSD(0x0A, 0x80|(ReadByteOSD(0x0A)&0x3F));				//... x path
		while(ReadOSDMemWr()&BIT7);										//... wait finishing write for odd field

		WriteByteOSD(0x09, (((_len*4-1)<<4)|((_posy)>>8)<<2)|0x08);		//... start: OSD_POS_V_ODD, end: OSD_POS_V_ODD
		WriteByteOSD(0x0A, 0x80|(ReadByteOSD(0x0A)&0x3F));				//... x path
		while(ReadOSDMemWr()&BIT7);										//... wait finishing write for odd field

		_posy++;
	}
}

// ===========================================================================
//
// Clear 16x16 Dots for word, tatal N words
// _posx  : Start point for Horizontal (unit = 8 Dots)
// _posy  : Start point for Vertical   (unit = 8 Dots)
// _len   : 1-4: 1-4 words
//
void PCT_ClearWordsPathX(U8 _posx, U16 _posy, U8 _len)	
{
	register U8 	wide;
	register U16 high;

	WriteByteOSD(0x00, backColor);		//... 1st pixel
	WriteByteOSD(0x01, backColor);		//... 2nd pixel
	WriteByteOSD(0x02, backColor);		//... 3rd pixel
	WriteByteOSD(0x03, backColor);		//... 4th pixel

	_posx <<= 1;
	_posx += BOX_OFFSET_X;    
	_posy <<= 3;
		#if (TW2837==ON)
		_posy += BOX_OFFSET_Y+2;
		#else
		_posy += BOX_OFFSET_Y;
		#endif
	wide = _posx+(_len<<2)-1;
	high = _posy+15;

	WriteByteOSD(0x05, _posx);
	WriteByteOSD(0x06, wide);
	WriteByteOSD(0x07, _posy&0xff);
	WriteByteOSD(0x08, high&0xff);
	WriteByteOSD(0x09, 0x02|((_posy>>8)<<2)+(high>>8));	//... ~ even field

	WriteByteOSD(0x0A, 0xc0|ReadByteOSD(0x0A));			//... acceleration|x path
	while(ReadOSDMemWr()&BIT7){}	//... wait finishing write for even field
}

// ===========================================================================
//
// Draw 16 Dots to OSD Dtat Buuffer 0-15
//
void PCT_WriteOSDDataBufferY(U8 _index, PU8 _dat)
{
	bitdat = _dat[0];
	WriteByteOSD(0x00, ((DAT_BIT7 ? (foreColor) : (backColor))<<4)|(DAT_BIT6 ? (foreColor) : (backColor)));		//... 1st 2nd pixel
	WriteByteOSD(0x01, ((DAT_BIT5 ? (foreColor) : (backColor))<<4)|(DAT_BIT4 ? (foreColor) : (backColor)));		//... 3rd 4th pixel
	WriteByteOSD(0x02, ((DAT_BIT3 ? (foreColor) : (backColor))<<4)|(DAT_BIT2 ? (foreColor) : (backColor)));		//... 3rd 4th pixel
	WriteByteOSD(0x03, ((DAT_BIT1 ? (foreColor) : (backColor))<<4)|(DAT_BIT0 ? (foreColor) : (backColor)));		//... 3rd 4th pixel
	WriteByteOSD(0x04, 0x80|_index++);			//... write to buffer
	
	bitdat = _dat[1];
	WriteByteOSD(0x00, ((DAT_BIT7 ? (foreColor) : (backColor))<<4)|(DAT_BIT6 ? (foreColor) : (backColor)));		//... 1st 2nd pixel
	WriteByteOSD(0x01, ((DAT_BIT5 ? (foreColor) : (backColor))<<4)|(DAT_BIT4 ? (foreColor) : (backColor)));		//... 3rd 4th pixel
	WriteByteOSD(0x02, ((DAT_BIT3 ? (foreColor) : (backColor))<<4)|(DAT_BIT2 ? (foreColor) : (backColor)));		//... 3rd 4th pixel
	WriteByteOSD(0x03, ((DAT_BIT1 ? (foreColor) : (backColor))<<4)|(DAT_BIT0 ? (foreColor) : (backColor)));		//... 3rd 4th pixel
	WriteByteOSD(0x04, 0x80|_index++);			//... write to buffer
}

// ===========================================================================
//
// Draw 16x16 Dots for word, tatal 8 words is 128 x 16 Dots
// _posx  : Start point for Horizontal (unit = 8 Dots)
// _posy  : Start point for Vertical   (unit = 8 Dots)
// _len   : 1-4: 1-8 words
// _index : Ascii code for string
//
void PCT_WriteOSDFntY(U8 _posx, U16 _posy, U8 _len, PU8 _indx)	//... only one _pth at once
{
	data U8	i,j;
	PCHAR charPtr[8];	
	
	_posx <<= 1;
	_posx += YFONT_OFFSET_X;
	_posy <<= 3;
	_posy += YFONT_OFFSET_Y;

	if(_len>8) _len=8;
	for(i=0; i<_len; i++)
		charPtr[i] = FONT_TABLE + (_indx[i]*32);
	
	for(i=0; i<32; i+=2) {
		for(j=0; j<_len; j++) PCT_WriteOSDDataBufferY( j<<1, charPtr[j]+i);
		WriteByteOSD(0x05, _posx);
		WriteByteOSD(0x07, _posy&0xff);
		WriteByteOSD(0x09, (((_len<<5)-0x10)|((_posy)>>8)<<2));			//... start: OSD_POS_V_ODD, end: OSD_POS_V_ODD
		WriteByteOSD(0x0A, 0x80|(ReadByteOSD(0x0A)&0x3F));				//... x path
		while(ReadOSDMemWr()&BIT7);							//... wait finishing write for odd field
		_posy++;
	}
}

//==================================================================================
//
// Show String on OSD
//
void PCT_ShowOSDString(U8 _path, U8 _addrx, U8 _addry, PCHAR _strptr)
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
			PCT_WriteOSDFntX(_addrx, _addry, (U8) slen, _strptr);
			slen -= 4;
			_strptr+=4;
			_addrx+=8;
		}while(slen>0);
	} else {
		do{
			PCT_WriteOSDFntY(_addrx, _addry, (U8) slen, _strptr);
			slen -= 8;
			_strptr+=8;
			_addrx+=8;
		}while(slen>0);
	}
	PTC_SwitchToI2CMode();
}


// ===========================================================================
// END of File 
// ===========================================================================
