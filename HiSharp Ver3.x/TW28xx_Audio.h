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


//	------------------------------------
//			Macro Definitions
//	------------------------------------ 
//
//	functions
//

//	
//	terminals
//	


//	------------------------------------
//			Type Definitions
//	------------------------------------

// ********** Audio Power Define **********
#define AUDIO_PWR_ADDR 	0x004C
#define AUDIO_ADC_PWR 	0x10
#define AUDIO_DAC_PWR 	0x20
// ****************************************


// ********** Audio Channel Define **********
#define ADO_CH00_ID	0
#define ADO_CH01_ID	1
#define ADO_CH02_ID	2
#define ADO_CH03_ID	3
#define ADO_CHAO_ID	4
// ******************************************

// ********** Gain Control Address & mask Define **********
#define AIGAIN_CH01_ADDR	0x0060	
#define AIGAIN_CH23_ADDR	0x0061	
#define AIGAIN_CHAO_ADDR	0x0070	

#define AIGAIN_CH00_MASK	0xF0	
#define AIGAIN_CH01_MASK	0x0F	
#define AIGAIN_CH03_MASK	0xF0	
#define AIGAIN_CH04_MASK	0x0F	
#define AIGAIN_CHAO_MASK	0x0F	
// ********************************************************

// ********** Mixing Control Address & mask Define **********
#define MIXRATIO_CH01_ADDR	0x006E	
#define MIXRATIO_CH23_ADDR	0x006F	
#define MIXRATIO_CHAO_ADDR	0x0070	

#define MIXRATIO_CH00_MASK	0xF0	
#define MIXRATIO_CH01_MASK	0x0F	
#define MIXRATIO_CH02_MASK	0xF0	
#define MIXRATIO_CH03_MASK	0x0F	
#define MIXRATIO_CHAO_MASK	0xF0	
// **********************************************************


// ********** Audio Setting Define **********
#define ADO_SET_ADDR_LB 0x0062
#define ADO_SET_ADDR_HB 0x0063

#define ADO_SETAI_DATALL	0x03FF
// Define the digital serial audio data format 
// for recode and mixing audio 
// on the ACLKR, ASYNR,ADATR and ADATM pin.
#define ADO_SYNC_I2S	0x0000
#define ADO_SYNC_DSP	0x0001
#define ADO_SYNC		0x0001

//Define the bit width for recode and mixingaudio
// on the ACLKR, ASYNR,ADATR and ADATM pin.
#define ADO_BITWID_16B	0x0000
#define ADO_BITWID_8B	0x0002
#define ADO_BITWID		0x0002

// Define the sample rate for recode and mixing audio 
// on the ACLKR, ASYNR,ADATR and ADATM pin.
#define ADO_SAMRATE_8K 	0x0000
#define ADO_SAMRATE_16K 0x0004
#define ADO_SAMRATE		0x0004

// Define the data mode on the ADATR and ADATM pin.
#define ADO_DATMOD_2CDM 0x0000
#define ADO_DATMOD_SBDM 0x0008
#define ADO_DATMOD		0x0008

// Define the bit rate for recode and mixing audio 
// on the ACLKR, ASYNR,ADATR and ADATM pin.
#define ADO_BITRATE_256 0x0000
#define ADO_BITRATE_384 0x0010
#define ADO_BITRATE		0x0010

// Define the secquence of mixing and playback 
// audio on the ADATM pin.
#define ADO_SWAP_RIGHT	0x0000
#define ADO_SWAP_LEFT	0x0020
#define ADO_SWAP		0x0020

// Select playback audio data on ADATM/AOUT pin.
#define ADO_PBSEL_CH00	0x0000
#define ADO_PBSEL_CH01	0x0040
#define ADO_PBSEL_CH02	0x0080
#define ADO_PBSEL_CH03	0x00C0
#define ADO_PBSEL		0x00C0

// Define the number of audio for recode on the ADATR pin.
#define ADO_ADATR_02AUD	0x0000
#define ADO_ADATR_04AUD 0x0100
#define ADO_ADATR_08AUD 0x0200
#define ADO_ADATR_16AUD 0x0300
#define ADO_ADATR	 	0x0300

// Select the output mode for the ADATM pin.
#define ADO_ADATM_MIX 	0x0000
#define ADO_ADATM_REC 	0x0400
#define ADO_ADATM	 	0x0400

// ******************************************


// ********** Audio Setting for Playback Inputer Define **********
#define ADO_SETPB_ADDR	0x006C

#define ADO_SETPB_DATALL	0x4F
// Define the digital serial audio data format for playback 
// audio on the ACLKP, ASYNP and ADATP pin.
#define ADO_PB_SYNC_I2S		0x00
#define ADO_PB_SYNC_DSP		0x01
#define ADO_PB_SYNC			0x01

// Defien the bit width for playback audio on the ADATP pin.
#define ADO_PB_BITWID_16B	0x00
#define ADO_PB_BITWID_8B	0x02
#define ADO_PB_BITWID		0x02

// Define the sample rate for playback 
// audio on the ACLKP, ASYNP and ADATP pin.
#define ADO_PB_SAMRATE_8K	0x00
#define ADO_PB_SAMRATE_16K	0x04
#define ADO_PB_SAMRATE		0x04

// Define the data mode on the ADATP pin.
#define ADO_PB_DATMOD_2CDM	0x00
#define ADO_PB_DATMOD_SBDM	0x08
#define ADO_PB_DATMOD		0x08

// Define the rate for playback 
// audio on the ACLKP, ASYNP and ADATP pin.
#define ADO_PB_BITRATE_256 	0x00
#define ADO_PB_BITRATE_384 	0x10
#define ADO_PB_BITRATE	 	0x10

// Select the channel for playback.
#define ADO_PB_LRSEL_LEFT	0x00
#define ADO_PB_LRSEL_RIGHT	0x20
#define ADO_PB_LRSEL		0x20

// Define the operation mode of 
// the ACLKP, ASYNP and ADATP pin.
#define ADO_PB_MASTER_MAS 	0x00
#define ADO_PB_MASTER_SLA 	0x40
#define ADO_PB_MASTER	 	0x40

// ***************************************************************

// ********** Audio Mute for Mixing Define **********
#define ADO_MIX_MUTE_ADDR	0x006D

// Enable the mute function for echo audio. It effects only for mixing.
#define ADO_MIX_MUTE_AIN0	0x01
#define ADO_MIX_MUTE_AIN1	0x02
#define ADO_MIX_MUTE_AIN2	0x04
#define ADO_MIX_MUTE_AIN3	0x08
#define ADO_MIX_MUTE_PBAI	0x10

// Disable the mixing ratio value for all audio 
#define ADO_MIX_DERATIO_DEF	0x00
#define ADO_MIX_DERATIO_NOM	0x20
#define ADO_MIX_DERATIO		0x20

// **************************************************

// ********** Audio Live & Mixing Mode Change Define **********
#define ADO_SEL_LMMOD_ADDR 0x0071
#define ADO_LIVE_MODE	0x40
#define ADO_MIX_MODE	0x54

#define ADO_LIVE_CHAN0	0x00
#define ADO_LIVE_CHAN1	0x01	
#define ADO_LIVE_CHAN2	0x02	
#define ADO_LIVE_CHAN3	0x03	
#define ADO_LIVE_CHAN4	0x04	
#define ADO_LIVE_CHAN5	0x05	
#define ADO_LIVE_CHAN6	0x06	
#define ADO_LIVE_CHAN7	0x07	
#define ADO_LIVE_CHAN8	0x08	
#define ADO_LIVE_CHAN9	0x09	
#define ADO_LIVE_CHAN10	0x0A  
#define ADO_LIVE_CHAN11 0x0B  
#define ADO_LIVE_CHAN12	0x0C  
#define ADO_LIVE_CHAN13	0x0D  
#define ADO_LIVE_CHAN14	0x0E  
#define ADO_LIVE_CHAN15	0x0F  

// ************************************************************

//	------------------------------------
//			Variables Definitions
//	------------------------------------

	
//	------------------------------------
//			Function Prototypes
//	------------------------------------

// ===========================================================================
//			Hardware-dependent ( Physical) primitives
// ===========================================================================
	extern void PCT_AudioRegList (void);
	extern BYTE PCT_AudioGainCtrl (U8 _dvc, U8 _channel, U8 _gain);
	extern BYTE PCT_AudioMixCtrl (U8 _dvc, U8 _channel, U8 _gain);
	extern BYTE PCT_AudioMixMute (U8 _dvc, U8 _ch, U8 _ctrl);
	extern BYTE PCT_AudioSelLive (U8 _dvc, U8 _chan);	
	
	
// ===========================================================================
//			Hardware-independent ( Logical) primitives
// ===========================================================================
	
	
// ===========================================================================
// END of File
// ===========================================================================
