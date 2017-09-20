//  **************************************************************************
//
//       Copyright (c) 1992-2006 Professonal Computer Technology Co., Ltd
//
//      All rights are reserved. Reproduction in whole or in parts is
//  prohibited without the prior written consent of the copyright owner.
//  --------------------------------------------------------------------------
//
//  Module: TW28xx_Audio.H
//
//  Purpose: Implementation of TW28xx Audio.
//
//  Version: 0.01                                   2006/10/25 09:05¤W¤È
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
//	R0.01 2006/10/25 09:05¤W¤È Phoenix Chuang
//	Reason:
//		1. Original.
//	Solution:
//	
//  **************************************************************************
// 	-----------------------------------
//			Header Files
//	----------------------------------- 
#include "Types.h"
#include "TW28xx_Audio.h"
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
void PCT_AudioRegList(void)
{	
	printf("***** %bx == %bx *****\n",0x4c, TW28_ReadByte(0, 0x4c) );
	printf("***** %bx == %bx *****\n",0x60, TW28_ReadByte(0, 0x60) );
	printf("***** %bx == %bx *****\n",0x61, TW28_ReadByte(0, 0x61) );
	printf("***** %bx == %bx *****\n",0x62, TW28_ReadByte(0, 0x62) );
	printf("***** %bx == %bx *****\n",0x63, TW28_ReadByte(0, 0x63) );

	printf("***** %bx == %bx *****\n",0x64, TW28_ReadByte(0, 0x64) );
	printf("***** %bx == %bx *****\n",0x65, TW28_ReadByte(0, 0x65) );
	printf("***** %bx == %bx *****\n",0x66, TW28_ReadByte(0, 0x66) );
	printf("***** %bx == %bx *****\n",0x67, TW28_ReadByte(0, 0x67) );
	printf("***** %bx == %bx *****\n",0x68, TW28_ReadByte(0, 0x68) );
	printf("***** %bx == %bx *****\n",0x69, TW28_ReadByte(0, 0x69) );
	printf("***** %bx == %bx *****\n",0x6A, TW28_ReadByte(0, 0x6A) );
	printf("***** %bx == %bx *****\n",0x6B, TW28_ReadByte(0, 0x6B) );

	printf("***** %bx == %bx *****\n",0x6C, TW28_ReadByte(0, 0x6C) );
	printf("***** %bx == %bx *****\n",0x6D, TW28_ReadByte(0, 0x6D) );
	printf("***** %bx == %bx *****\n",0x6E, TW28_ReadByte(0, 0x6E) );
	printf("***** %bx == %bx *****\n",0x6F, TW28_ReadByte(0, 0x6F) );
	printf("***** %bx == %bx *****\n",0x70, TW28_ReadByte(0, 0x70) );

	printf("***** %bx == %bx *****\n",0x71, TW28_ReadByte(0, 0x71) );
	printf("***** %bx == %bx *****\n",0x72, TW28_ReadByte(0, 0x72) );
	printf("***** %bx == %bx *****\n",0x73, TW28_ReadByte(0, 0x73) );
	printf("***** %bx == %bx *****\n",0x74, TW28_ReadByte(0, 0x74) );
}

// ===========================================================================
//
//		Audio Inputer & Output Gain Control
//
BYTE PCT_AudioGainCtrl(U8 _dvc, U8 _channel, U8 _gain)
{
	register U8	dat;
	register U8 result;

	code RW_REG_DATA chanData[]= {
		{AIGAIN_CH01_ADDR, AIGAIN_CH00_MASK, 0},
		{AIGAIN_CH01_ADDR, AIGAIN_CH01_MASK, 4},
		{AIGAIN_CH23_ADDR, AIGAIN_CH03_MASK, 0},
		{AIGAIN_CH23_ADDR, AIGAIN_CH04_MASK, 4},
		{AIGAIN_CHAO_ADDR, AIGAIN_CHAO_MASK, 4}, 
	};
	
	#define AGAIN_PAGE 	GETHBYTE(chanData[_channel].addr)
	#define AGAIN_ADDR 	GETLBYTE(chanData[_channel].addr)
	#define AGAIN_MASK 	chanData[_channel].mask

	_dvc = 0;
	dat = TW28_ReadByte(AGAIN_PAGE, AGAIN_ADDR );
		
	dat &= AGAIN_MASK;
	dat |= _gain<<chanData[_channel].offset;
	
	TW28_WriteByte(AGAIN_PAGE, AGAIN_ADDR, dat);
	result = TW28_ReadByte(AGAIN_PAGE, AGAIN_ADDR );
	return true;
}


// ===========================================================================
//
//	Audio Miaxing Ratio Control
//
BYTE PCT_AudioMixCtrl(U8 _dvc, U8 _channel, U8 _gain)
{
	register U8	dat;
	register U8 result;

	code RW_REG_DATA chanData[]= {
		{MIXRATIO_CH01_ADDR,MIXRATIO_CH00_MASK, 0},
		{MIXRATIO_CH01_ADDR,MIXRATIO_CH01_MASK, 4},
		{MIXRATIO_CH23_ADDR,MIXRATIO_CH02_MASK, 0},
		{MIXRATIO_CH23_ADDR,MIXRATIO_CH03_MASK, 4},
		{MIXRATIO_CHAO_ADDR,MIXRATIO_CHAO_MASK, 0}, 
	};
	
	#define AMIX_PAGE 	GETHBYTE(chanData[_channel].addr)
	#define AMIX_ADDR 	GETLBYTE(chanData[_channel].addr)
	#define AMIX_MASK 	chanData[_channel].mask

	_dvc = 0;
	dat = TW28_ReadByte(AMIX_PAGE, AMIX_ADDR );
		
	dat &= AMIX_MASK;
	dat |= _gain<<chanData[_channel].offset;
	
	TW28_WriteByte(AMIX_PAGE, AMIX_ADDR, dat);
	result = TW28_ReadByte(AMIX_PAGE, AMIX_ADDR );

	PCT_AudioSelLive(_dvc, 0xFF);
	return true;
}

// ===========================================================================
//
//	Audio Mixing Mute Control
//
BYTE PCT_AudioMixMute(U8 _dvc, U8 _ch, U8 _ctrl)
{
	data U8 dat;

	#define MIXMUTE_PAGE GETHBYTE(ADO_MIX_MUTE_ADDR)
	#define MIXMUTE_ADDR GETLBYTE(ADO_MIX_MUTE_ADDR)
	
	_dvc = 0;
	dat = TW28_ReadByte(MIXMUTE_PAGE, MIXMUTE_ADDR );
	if( _ctrl==ON ) {
		dat &= ~_ch;
	} else  {
		dat |=  _ch;
	}
	TW28_WriteByte(MIXMUTE_PAGE, MIXMUTE_ADDR, dat);
	
	return true;
}

// ===========================================================================
//
// Audio Liive Select Control
//
BYTE PCT_AudioSelLive(U8 _dvc, U8 _chan)
{
	#define SEL_LMMOD_PAGE GETHBYTE(ADO_SEL_LMMOD_ADDR)
	#define SEL_LMMOD_ADDR GETLBYTE(ADO_SEL_LMMOD_ADDR)

	_dvc = 0;
	if( _chan==0xFF ) {
		TW28_WriteByte(SEL_LMMOD_PAGE, SEL_LMMOD_ADDR, ADO_MIX_MODE);
		return true;
	}
		
	_chan |= ADO_LIVE_MODE;
	TW28_WriteByte(SEL_LMMOD_PAGE, SEL_LMMOD_ADDR, _chan);
	return true;  //Pinchi 20150323 add for compiler warning
}


// ===========================================================================
// END of File 
// ===========================================================================

