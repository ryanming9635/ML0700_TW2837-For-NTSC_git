//  **************************************************************************
//
//       Copyright (c) 1992-2006 Professonal Computer Technology Co., Ltd
//
//      All rights are reserved. Reproduction in whole or in parts is
//  prohibited without the prior written consent of the copyright owner.
//  --------------------------------------------------------------------------
//
//  Module: OSDAction.C
//
//  Purpose: Implementation of OSD Action.
//
//  Version: 0.01                                   2006/12/25 09:43¤W¤È
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
//	R0.01 2006/12/25 09:43¤W¤È Phoenix Chuang
//	Reason:
//		1. Original.
//	Solution:
//	
//  **************************************************************************
// 	-----------------------------------
//			Header Files
//	----------------------------------- 
#include "Types.h"
#include "TW28xx_Video.h"
#include "Timer.h"
#include "BusCtrl.h"
#include "CommandShell.h"
#include "OSDAction.h"
#include "OSDCtrl.h"
#include "OSD_Graph.h"
#include "Main.h"  //Pinchi 20150323 add


//	------------------------------------
//			Macro Definitions
//	------------------------------------ 
#define GRAPH_FONT
#ifndef GRAPH_FONT
	#define DrawString(a, b, c)		PCT_ShowOSDString(PTH_X, a, b, c)
#else
	#define DrawString(a, b, c)		PCT_ShowGraphString(PTH_X, a, b, c)
#endif

#define LOCATE_XM0	20
#define LOCATE_XM1	41
#define LOCATE_XM2	62

#define LOCATE_YT0	0
#define LOCATE_YT1	15
#define LOCATE_YT2	18

code unsigned char camstr[7][3]={	{0x05,'\0'},//"A",
									{0x06,'\0'},//"B",
									{0x07,'\0'},//"C",
									{0x08,'\0'},//"R",
									{0x09,'\0'},//"M",
									{0x0A,'\0'},//"J",
								#if 1  //Pinchi 20150513 add new 'S' for SEQ mode
									{0x1F,'\0'},//"S",
								#else
									{0x12,'\0'},//"S",
								#endif
};

//	------------------------------------
//			Type Definitions
//	------------------------------------


//	------------------------------------
//			Variables Definitions
//	------------------------------------
	U8 bdata osdflage=0;
	sbit OSDPAGE2 = osdflage^0;
	sbit OSDPAGE3 = osdflage^1;
	sbit OSDPAGE4 = osdflage^2;
	sbit OSDPAGE5 = osdflage^3;
	U8 VlossCount;
	//bit VlossState;

	extern bit VlossFlag;

//	------------------------------------
//			Function Prototypes
//	------------------------------------


// ===========================================================================
//                      Parallel function description
// ===========================================================================
//
void PCT_InitialOSD(void)
{
	data U8 page;
	//... OSD color index
	PCT_InitOSDColor();
	PCT_ClearGraphAttr();

	PCT_PreSetForegroundColor(OSD_COL_100WHT);
	PCT_PreSetBackgroundColor(OSD_COL_BLU);
	for(page=0; page<6; page++){
		PCT_SetOSDDrawPage(page);
		PCT_FullColorOnOSD(0,0,90,38);			//... max line num is 310 line for OSD
	}
	PCT_EnShowOSDPage(WRPHX_PAGE1);
	PCT_PreSetBackgroundColor(OSD_COL_CLR);
	PCT_SetOSDDrawPage(WRPHY_PAGE0);
	PCT_FullColorOnOSD(0,0,90,38);				// ??

	SYSMODE=0;
}

// ===========================================================================
//
// PTH_X OSD Action
//
#define OSDBIT	BIT1
void PCT_OSD_ActionPthX(PU8 _attr)
{
	PCT_PreSetForegroundColor(OSD_COL_GRN);
	PCT_PreSetBackgroundColor(OSD_COL_CLR);
	switch(SYSMIXTYP) {
	#ifdef TW2835_FUNC_DEFINE  //Pinchi 20150324 add
		// ------------------------------------ NTSC ----------------------------------------
		case VMIX_TYPE_N11:
			_ifBitSet(_attr[0],OSDBIT) DrawString(LOCATE_XM1, LOCATE_YT0, camstr[SYSWINLK[0]]);
			break;

		case VMIX_TYPE_N21:
			_ifBitSet(_attr[0],OSDBIT) DrawString(LOCATE_XM1, LOCATE_YT0, camstr[SYSWINLK[0]]);//andy 980629
			_ifBitSet(_attr[1],OSDBIT) DrawString(LOCATE_XM1, LOCATE_YT1, camstr[SYSWINLK[1]]);//andy 980629
			break;

		case VMIX_TYPE_N22:
			_ifBitSet(_attr[0],OSDBIT) DrawString(LOCATE_XM0, LOCATE_YT0, camstr[SYSWINLK[0]]);
			_ifBitSet(_attr[1],OSDBIT) DrawString(LOCATE_XM2, LOCATE_YT0, camstr[SYSWINLK[1]]);
			break;

		case VMIX_TYPE_N31:
			_ifBitSet(_attr[0],OSDBIT) DrawString(LOCATE_XM1, LOCATE_YT0, camstr[SYSWINLK[0]]);
			_ifBitSet(_attr[1],OSDBIT) DrawString(LOCATE_XM0, LOCATE_YT1, camstr[SYSWINLK[1]]);
			_ifBitSet(_attr[2],OSDBIT) DrawString(LOCATE_XM2, LOCATE_YT1, camstr[SYSWINLK[2]]);
			break;

		case VMIX_TYPE_N32:
			break;

		case VMIX_TYPE_N33:	// Turn LEFT
			_ifBitSet(_attr[0],OSDBIT) DrawString(LOCATE_XM0, LOCATE_YT0, camstr[SYSWINLK[0]]);
			_ifBitSet(_attr[1],OSDBIT) DrawString(LOCATE_XM2, LOCATE_YT0, camstr[SYSWINLK[1]]);
			_ifBitSet(_attr[2],OSDBIT) DrawString(LOCATE_XM2, LOCATE_YT1, camstr[SYSWINLK[2]]);
			break;

		case VMIX_TYPE_N34:	// Turn RIGHT
			_ifBitSet(_attr[0],OSDBIT) DrawString(LOCATE_XM0, LOCATE_YT0, camstr[SYSWINLK[0]]);
			_ifBitSet(_attr[1],OSDBIT) DrawString(LOCATE_XM2, LOCATE_YT0, camstr[SYSWINLK[1]]);
			_ifBitSet(_attr[2],OSDBIT) DrawString(LOCATE_XM0, LOCATE_YT1, camstr[SYSWINLK[2]]);
			break;

		case VMIX_TYPE_N41:	
			_ifBitSet(_attr[0],OSDBIT) DrawString(LOCATE_XM0, LOCATE_YT0, camstr[SYSWINLK[0]]);
			_ifBitSet(_attr[1],OSDBIT) DrawString(LOCATE_XM2, LOCATE_YT0, camstr[SYSWINLK[1]]);
			_ifBitSet(_attr[2],OSDBIT) DrawString(LOCATE_XM0, LOCATE_YT1, camstr[SYSWINLK[2]]);
			_ifBitSet(_attr[3],OSDBIT) DrawString(LOCATE_XM2, LOCATE_YT1, camstr[SYSWINLK[3]]);
			break;

		// ------------------------------------ PAL ----------------------------------------
		case VMIX_TYPE_P11:	
			_ifBitSet(_attr[0],OSDBIT) DrawString(LOCATE_XM1, LOCATE_YT0, camstr[SYSWINLK[0]]);
			break;

		case VMIX_TYPE_P21:	
            _ifBitSet(_attr[0],OSDBIT) DrawString(LOCATE_XM1, LOCATE_YT0, camstr[SYSWINLK[0]]);//andy 980629
            _ifBitSet(_attr[1],OSDBIT) DrawString(LOCATE_XM1, LOCATE_YT2, camstr[SYSWINLK[1]]);//andy 980629
			break;

		case VMIX_TYPE_P22:	
			_ifBitSet(_attr[0],OSDBIT) DrawString(LOCATE_XM0, LOCATE_YT0, camstr[SYSWINLK[0]]);
			_ifBitSet(_attr[1],OSDBIT) DrawString(LOCATE_XM2, LOCATE_YT0, camstr[SYSWINLK[1]]);
			break;

		case VMIX_TYPE_P31:	
			_ifBitSet(_attr[0],OSDBIT) DrawString(LOCATE_XM1, LOCATE_YT0, camstr[SYSWINLK[0]]);
			_ifBitSet(_attr[1],OSDBIT) DrawString(LOCATE_XM0, LOCATE_YT2, camstr[SYSWINLK[1]]);
			_ifBitSet(_attr[2],OSDBIT) DrawString(LOCATE_XM2, LOCATE_YT2, camstr[SYSWINLK[2]]);
			break;

		case VMIX_TYPE_P32:	
			break;

		case VMIX_TYPE_P33:	// Turn LEFT
			_ifBitSet(_attr[0],OSDBIT) DrawString(LOCATE_XM0, LOCATE_YT0, camstr[SYSWINLK[0]]);
			_ifBitSet(_attr[1],OSDBIT) DrawString(LOCATE_XM2, LOCATE_YT0, camstr[SYSWINLK[1]]);
			_ifBitSet(_attr[2],OSDBIT) DrawString(LOCATE_XM2, LOCATE_YT2, camstr[SYSWINLK[2]]);
			break;

		case VMIX_TYPE_P34:	// Turn RIGHT
			_ifBitSet(_attr[0],OSDBIT) DrawString(LOCATE_XM0, LOCATE_YT0, camstr[SYSWINLK[0]]);
			_ifBitSet(_attr[1],OSDBIT) DrawString(LOCATE_XM2, LOCATE_YT0, camstr[SYSWINLK[1]]);
			_ifBitSet(_attr[2],OSDBIT) DrawString(LOCATE_XM0, LOCATE_YT2, camstr[SYSWINLK[2]]);
			break;

		case VMIX_TYPE_P41:	
			_ifBitSet(_attr[0],OSDBIT) DrawString(LOCATE_XM0, LOCATE_YT0, camstr[SYSWINLK[0]]);
			_ifBitSet(_attr[1],OSDBIT) DrawString(LOCATE_XM2, LOCATE_YT0, camstr[SYSWINLK[1]]);
			_ifBitSet(_attr[2],OSDBIT) DrawString(LOCATE_XM0, LOCATE_YT2, camstr[SYSWINLK[2]]);
			_ifBitSet(_attr[3],OSDBIT) DrawString(LOCATE_XM2, LOCATE_YT2, camstr[SYSWINLK[3]]);
			break;
	#else
		// ------------------------------------ NTSC ----------------------------------------
		case VMIX_TYPE_N11:	
			ifBitSet(_attr[0],OSDBIT) DrawString(LOCATE_XM1, LOCATE_YT0, camstr[SYSWINLK[0]]);
			break;

		case VMIX_TYPE_N21:	
			ifBitSet(_attr[0],OSDBIT) DrawString(LOCATE_XM1, LOCATE_YT0, camstr[SYSWINLK[0]]);//andy 980629
			ifBitSet(_attr[1],OSDBIT) DrawString(LOCATE_XM1, LOCATE_YT1, camstr[SYSWINLK[1]]);//andy 980629
			break;

		case VMIX_TYPE_N22:	
			ifBitSet(_attr[0],OSDBIT) DrawString(LOCATE_XM0, LOCATE_YT0, camstr[SYSWINLK[0]]);
			ifBitSet(_attr[1],OSDBIT) DrawString(LOCATE_XM2, LOCATE_YT0, camstr[SYSWINLK[1]]);
			break;

		case VMIX_TYPE_N31:	
			ifBitSet(_attr[0],OSDBIT) DrawString(LOCATE_XM1, LOCATE_YT0, camstr[SYSWINLK[0]]);
			ifBitSet(_attr[1],OSDBIT) DrawString(LOCATE_XM0, LOCATE_YT1, camstr[SYSWINLK[1]]);
			ifBitSet(_attr[2],OSDBIT) DrawString(LOCATE_XM2, LOCATE_YT1, camstr[SYSWINLK[2]]);
			break;

		case VMIX_TYPE_N32:	
			break;

		case VMIX_TYPE_N33:	// Turn LEFT
			ifBitSet(_attr[0],OSDBIT) DrawString(LOCATE_XM0, LOCATE_YT0, camstr[SYSWINLK[0]]);
			ifBitSet(_attr[1],OSDBIT) DrawString(LOCATE_XM2, LOCATE_YT0, camstr[SYSWINLK[1]]);
			ifBitSet(_attr[2],OSDBIT) DrawString(LOCATE_XM2, LOCATE_YT1, camstr[SYSWINLK[2]]);
			break;

		case VMIX_TYPE_N34:	// Turn RIGHT
			ifBitSet(_attr[0],OSDBIT) DrawString(LOCATE_XM0, LOCATE_YT0, camstr[SYSWINLK[0]]);
			ifBitSet(_attr[1],OSDBIT) DrawString(LOCATE_XM2, LOCATE_YT0, camstr[SYSWINLK[1]]);
			ifBitSet(_attr[2],OSDBIT) DrawString(LOCATE_XM0, LOCATE_YT1, camstr[SYSWINLK[2]]);
			break;

		case VMIX_TYPE_N41:	
			ifBitSet(_attr[0],OSDBIT) DrawString(LOCATE_XM0, LOCATE_YT0, camstr[SYSWINLK[0]]);
			ifBitSet(_attr[1],OSDBIT) DrawString(LOCATE_XM2, LOCATE_YT0, camstr[SYSWINLK[1]]);
			ifBitSet(_attr[2],OSDBIT) DrawString(LOCATE_XM0, LOCATE_YT1, camstr[SYSWINLK[2]]);
			ifBitSet(_attr[3],OSDBIT) DrawString(LOCATE_XM2, LOCATE_YT1, camstr[SYSWINLK[3]]);
			break;

		// ------------------------------------ PAL ----------------------------------------
		case VMIX_TYPE_P11:	
			ifBitSet(_attr[0],OSDBIT) DrawString(LOCATE_XM1, LOCATE_YT0, camstr[SYSWINLK[0]]);
			break;

		case VMIX_TYPE_P21:	
			ifBitSet(_attr[0],OSDBIT) DrawString(LOCATE_XM1, LOCATE_YT0, camstr[SYSWINLK[0]]);//andy 980629
			ifBitSet(_attr[1],OSDBIT) DrawString(LOCATE_XM1, LOCATE_YT2, camstr[SYSWINLK[1]]);//andy 980629
			break;

		case VMIX_TYPE_P22:	
			ifBitSet(_attr[0],OSDBIT) DrawString(LOCATE_XM0, LOCATE_YT0, camstr[SYSWINLK[0]]);
			ifBitSet(_attr[1],OSDBIT) DrawString(LOCATE_XM2, LOCATE_YT0, camstr[SYSWINLK[1]]);
			break;

		case VMIX_TYPE_P31:	
			ifBitSet(_attr[0],OSDBIT) DrawString(LOCATE_XM1, LOCATE_YT0, camstr[SYSWINLK[0]]);
			ifBitSet(_attr[1],OSDBIT) DrawString(LOCATE_XM0, LOCATE_YT2, camstr[SYSWINLK[1]]);
			ifBitSet(_attr[2],OSDBIT) DrawString(LOCATE_XM2, LOCATE_YT2, camstr[SYSWINLK[2]]);
			break;

		case VMIX_TYPE_P32:	
			break;

		case VMIX_TYPE_P33:	// Turn LEFT
			ifBitSet(_attr[0],OSDBIT) DrawString(LOCATE_XM0, LOCATE_YT0, camstr[SYSWINLK[0]]);
			ifBitSet(_attr[1],OSDBIT) DrawString(LOCATE_XM2, LOCATE_YT0, camstr[SYSWINLK[1]]);
			ifBitSet(_attr[2],OSDBIT) DrawString(LOCATE_XM2, LOCATE_YT2, camstr[SYSWINLK[2]]);
			break;

		case VMIX_TYPE_P34:	// Turn RIGHT
			ifBitSet(_attr[0],OSDBIT) DrawString(LOCATE_XM0, LOCATE_YT0, camstr[SYSWINLK[0]]);
			ifBitSet(_attr[1],OSDBIT) DrawString(LOCATE_XM2, LOCATE_YT0, camstr[SYSWINLK[1]]);
			ifBitSet(_attr[2],OSDBIT) DrawString(LOCATE_XM0, LOCATE_YT2, camstr[SYSWINLK[2]]);
			break;

		case VMIX_TYPE_P41:	
			ifBitSet(_attr[0],OSDBIT) DrawString(LOCATE_XM0, LOCATE_YT0, camstr[SYSWINLK[0]]);
			ifBitSet(_attr[1],OSDBIT) DrawString(LOCATE_XM2, LOCATE_YT0, camstr[SYSWINLK[1]]);
			ifBitSet(_attr[2],OSDBIT) DrawString(LOCATE_XM0, LOCATE_YT2, camstr[SYSWINLK[2]]);
			ifBitSet(_attr[3],OSDBIT) DrawString(LOCATE_XM2, LOCATE_YT2, camstr[SYSWINLK[3]]);
			break;
	#endif

		default:
			break;
	}
}

// ===========================================================================
//
// Check Video Loss
//
void PCT_EnfalshVLoss(void)
{	
	SYSVDOSGL |= BIT7;
}

// ===========================================================================
//
// Get Video Signal Status
//
void PCT_GetVideoSignalStatus(void)
{	
	MSGVDOSGL = ReadSignalSta(0x01, 0x78)&0x0F;

	if(SYSVDOSGL == MSGVDOSGL) return;				// Check Video Loss
	// --------------- Processing Show VLoss ---------------
     //William-V3.10-20100206>>>>>>>>>>>>>>>>NTSC PAL Detect when Video Loss
	VlossFlag=1;
	TW28_WriteByte(0x00,0x31,TW28_ReadByte(0x00,0x31)&0x7f);
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#ifdef AWT_NO_SIGNAL_MSG  //Pinchi 20150323 add
//	if (VlossFlag == 0)
	{
//		VlossFlag=1;
	PCT_ShowVLoss();
	}
#else
	#ifdef HOLGER//don't dispaly vloss OSD
	#else
	PCT_PreSetForegroundColor(OSD_COL_RED255|OSD_BLINK);
	PCT_PreSetGraphAttr(OSD_BLINK);
	PCT_ShowVLoss();
	PCT_ClearGraphAttr();
	#endif
#endif
	// -----------------------------------------------------
	SYSVDOSGL = MSGVDOSGL;
}

// ===========================================================================
//
// Show '<-' on OSD when Trun LEFT
// Show '->' on OSD when Trun RIGHT
//
#define ILCT_X0	28
#define ILCT_X1	49
#define ILCT_X2	70
#define ICONBIT	0x0C
#define ICONSFT	2

code unsigned char indicate_icon[] = {
	0x20,'\0',	//+ 0x20,'\0',
	0x0B,'\0',  //+ 0x02,'\0',
	0x0C,'\0',  //+ 0x03,'\0',
	0x0D,'\0',  //+ 0x04,'\0',
};

void PCT_ShowIndicateIcon(PU8 _attr)
{
	data U8 iconid;
//	printf("Command Shell for HiSharp Set S or J Mode");
	
	PCT_PreSetForegroundColor(OSD_COL_RED+OSD_BLINK);
	switch(SYSMIXTYP) {
		// ------------------------------------ NTSC & PAL ----------------------------------------
		case VMIX_TYPE_N11:	
		case VMIX_TYPE_P11:	
			iconid = (_attr[0]&ICONBIT) >> ICONSFT;

			if(iconid) {
				PCT_ClearWordsPathX(0, LOCATE_YT0, 2);
				DrawString(ILCT_X1, LOCATE_YT0, &indicate_icon[iconid<<1]);
			} 
			else {
				PCT_ClearWordsPathX(ILCT_X1, LOCATE_YT0, 1);
			#ifdef AWT_DRAW_T_ICON  //Pinchi 20150415 add to draw T icon when CAM C trigger
				if (_attr[0] & 0x20)
				{
					PCT_ClearWordsPathX(0, LOCATE_YT0, 2);	//Pinchi 20150422 add
					DrawString(1, LOCATE_YT0, &indicate_icon[0]);
				}
				else
				{
					if (SYSMODE == 0)	//Pinchi 20150422 add
						PCT_ClearWordsPathX(1, LOCATE_YT0, 1);
				}
			#endif
			}
			break;

		case VMIX_TYPE_N21:	
		case VMIX_TYPE_P21:	////////////////////////////andy-980604
			// ---------- LEFT Windows ----------
			iconid = (_attr[0]&ICONBIT) >> ICONSFT;

			if(iconid) {
				PCT_ClearWordsPathX(0, LOCATE_YT0, 2);
				DrawString(ILCT_X0, LOCATE_YT0, &indicate_icon[iconid<<1]);
			}
			else {
				PCT_ClearWordsPathX(ILCT_X0, LOCATE_YT0, 1);			
			#ifdef AWT_DRAW_T_ICON	//Pinchi 20150415 add to draw T icon when CAM C trigger
				if (_attr[0] & 0x20)
				{
					PCT_ClearWordsPathX(0, LOCATE_YT0, 2);	//Pinchi 20150422 add
					DrawString(1, LOCATE_YT0, &indicate_icon[0]);
				}
				else
				{
					if (SYSMODE == 0)	//Pinchi 20150422 add
						PCT_ClearWordsPathX(1, LOCATE_YT0, 1);
				}
			#endif
			}

			// ---------- RIGHT Windows ----------
			iconid = (_attr[1]&ICONBIT) >> ICONSFT;
			if(iconid) {
				PCT_ClearWordsPathX(0, LOCATE_YT0, 2);
				DrawString(ILCT_X2, LOCATE_YT0, &indicate_icon[iconid<<1]);
			}
			else {
				PCT_ClearWordsPathX(ILCT_X2, LOCATE_YT0, 1);
			}
			break;

		case VMIX_TYPE_N22:	
		case VMIX_TYPE_P22:	
			// ---------- LEFT Windows ----------
			iconid = (_attr[0]&ICONBIT) >> ICONSFT;

			if(iconid) {
				PCT_ClearWordsPathX(0, LOCATE_YT0, 2);
				DrawString(ILCT_X0, LOCATE_YT0, &indicate_icon[iconid<<1]);
			}
			else {
				PCT_ClearWordsPathX(ILCT_X0, LOCATE_YT0, 1);
			#ifdef AWT_DRAW_T_ICON	//Pinchi 20150415 add to draw T icon when CAM C trigger
				if (_attr[0] & 0x20)
				{
					PCT_ClearWordsPathX(0, LOCATE_YT0, 2);	//Pinchi 20150422 add
					DrawString(1, LOCATE_YT0, &indicate_icon[0]);
				}
				else
				{
					if (SYSMODE == 0)	//Pinchi 20150422 add
						PCT_ClearWordsPathX(1, LOCATE_YT0, 1);
				}
			#endif
			}

			// ---------- RIGHT Windows ----------
			iconid = (_attr[1]&ICONBIT) >> ICONSFT;
			if(iconid) {
				PCT_ClearWordsPathX(0, LOCATE_YT0, 2);
				DrawString(ILCT_X2, LOCATE_YT0, &indicate_icon[iconid<<1]);
			}
			else {
				PCT_ClearWordsPathX(ILCT_X2, LOCATE_YT0, 1);
			}
			break;

		case VMIX_TYPE_N31:	// Trun Back
		case VMIX_TYPE_P31:	// Trun Back
			// ---------- Trun Back Window Show "|" ----------
			iconid = (_attr[0]&ICONBIT) >> ICONSFT;

			if(iconid) {
				PCT_ClearWordsPathX(0, LOCATE_YT0, 2);
				DrawString(ILCT_X1, LOCATE_YT0, &indicate_icon[iconid<<1]);
			}
			else {
				PCT_ClearWordsPathX(ILCT_X1, LOCATE_YT0, 1);
			#ifdef AWT_DRAW_T_ICON	//Pinchi 20150415 add to draw T icon when CAM C trigger
				if (_attr[0] & 0x20)
				{
					PCT_ClearWordsPathX(0, LOCATE_YT0, 2);	//Pinchi 20150422 add
					DrawString(1, LOCATE_YT0, &indicate_icon[0]);
				}
				else
				{
					if (SYSMODE == 0)	//Pinchi 20150422 add
						PCT_ClearWordsPathX(1, LOCATE_YT0, 1);
				}
			#endif
			}
			break;

		case VMIX_TYPE_N32:	
		case VMIX_TYPE_P32:	
			break;

		case VMIX_TYPE_N33:	// Trun LEFT
		case VMIX_TYPE_P33:	// Trun LEFT
			// ---------- Show "<-" ----------
			iconid = (_attr[0]&ICONBIT) >> ICONSFT;

			if(iconid) {
				PCT_ClearWordsPathX(0, LOCATE_YT0, 2);
				DrawString(ILCT_X0, LOCATE_YT0, &indicate_icon[iconid<<1]);
			}
			else {
				PCT_ClearWordsPathX(ILCT_X0, LOCATE_YT0, 1);
			#ifdef AWT_DRAW_T_ICON	//Pinchi 20150415 add to draw T icon when CAM C trigger
				if (_attr[0] & 0x20)
				{
					PCT_ClearWordsPathX(0, LOCATE_YT0, 2);	//Pinchi 20150422 add
					DrawString(1, LOCATE_YT0, &indicate_icon[0]);
				}
				else
				{
					if (SYSMODE == 0)	//Pinchi 20150422 add
						PCT_ClearWordsPathX(1, LOCATE_YT0, 1);
				}
			#endif
			}
			break;

		case VMIX_TYPE_N34:	// Trun RIGHT
		case VMIX_TYPE_P34:	// Trun RIGHT
			// ---------- Show "->" ----------
			iconid = (_attr[1]&ICONBIT) >> ICONSFT;

			if(iconid) {
				PCT_ClearWordsPathX(0, LOCATE_YT0, 2);
				DrawString(ILCT_X2, LOCATE_YT0, &indicate_icon[iconid<<1]);
			}
			else {
				PCT_ClearWordsPathX(ILCT_X2, LOCATE_YT0, 1);
			#ifdef AWT_DRAW_T_ICON	//Pinchi 20150415 add to draw T icon when CAM C trigger
				if (_attr[0] & 0x20)
				{
					PCT_ClearWordsPathX(0, LOCATE_YT0, 2);	//Pinchi 20150422 add
					DrawString(1, LOCATE_YT0, &indicate_icon[0]);
				}
				else
				{
					if (SYSMODE == 0)	//Pinchi 20150422 add
						PCT_ClearWordsPathX(1, LOCATE_YT0, 1);
				}
			#endif
			}
			break;

		case VMIX_TYPE_N41:	
		case VMIX_TYPE_P41:	
			break;

		default:	
			break;
	}
}

// ===========================================================================
//
// Show 'M'  on OSD when Video Mirror
//
#define MLCT_X0	23
#define MLCT_X1	44
#define MLCT_X2	65
#define MIRROR	camstr[4]
void PCT_ShowMirrorIcon(PU8 _attr)
{
	PCT_PreSetForegroundColor(OSD_COL_YLW);
	switch(SYSMIXTYP) {
	#ifdef TW2835_FUNC_DEFINE  //Pinchi 20150324 add
		// ------------------------------------ NTSC ----------------------------------------
		case VMIX_TYPE_N11:	
			// ---------- Window Show "M" ----------
			_ifBitSet(_attr[0],BIT0) {
				DrawString(MLCT_X1, LOCATE_YT0, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X1, LOCATE_YT0, 1);
			}
			break;

		case VMIX_TYPE_N21:	
            // ----------UP Window Show "M" ----------
			_ifBitSet(_attr[0],BIT0) {
				DrawString(MLCT_X1, LOCATE_YT0, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X1, LOCATE_YT0, 1);
			}
            // ----------DOWN Window Show "M" ----------
			_ifBitSet(_attr[1],BIT0) {
				DrawString(MLCT_X1, LOCATE_YT1, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X1, LOCATE_YT1, 1);
			}	
			break;

		case VMIX_TYPE_N22:	
			// ---------- LEFT Window Show "M" ----------
			_ifBitSet(_attr[0],BIT0) {
				DrawString(MLCT_X0, LOCATE_YT0, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X0, LOCATE_YT0, 1);
			}

			// ---------- RIGHT Window Show "M" ----------
			_ifBitSet(_attr[1],BIT0) {
				DrawString(MLCT_X2, LOCATE_YT0, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X2, LOCATE_YT0, 1);
			}

			break;

		case VMIX_TYPE_N31:	// Trun Back
			// ---------- TOP Window Show "M" ----------
			_ifBitSet(_attr[0],BIT0) {
				DrawString(MLCT_X1, LOCATE_YT0, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X1, LOCATE_YT0, 1);
			}

			// ---------- LEFT Window Show "M" ----------
			_ifBitSet(_attr[1],BIT0) {
				DrawString(MLCT_X0, LOCATE_YT1, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X0, LOCATE_YT1, 1);
			}

			// ---------- RIGHT Window Show "M" ----------
			_ifBitSet(_attr[2],BIT0) {
				DrawString(MLCT_X2, LOCATE_YT1, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X2, LOCATE_YT1, 1);
			}
			break;

		case VMIX_TYPE_N32:	
			break;

		case VMIX_TYPE_N33:	// Trun LEFT
			// ---------- LEFT Window Show "M" ----------
			_ifBitSet(_attr[0],BIT0) {
				DrawString(MLCT_X0, LOCATE_YT0, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X0, LOCATE_YT0, 1);
			}

			// ---------- RIGHT_TOP Window Show "M" ----------
			_ifBitSet(_attr[1],BIT0) {
				DrawString(MLCT_X2, LOCATE_YT0, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X2, LOCATE_YT0, 1);
			}

			// ---------- RIGHT_DOWN Window Show "M" ----------
			_ifBitSet(_attr[2],BIT0) {
				DrawString(MLCT_X2, LOCATE_YT1, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X2, LOCATE_YT1, 1);
			}
			break;

		case VMIX_TYPE_N34:	// Trun RIGHT
			// ---------- LEFT_TOP Window Show "M" ----------
			_ifBitSet(_attr[0],BIT0) {
				DrawString(MLCT_X0, LOCATE_YT0, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X0, LOCATE_YT0, 1);
			}

			// ---------- RIGHT Window Show "M" ----------
			_ifBitSet(_attr[1],BIT0) {
				DrawString(MLCT_X2, LOCATE_YT0, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X2, LOCATE_YT0, 1);
			}

			// ---------- LEFT_DOWN Window Show "M" ----------
			_ifBitSet(_attr[2],BIT0) {
				DrawString(MLCT_X0, LOCATE_YT1, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X0, LOCATE_YT1, 1);
			}
			break;

		case VMIX_TYPE_N41:	
			// ---------- LEFT_TOP Window Show "M" ----------
			_ifBitSet(_attr[0],BIT0) {
				DrawString(MLCT_X0, LOCATE_YT0, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X0, LOCATE_YT0, 1);
			}

			// ---------- RIGHT_TOP Window Show "M" ----------
			_ifBitSet(_attr[1],BIT0) {
				DrawString(MLCT_X2, LOCATE_YT0, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X2, LOCATE_YT0, 1);
			}

			// ---------- LEFT_DOWN Window Show "M" ----------
			_ifBitSet(_attr[2],BIT0) {
				DrawString(MLCT_X0, LOCATE_YT1, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X0, LOCATE_YT1, 1);
			}

			// ---------- RIGHT_DOWN Window Show "M" ----------
			_ifBitSet(_attr[3],BIT0) {
				DrawString(MLCT_X2, LOCATE_YT1, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X2, LOCATE_YT1, 1);
			}
			break;

		// ------------------------------------ PAL ----------------------------------------
		case VMIX_TYPE_P11:	
			// ---------- Window Show "M" ----------
			_ifBitSet(_attr[0],BIT0) {
				DrawString(MLCT_X1, LOCATE_YT0, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X1, LOCATE_YT0, 1);
			}
			break;

		case VMIX_TYPE_P21:	
             // ----------UP Window Show "M" ----------
			_ifBitSet(_attr[0],BIT0) {
				DrawString(MLCT_X1, LOCATE_YT0, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X1, LOCATE_YT0, 1);
			}
            // ----------DOWN Window Show "M" ----------
			_ifBitSet(_attr[1],BIT0) {
				DrawString(MLCT_X1, LOCATE_YT1, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X1, LOCATE_YT1, 1);
			}
			break;

		case VMIX_TYPE_P22:	
			// ---------- LEFT Window Show "M" ----------
			_ifBitSet(_attr[0],BIT0) {
				DrawString(MLCT_X0, LOCATE_YT0, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X0, LOCATE_YT0, 1);
			}

			// ---------- RIGHT Window Show "M" ----------
			_ifBitSet(_attr[1],BIT0) {
				DrawString(MLCT_X2, LOCATE_YT0, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X2, LOCATE_YT0, 1);
			}

			break;

		case VMIX_TYPE_P31:	// Trun Back
			// ---------- TOP Window Show "M" ----------
			_ifBitSet(_attr[0],BIT0) {
				DrawString(MLCT_X1, LOCATE_YT0, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X1, LOCATE_YT0, 1);
			}

			// ---------- LEFT Window Show "M" ----------
			_ifBitSet(_attr[1],BIT0) {
				DrawString(MLCT_X0, LOCATE_YT2, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X0, LOCATE_YT2, 1);
			}

			// ---------- RIGHT Window Show "M" ----------
			_ifBitSet(_attr[2],BIT0) {
				DrawString(MLCT_X2, LOCATE_YT2, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X2, LOCATE_YT2, 1);
			}
			break;

		case VMIX_TYPE_P32:	
			break;

		case VMIX_TYPE_P33:	// Trun LEFT
			// ---------- LEFT Window Show "M" ----------
			_ifBitSet(_attr[0],BIT0) {
				DrawString(MLCT_X0, LOCATE_YT0, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X0, LOCATE_YT0, 1);
			}

			// ---------- RIGHT_TOP Window Show "M" ----------
			_ifBitSet(_attr[1],BIT0) {
				DrawString(MLCT_X2, LOCATE_YT0, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X2, LOCATE_YT0, 1);
			}

			// ---------- RIGHT_DOWN Window Show "M" ----------
			_ifBitSet(_attr[2],BIT0) {
				DrawString(MLCT_X2, LOCATE_YT2, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X2, LOCATE_YT2, 1);
			}
			break;

		case VMIX_TYPE_P34:	// Trun RIGHT
			// ---------- LEFT_TOP Window Show "M" ----------
			_ifBitSet(_attr[0],BIT0) {
				DrawString(MLCT_X0, LOCATE_YT0, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X0, LOCATE_YT0, 1);
			}

			// ---------- RIGHT Window Show "M" ----------
			_ifBitSet(_attr[1],BIT0) {
				DrawString(MLCT_X2, LOCATE_YT0, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X2, LOCATE_YT0, 1);
			}

			// ---------- LEFT_DOWN Window Show "M" ----------
			_ifBitSet(_attr[2],BIT0) {
				DrawString(MLCT_X0, LOCATE_YT2, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X0, LOCATE_YT2, 1);
			}
			break;

		case VMIX_TYPE_P41:	
			// ---------- LEFT_TOP Window Show "M" ----------
			_ifBitSet(_attr[0],BIT0) {
				DrawString(MLCT_X0, LOCATE_YT0, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X0, LOCATE_YT0, 1);
			}

			// ---------- RIGHT_TOP Window Show "M" ----------
			_ifBitSet(_attr[1],BIT0) {
				DrawString(MLCT_X2, LOCATE_YT0, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X2, LOCATE_YT0, 1);
			}

			// ---------- LEFT_DOWN Window Show "M" ----------
			_ifBitSet(_attr[2],BIT0) {
				DrawString(MLCT_X0, LOCATE_YT2, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X0, LOCATE_YT2, 1);
			}

			// ---------- RIGHT_DOWN Window Show "M" ----------
			_ifBitSet(_attr[3],BIT0) {
				DrawString(MLCT_X2, LOCATE_YT2, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X2, LOCATE_YT2, 1);
			}
			break;
	#else
		// ------------------------------------ NTSC ----------------------------------------
		case VMIX_TYPE_N11:	
			// ---------- Window Show "M" ----------
			ifBitSet(_attr[0],BIT0) {
				DrawString(MLCT_X1, LOCATE_YT0, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X1, LOCATE_YT0, 1);
			}
			break;

		case VMIX_TYPE_N21:	
            // ----------UP Window Show "M" ----------
			ifBitSet(_attr[0],BIT0) {
				DrawString(MLCT_X1, LOCATE_YT0, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X1, LOCATE_YT0, 1);
			}
            // ----------DOWN Window Show "M" ----------
			ifBitSet(_attr[1],BIT0) {
				DrawString(MLCT_X1, LOCATE_YT1, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X1, LOCATE_YT1, 1);
			}	
			break;

		case VMIX_TYPE_N22:	
			// ---------- LEFT Window Show "M" ----------
			ifBitSet(_attr[0],BIT0) {
				DrawString(MLCT_X0, LOCATE_YT0, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X0, LOCATE_YT0, 1);
			}

			// ---------- RIGHT Window Show "M" ----------
			ifBitSet(_attr[1],BIT0) {
				DrawString(MLCT_X2, LOCATE_YT0, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X2, LOCATE_YT0, 1);
			}

			break;

		case VMIX_TYPE_N31:	// Trun Back
			// ---------- TOP Window Show "M" ----------
			ifBitSet(_attr[0],BIT0) {
				DrawString(MLCT_X1, LOCATE_YT0, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X1, LOCATE_YT0, 1);
			}

			// ---------- LEFT Window Show "M" ----------
			ifBitSet(_attr[1],BIT0) {
				DrawString(MLCT_X0, LOCATE_YT1, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X0, LOCATE_YT1, 1);
			}

			// ---------- RIGHT Window Show "M" ----------
			ifBitSet(_attr[2],BIT0) {
				DrawString(MLCT_X2, LOCATE_YT1, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X2, LOCATE_YT1, 1);
			}
			break;

		case VMIX_TYPE_N32:	
			break;

		case VMIX_TYPE_N33:	// Trun LEFT
			// ---------- LEFT Window Show "M" ----------
			ifBitSet(_attr[0],BIT0) {
				DrawString(MLCT_X0, LOCATE_YT0, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X0, LOCATE_YT0, 1);
			}

			// ---------- RIGHT_TOP Window Show "M" ----------
			ifBitSet(_attr[1],BIT0) {
				DrawString(MLCT_X2, LOCATE_YT0, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X2, LOCATE_YT0, 1);
			}

			// ---------- RIGHT_DOWN Window Show "M" ----------
			ifBitSet(_attr[2],BIT0) {
				DrawString(MLCT_X2, LOCATE_YT1, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X2, LOCATE_YT1, 1);
			}
			break;

		case VMIX_TYPE_N34:	// Trun RIGHT
			// ---------- LEFT_TOP Window Show "M" ----------
			ifBitSet(_attr[0],BIT0) {
				DrawString(MLCT_X0, LOCATE_YT0, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X0, LOCATE_YT0, 1);
			}

			// ---------- RIGHT Window Show "M" ----------
			ifBitSet(_attr[1],BIT0) {
				DrawString(MLCT_X2, LOCATE_YT0, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X2, LOCATE_YT0, 1);
			}

			// ---------- LEFT_DOWN Window Show "M" ----------
			ifBitSet(_attr[2],BIT0) {
				DrawString(MLCT_X0, LOCATE_YT1, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X0, LOCATE_YT1, 1);
			}
			break;

		case VMIX_TYPE_N41:	
			// ---------- LEFT_TOP Window Show "M" ----------
			ifBitSet(_attr[0],BIT0) {
				DrawString(MLCT_X0, LOCATE_YT0, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X0, LOCATE_YT0, 1);
			}

			// ---------- RIGHT_TOP Window Show "M" ----------
			ifBitSet(_attr[1],BIT0) {
				DrawString(MLCT_X2, LOCATE_YT0, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X2, LOCATE_YT0, 1);
			}

			// ---------- LEFT_DOWN Window Show "M" ----------
			ifBitSet(_attr[2],BIT0) {
				DrawString(MLCT_X0, LOCATE_YT1, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X0, LOCATE_YT1, 1);
			}

			// ---------- RIGHT_DOWN Window Show "M" ----------
			ifBitSet(_attr[3],BIT0) {
				DrawString(MLCT_X2, LOCATE_YT1, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X2, LOCATE_YT1, 1);
			}
			break;

		// ------------------------------------ PAL ----------------------------------------
		case VMIX_TYPE_P11:	
			// ---------- Window Show "M" ----------
			ifBitSet(_attr[0],BIT0) {
				DrawString(MLCT_X1, LOCATE_YT0, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X1, LOCATE_YT0, 1);
			}
			break;

		case VMIX_TYPE_P21:	
             // ----------UP Window Show "M" ----------
			ifBitSet(_attr[0],BIT0) {
				DrawString(MLCT_X1, LOCATE_YT0, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X1, LOCATE_YT0, 1);
			}
            // ----------DOWN Window Show "M" ----------
			ifBitSet(_attr[1],BIT0) {
				DrawString(MLCT_X1, LOCATE_YT1, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X1, LOCATE_YT1, 1);
			}
			break;

		case VMIX_TYPE_P22:	
			// ---------- LEFT Window Show "M" ----------
			ifBitSet(_attr[0],BIT0) {
				DrawString(MLCT_X0, LOCATE_YT0, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X0, LOCATE_YT0, 1);
			}

			// ---------- RIGHT Window Show "M" ----------
			ifBitSet(_attr[1],BIT0) {
				DrawString(MLCT_X2, LOCATE_YT0, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X2, LOCATE_YT0, 1);
			}

			break;

		case VMIX_TYPE_P31:	// Trun Back
			// ---------- TOP Window Show "M" ----------
			ifBitSet(_attr[0],BIT0) {
				DrawString(MLCT_X1, LOCATE_YT0, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X1, LOCATE_YT0, 1);
			}

			// ---------- LEFT Window Show "M" ----------
			ifBitSet(_attr[1],BIT0) {
				DrawString(MLCT_X0, LOCATE_YT2, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X0, LOCATE_YT2, 1);
			}

			// ---------- RIGHT Window Show "M" ----------
			ifBitSet(_attr[2],BIT0) {
				DrawString(MLCT_X2, LOCATE_YT2, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X2, LOCATE_YT2, 1);
			}
			break;

		case VMIX_TYPE_P32:	
			break;

		case VMIX_TYPE_P33:	// Trun LEFT
			// ---------- LEFT Window Show "M" ----------
			ifBitSet(_attr[0],BIT0) {
				DrawString(MLCT_X0, LOCATE_YT0, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X0, LOCATE_YT0, 1);
			}

			// ---------- RIGHT_TOP Window Show "M" ----------
			ifBitSet(_attr[1],BIT0) {
				DrawString(MLCT_X2, LOCATE_YT0, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X2, LOCATE_YT0, 1);
			}

			// ---------- RIGHT_DOWN Window Show "M" ----------
			ifBitSet(_attr[2],BIT0) {
				DrawString(MLCT_X2, LOCATE_YT2, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X2, LOCATE_YT2, 1);
			}
			break;

		case VMIX_TYPE_P34:	// Trun RIGHT
			// ---------- LEFT_TOP Window Show "M" ----------
			ifBitSet(_attr[0],BIT0) {
				DrawString(MLCT_X0, LOCATE_YT0, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X0, LOCATE_YT0, 1);
			}

			// ---------- RIGHT Window Show "M" ----------
			ifBitSet(_attr[1],BIT0) {
				DrawString(MLCT_X2, LOCATE_YT0, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X2, LOCATE_YT0, 1);
			}

			// ---------- LEFT_DOWN Window Show "M" ----------
			ifBitSet(_attr[2],BIT0) {
				DrawString(MLCT_X0, LOCATE_YT2, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X0, LOCATE_YT2, 1);
			}
			break;

		case VMIX_TYPE_P41:	
			// ---------- LEFT_TOP Window Show "M" ----------
			ifBitSet(_attr[0],BIT0) {
				DrawString(MLCT_X0, LOCATE_YT0, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X0, LOCATE_YT0, 1);
			}

			// ---------- RIGHT_TOP Window Show "M" ----------
			ifBitSet(_attr[1],BIT0) {
				DrawString(MLCT_X2, LOCATE_YT0, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X2, LOCATE_YT0, 1);
			}

			// ---------- LEFT_DOWN Window Show "M" ----------
			ifBitSet(_attr[2],BIT0) {
				DrawString(MLCT_X0, LOCATE_YT2, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X0, LOCATE_YT2, 1);
			}

			// ---------- RIGHT_DOWN Window Show "M" ----------
			ifBitSet(_attr[3],BIT0) {
				DrawString(MLCT_X2, LOCATE_YT2, MIRROR);
			} else {
				PCT_ClearWordsPathX(MLCT_X2, LOCATE_YT2, 1);
			}
			break;
	#endif

		default:
			break;
	}
}

#define SLCT_X0	31
#define SLCT_X1	52
#define SLCT_X2	73
//+ code unsigned char SPEAKICON[] = {0x01,'\0'};
code unsigned char SPEAKICON[] = {0x0E,'\0'};
// ===========================================================================
//
// Show Speak Icon on OSD 
//
void PCT_ShowSpeakIcon(PU8 _attr)
{
	PCT_PreSetForegroundColor(OSD_COL_GRN);
	switch(SYSMIXTYP) {
	#ifdef TW2835_FUNC_DEFINE  //Pinchi 20150324 add
		// ------------------------------------ NTSC ----------------------------------------
		case VMIX_TYPE_N11:	
			_ifBitSet(_attr[0],BIT4) {
				DrawString(SLCT_X1, LOCATE_YT0, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X1, LOCATE_YT0, 1);
			}
			break;

		case VMIX_TYPE_N21:	     //andy 980630
			_ifBitSet(_attr[0],BIT4) {
				DrawString(SLCT_X1, LOCATE_YT0, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X1, LOCATE_YT0, 1);
			}
			_ifBitSet(_attr[0],BIT4) {
				DrawString(SLCT_X1, LOCATE_YT0, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X1, LOCATE_YT1, 1);
			}
			break;

		case VMIX_TYPE_N22:	
			_ifBitSet(_attr[0],BIT4) {
				DrawString(SLCT_X0, LOCATE_YT0, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X0, LOCATE_YT0, 1);
			}
			_ifBitSet(_attr[1],BIT4) {
				DrawString(SLCT_X2, LOCATE_YT0, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X2, LOCATE_YT0, 1);
			}
			break;

		case VMIX_TYPE_N31:	// Trun Back
			_ifBitSet(_attr[0],BIT4) {
				DrawString(SLCT_X1, LOCATE_YT0, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X1, LOCATE_YT0, 1);
			}
			_ifBitSet(_attr[1],BIT4) {
				DrawString(SLCT_X0, LOCATE_YT1, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X0, LOCATE_YT1, 1);
			}
			_ifBitSet(_attr[2],BIT4) {
				DrawString(SLCT_X2, LOCATE_YT1, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X2, LOCATE_YT1, 1);
			}
			break;

		case VMIX_TYPE_N32:	
			break;

		case VMIX_TYPE_N33:	// Trun LEFT
			_ifBitSet(_attr[0],BIT4) {
				DrawString(SLCT_X0, LOCATE_YT0, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X0, LOCATE_YT0, 1);
			}
			_ifBitSet(_attr[1],BIT4) {
				DrawString(SLCT_X2, LOCATE_YT0, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X2, LOCATE_YT0, 1);
			}
			_ifBitSet(_attr[2],BIT4) {
				DrawString(SLCT_X2, LOCATE_YT1, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X2, LOCATE_YT1, 1);
			}
			break;

		case VMIX_TYPE_N34:	// Trun RIGHT
			_ifBitSet(_attr[0],BIT4) {
				DrawString(SLCT_X0, LOCATE_YT0, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X0, LOCATE_YT0, 1);
			}
			_ifBitSet(_attr[1],BIT4) {
				DrawString(SLCT_X2, LOCATE_YT0, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X2, LOCATE_YT0, 1);
			}
			_ifBitSet(_attr[2],BIT4) {
				DrawString(SLCT_X0, LOCATE_YT1, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X0, LOCATE_YT1, 1);
			}
			break;

		case VMIX_TYPE_N41:	
			_ifBitSet(_attr[0],BIT4) {
				DrawString(SLCT_X0, LOCATE_YT0, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X0, LOCATE_YT0, 1);
			}
			_ifBitSet(_attr[1],BIT4) {
				DrawString(SLCT_X2, LOCATE_YT0, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X2, LOCATE_YT0, 1);
			}
			_ifBitSet(_attr[2],BIT4) {
				DrawString(SLCT_X0, LOCATE_YT1, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X0, LOCATE_YT1, 1);
			}
			_ifBitSet(_attr[3],BIT4) {
				DrawString(SLCT_X2, LOCATE_YT1, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X2, LOCATE_YT1, 1);
			}
			break;

		// ------------------------------------ PAL ----------------------------------------
		case VMIX_TYPE_P11:	
			_ifBitSet(_attr[0],BIT4) {
				DrawString(SLCT_X1, LOCATE_YT0, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X1, LOCATE_YT0, 1);
			}
			break;

		case VMIX_TYPE_P21:	
			break;

		case VMIX_TYPE_P22:	
			_ifBitSet(_attr[0],BIT4) {
				DrawString(SLCT_X0, LOCATE_YT0, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X0, LOCATE_YT0, 1);
			}
			_ifBitSet(_attr[1],BIT4) {
				DrawString(SLCT_X2, LOCATE_YT0, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X2, LOCATE_YT0, 1);
			}
			break;

		case VMIX_TYPE_P31:	// Trun Back
			_ifBitSet(_attr[0],BIT4) {
				DrawString(SLCT_X1, LOCATE_YT0, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X1, LOCATE_YT0, 1);
			}
			_ifBitSet(_attr[1],BIT4) {
				DrawString(SLCT_X0, LOCATE_YT2, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X0, LOCATE_YT2, 1);
			}
			_ifBitSet(_attr[2],BIT4) {
				DrawString(SLCT_X2, LOCATE_YT2, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X2, LOCATE_YT2, 1);
			}
			break;

		case VMIX_TYPE_P32:	
			break;

		case VMIX_TYPE_P33:	// Trun LEFT
			_ifBitSet(_attr[0],BIT4) {
				DrawString(SLCT_X0, LOCATE_YT0, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X0, LOCATE_YT0, 1);
			}
			_ifBitSet(_attr[1],BIT4) {
				DrawString(SLCT_X2, LOCATE_YT0, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X2, LOCATE_YT0, 1);
			}
			_ifBitSet(_attr[2],BIT4) {
				DrawString(SLCT_X2, LOCATE_YT2, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X2, LOCATE_YT2, 1);
			}
			break;

		case VMIX_TYPE_P34:	// Trun RIGHT
			_ifBitSet(_attr[0],BIT4) {
				DrawString(SLCT_X0, LOCATE_YT0, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X0, LOCATE_YT0, 1);
			}
			_ifBitSet(_attr[1],BIT4) {
				DrawString(SLCT_X2, LOCATE_YT0, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X2, LOCATE_YT0, 1);
			}
			_ifBitSet(_attr[2],BIT4) {
				DrawString(SLCT_X0, LOCATE_YT2, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X0, LOCATE_YT2, 1);
			}
			break;

		case VMIX_TYPE_P41:	
			_ifBitSet(_attr[0],BIT4) {
				DrawString(SLCT_X0, LOCATE_YT0, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X0, LOCATE_YT0, 1);
			}
			_ifBitSet(_attr[1],BIT4) {
				DrawString(SLCT_X2, LOCATE_YT0, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X2, LOCATE_YT0, 1);
			}
			_ifBitSet(_attr[2],BIT4) {
				DrawString(SLCT_X0, LOCATE_YT2, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X0, LOCATE_YT2, 1);
			}
			_ifBitSet(_attr[3],BIT4) {
				DrawString(SLCT_X2, LOCATE_YT2, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X2, LOCATE_YT2, 1);
			}
			break;
	#else
		// ------------------------------------ NTSC ----------------------------------------
		case VMIX_TYPE_N11:	
			ifBitSet(_attr[0],BIT4) {
				DrawString(SLCT_X1, LOCATE_YT0, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X1, LOCATE_YT0, 1);
			}
			break;

		case VMIX_TYPE_N21:	     //andy 980630
			ifBitSet(_attr[0],BIT4) {
				DrawString(SLCT_X1, LOCATE_YT0, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X1, LOCATE_YT0, 1);
			}
			ifBitSet(_attr[0],BIT4) {
				DrawString(SLCT_X1, LOCATE_YT0, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X1, LOCATE_YT1, 1);
			}
			break;

		case VMIX_TYPE_N22:	
			ifBitSet(_attr[0],BIT4) {
				DrawString(SLCT_X0, LOCATE_YT0, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X0, LOCATE_YT0, 1);
			}
			ifBitSet(_attr[1],BIT4) {
				DrawString(SLCT_X2, LOCATE_YT0, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X2, LOCATE_YT0, 1);
			}
			break;

		case VMIX_TYPE_N31:	// Trun Back
			ifBitSet(_attr[0],BIT4) {
				DrawString(SLCT_X1, LOCATE_YT0, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X1, LOCATE_YT0, 1);
			}
			ifBitSet(_attr[1],BIT4) {
				DrawString(SLCT_X0, LOCATE_YT1, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X0, LOCATE_YT1, 1);
			}
			ifBitSet(_attr[2],BIT4) {
				DrawString(SLCT_X2, LOCATE_YT1, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X2, LOCATE_YT1, 1);
			}
			break;

		case VMIX_TYPE_N32:	
			break;

		case VMIX_TYPE_N33:	// Trun LEFT
			ifBitSet(_attr[0],BIT4) {
				DrawString(SLCT_X0, LOCATE_YT0, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X0, LOCATE_YT0, 1);
			}
			ifBitSet(_attr[1],BIT4) {
				DrawString(SLCT_X2, LOCATE_YT0, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X2, LOCATE_YT0, 1);
			}
			ifBitSet(_attr[2],BIT4) {
				DrawString(SLCT_X2, LOCATE_YT1, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X2, LOCATE_YT1, 1);
			}
			break;

		case VMIX_TYPE_N34:	// Trun RIGHT
			ifBitSet(_attr[0],BIT4) {
				DrawString(SLCT_X0, LOCATE_YT0, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X0, LOCATE_YT0, 1);
			}
			ifBitSet(_attr[1],BIT4) {
				DrawString(SLCT_X2, LOCATE_YT0, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X2, LOCATE_YT0, 1);
			}
			ifBitSet(_attr[2],BIT4) {
				DrawString(SLCT_X0, LOCATE_YT1, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X0, LOCATE_YT1, 1);
			}
			break;

		case VMIX_TYPE_N41:	
			ifBitSet(_attr[0],BIT4) {
				DrawString(SLCT_X0, LOCATE_YT0, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X0, LOCATE_YT0, 1);
			}
			ifBitSet(_attr[1],BIT4) {
				DrawString(SLCT_X2, LOCATE_YT0, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X2, LOCATE_YT0, 1);
			}
			ifBitSet(_attr[2],BIT4) {
				DrawString(SLCT_X0, LOCATE_YT1, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X0, LOCATE_YT1, 1);
			}
			ifBitSet(_attr[3],BIT4) {
				DrawString(SLCT_X2, LOCATE_YT1, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X2, LOCATE_YT1, 1);
			}
			break;

		// ------------------------------------ PAL ----------------------------------------
		case VMIX_TYPE_P11:	
			ifBitSet(_attr[0],BIT4) {
				DrawString(SLCT_X1, LOCATE_YT0, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X1, LOCATE_YT0, 1);
			}
			break;

		case VMIX_TYPE_P21:	
			break;

		case VMIX_TYPE_P22:	
			ifBitSet(_attr[0],BIT4) {
				DrawString(SLCT_X0, LOCATE_YT0, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X0, LOCATE_YT0, 1);
			}
			ifBitSet(_attr[1],BIT4) {
				DrawString(SLCT_X2, LOCATE_YT0, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X2, LOCATE_YT0, 1);
			}
			break;

		case VMIX_TYPE_P31:	// Trun Back
			ifBitSet(_attr[0],BIT4) {
				DrawString(SLCT_X1, LOCATE_YT0, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X1, LOCATE_YT0, 1);
			}
			ifBitSet(_attr[1],BIT4) {
				DrawString(SLCT_X0, LOCATE_YT2, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X0, LOCATE_YT2, 1);
			}
			ifBitSet(_attr[2],BIT4) {
				DrawString(SLCT_X2, LOCATE_YT2, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X2, LOCATE_YT2, 1);
			}
			break;

		case VMIX_TYPE_P32:	
			break;

		case VMIX_TYPE_P33:	// Trun LEFT
			ifBitSet(_attr[0],BIT4) {
				DrawString(SLCT_X0, LOCATE_YT0, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X0, LOCATE_YT0, 1);
			}
			ifBitSet(_attr[1],BIT4) {
				DrawString(SLCT_X2, LOCATE_YT0, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X2, LOCATE_YT0, 1);
			}
			ifBitSet(_attr[2],BIT4) {
				DrawString(SLCT_X2, LOCATE_YT2, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X2, LOCATE_YT2, 1);
			}
			break;

		case VMIX_TYPE_P34:	// Trun RIGHT
			ifBitSet(_attr[0],BIT4) {
				DrawString(SLCT_X0, LOCATE_YT0, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X0, LOCATE_YT0, 1);
			}
			ifBitSet(_attr[1],BIT4) {
				DrawString(SLCT_X2, LOCATE_YT0, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X2, LOCATE_YT0, 1);
			}
			ifBitSet(_attr[2],BIT4) {
				DrawString(SLCT_X0, LOCATE_YT2, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X0, LOCATE_YT2, 1);
			}
			break;

		case VMIX_TYPE_P41:	
			ifBitSet(_attr[0],BIT4) {
				DrawString(SLCT_X0, LOCATE_YT0, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X0, LOCATE_YT0, 1);
			}
			ifBitSet(_attr[1],BIT4) {
				DrawString(SLCT_X2, LOCATE_YT0, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X2, LOCATE_YT0, 1);
			}
			ifBitSet(_attr[2],BIT4) {
				DrawString(SLCT_X0, LOCATE_YT2, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X0, LOCATE_YT2, 1);
			}
			ifBitSet(_attr[3],BIT4) {
				DrawString(SLCT_X2, LOCATE_YT2, SPEAKICON);
			} else {
				PCT_ClearWordsPathX(SLCT_X2, LOCATE_YT2, 1);
			}
			break;
	#endif

		default:
			break;
	}
}

#if 0 //Pinchi 20150505 change string to reduce time  //def AWT_NO_SIGNAL_MSG  //Pinchi 20150323 add
//Pinchi 20150422 modify to H center
#define VLS_LCT_XM0	(LOCATE_XM0-4)-8
#define VLS_LCT_XM1	(LOCATE_XM1-4)-8
#define VLS_LCT_XM2	(LOCATE_XM2-4)-8
#else
#define VLS_LCT_XM0	LOCATE_XM0-4
#define VLS_LCT_XM1	LOCATE_XM1-4
#define VLS_LCT_XM2	LOCATE_XM2-4
#endif

#define LOCATE_YM0	7
#define LOCATE_YM1	13
#define LOCATE_YM2	21

#define LOCATE_PYM0	8
#define LOCATE_PYM1	16
#define LOCATE_PYM2	25

//H	#define msgVLOSS "VLoss"
#if 0 //Pinchi 20150505 change string to reduce time  //def AWT_NO_SIGNAL_MSG  //Pinchi 20150323 add
code unsigned char msgVLOSS[]= {0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1c, 0x1d, 0x1e,'\0'};

#define msgCLEAR_W 	15  //Pinchi 20150331 modify for lenghth of NO VIDEO SIGNAL
#else
code unsigned char msgVLOSS[]= {0x0F, 0x10, 0x11, 0x12, 0x12, '\0'};	// VLoss define for HiSharp
//code unsigned char msgVLOSS[]= {'\0'};	// VLoss define for HiSharp		//william-v3.5-971001

#define msgCLEAR_W 	5
#endif


// ===========================================================================
//
// Show VLoss on OSD when Video Signal Loss
//
// ===========================================================================
#ifdef HOLGER
#else
void PCT_ShowVLoss(void)
{
#if 0  //Pinchi 20150325 disable
	data U8 tmpsta;
	tmpsta = SYSVDOSGL^MSGVDOSGL;
#endif

	switch(SYSMIXTYP) {
		// ------------------------------ NTSC ----------------------------
		case VMIX_TYPE_N11:	
			if(MSGVDOSGL&(0x01<<SYSWINLK[0]))
				DrawString(VLS_LCT_XM1, LOCATE_YM1, msgVLOSS) ;
			else
				PCT_ClearWordsPathX(VLS_LCT_XM1, LOCATE_YM1, msgCLEAR_W);
			break;

		case VMIX_TYPE_N21:	
			break;

		case VMIX_TYPE_N22:	
			if(MSGVDOSGL&(0x01<<SYSWINLK[0]))
				DrawString(VLS_LCT_XM0, LOCATE_YM1, msgVLOSS);
			else
				PCT_ClearWordsPathX(VLS_LCT_XM0, LOCATE_YM1, msgCLEAR_W);
			if(MSGVDOSGL&(0x01<<SYSWINLK[1]))
				DrawString(VLS_LCT_XM2, LOCATE_YM1, msgVLOSS);
			else
				PCT_ClearWordsPathX(VLS_LCT_XM2, LOCATE_YM1, msgCLEAR_W);
			break;

		case VMIX_TYPE_N31:	// Trun Back
			if(MSGVDOSGL&(0x01<<SYSWINLK[0]))
				DrawString(VLS_LCT_XM1, LOCATE_YM0, msgVLOSS);
			else
				PCT_ClearWordsPathX(VLS_LCT_XM1, LOCATE_YM0, msgCLEAR_W);
			if(MSGVDOSGL&(0x01<<SYSWINLK[1]))
				DrawString(VLS_LCT_XM0, LOCATE_YM2, msgVLOSS);
			else
				PCT_ClearWordsPathX(VLS_LCT_XM0, LOCATE_YM2, msgCLEAR_W);
			if(MSGVDOSGL&(0x01<<SYSWINLK[2]))
				DrawString(VLS_LCT_XM2, LOCATE_YM2, msgVLOSS);
			else
				PCT_ClearWordsPathX(VLS_LCT_XM2, LOCATE_YM2, msgCLEAR_W);
			break;

		case VMIX_TYPE_N32:	
			break;

		case VMIX_TYPE_N33:	// Trun LEFT
			if(MSGVDOSGL&(0x01<<SYSWINLK[0]))
				DrawString(VLS_LCT_XM0, LOCATE_YM1, msgVLOSS);
			else
				PCT_ClearWordsPathX(VLS_LCT_XM0, LOCATE_YM1, msgCLEAR_W);
			if(MSGVDOSGL&(0x01<<SYSWINLK[1]))
				DrawString(VLS_LCT_XM2, LOCATE_YM0, msgVLOSS);
			else
				PCT_ClearWordsPathX(VLS_LCT_XM2, LOCATE_YM0, msgCLEAR_W);
			if(MSGVDOSGL&(0x01<<SYSWINLK[2]))
				DrawString(VLS_LCT_XM2, LOCATE_YM2, msgVLOSS);
			else
				PCT_ClearWordsPathX(VLS_LCT_XM2, LOCATE_YM2, msgCLEAR_W);
			break;

		case VMIX_TYPE_N34:	// Trun RIGHT
			if(MSGVDOSGL&(0x01<<SYSWINLK[0]))
				DrawString(VLS_LCT_XM0, LOCATE_YM0, msgVLOSS);
			else
				PCT_ClearWordsPathX(VLS_LCT_XM0, LOCATE_YM0, msgCLEAR_W);
			if(MSGVDOSGL&(0x01<<SYSWINLK[1]))
				DrawString(VLS_LCT_XM2, LOCATE_YM1, msgVLOSS);
			else
				PCT_ClearWordsPathX(VLS_LCT_XM2, LOCATE_YM1, msgCLEAR_W);
			if(MSGVDOSGL&(0x01<<SYSWINLK[2]))
				DrawString(VLS_LCT_XM0, LOCATE_YM2, msgVLOSS);
			else
				PCT_ClearWordsPathX(VLS_LCT_XM0, LOCATE_YM2, msgCLEAR_W);
			break;

		case VMIX_TYPE_N41:	
			if(MSGVDOSGL&(0x01<<SYSWINLK[0]))
				DrawString(VLS_LCT_XM0, LOCATE_YM0, msgVLOSS);
			else
				PCT_ClearWordsPathX(VLS_LCT_XM0, LOCATE_YM0, msgCLEAR_W);
			if(MSGVDOSGL&(0x01<<SYSWINLK[1]))
				DrawString(VLS_LCT_XM2, LOCATE_YM0, msgVLOSS);
			else
				PCT_ClearWordsPathX(VLS_LCT_XM2, LOCATE_YM0, msgCLEAR_W);
			if(MSGVDOSGL&(0x01<<SYSWINLK[2]))
				DrawString(VLS_LCT_XM0, LOCATE_YM2, msgVLOSS);
			else
				PCT_ClearWordsPathX(VLS_LCT_XM0, LOCATE_YM2, msgCLEAR_W);
			if(MSGVDOSGL&(0x01<<SYSWINLK[3]))
				DrawString(VLS_LCT_XM2, LOCATE_YM2, msgVLOSS);
			else
				PCT_ClearWordsPathX(VLS_LCT_XM2, LOCATE_YM2, msgCLEAR_W);
			break;

		// ------------------------------ PAL ----------------------------
		case VMIX_TYPE_P11:	
			if(MSGVDOSGL&(0x01<<SYSWINLK[0]))
				DrawString(VLS_LCT_XM1, LOCATE_PYM1, msgVLOSS) ;
			else
				PCT_ClearWordsPathX(VLS_LCT_XM1, LOCATE_PYM1, msgCLEAR_W);
			break;

		case VMIX_TYPE_P21:	
			break;

		case VMIX_TYPE_P22:	
			if(MSGVDOSGL&(0x01<<SYSWINLK[0]))
				DrawString(VLS_LCT_XM0, LOCATE_PYM1, msgVLOSS);
			else
				PCT_ClearWordsPathX(VLS_LCT_XM0, LOCATE_PYM1, msgCLEAR_W);
			if(MSGVDOSGL&(0x01<<SYSWINLK[1]))
				DrawString(VLS_LCT_XM2, LOCATE_PYM1, msgVLOSS);
			else
				PCT_ClearWordsPathX(VLS_LCT_XM2, LOCATE_PYM1, msgCLEAR_W);
			break;

		case VMIX_TYPE_P31:	// Trun Back
			if(MSGVDOSGL&(0x01<<SYSWINLK[0]))
				DrawString(VLS_LCT_XM1, LOCATE_PYM0, msgVLOSS);
			else
				PCT_ClearWordsPathX(VLS_LCT_XM1, LOCATE_PYM0, msgCLEAR_W);
			if(MSGVDOSGL&(0x01<<SYSWINLK[1]))
				DrawString(VLS_LCT_XM0, LOCATE_PYM2, msgVLOSS);
			else
				PCT_ClearWordsPathX(VLS_LCT_XM0, LOCATE_PYM2, msgCLEAR_W);
			if(MSGVDOSGL&(0x01<<SYSWINLK[2]))
				DrawString(VLS_LCT_XM2, LOCATE_PYM2, msgVLOSS);
			else
				PCT_ClearWordsPathX(VLS_LCT_XM2, LOCATE_PYM2, msgCLEAR_W);
			break;

		case VMIX_TYPE_P32:	
			break;

		case VMIX_TYPE_P33:	// Trun LEFT
			if(MSGVDOSGL&(0x01<<SYSWINLK[0]))
				DrawString(VLS_LCT_XM0, LOCATE_YM1, msgVLOSS);
			else
				PCT_ClearWordsPathX(VLS_LCT_XM0, LOCATE_PYM1, msgCLEAR_W);
			if(MSGVDOSGL&(0x01<<SYSWINLK[1]))
				DrawString(VLS_LCT_XM2, LOCATE_PYM0, msgVLOSS);
			else
				PCT_ClearWordsPathX(VLS_LCT_XM2, LOCATE_PYM0, msgCLEAR_W);
			if(MSGVDOSGL&(0x01<<SYSWINLK[2]))
				DrawString(VLS_LCT_XM2, LOCATE_PYM2, msgVLOSS);
			else
				PCT_ClearWordsPathX(VLS_LCT_XM2, LOCATE_PYM2, msgCLEAR_W);
			break;

		case VMIX_TYPE_P34:	// Trun RIGHT
			if(MSGVDOSGL&(0x01<<SYSWINLK[0]))
				DrawString(VLS_LCT_XM0, LOCATE_PYM0, msgVLOSS);
			else
				PCT_ClearWordsPathX(VLS_LCT_XM0, LOCATE_PYM0, msgCLEAR_W);
			if(MSGVDOSGL&(0x01<<SYSWINLK[1]))
				DrawString(VLS_LCT_XM2, LOCATE_PYM1, msgVLOSS);
			else
				PCT_ClearWordsPathX(VLS_LCT_XM2, LOCATE_PYM1, msgCLEAR_W);
			if(MSGVDOSGL&(0x01<<SYSWINLK[2]))
				DrawString(VLS_LCT_XM0, LOCATE_PYM2, msgVLOSS);
			else
				PCT_ClearWordsPathX(VLS_LCT_XM0, LOCATE_PYM2, msgCLEAR_W);
			break;

		case VMIX_TYPE_P41:	
			if(MSGVDOSGL&(0x01<<SYSWINLK[0]))
				DrawString(VLS_LCT_XM0, LOCATE_PYM0, msgVLOSS);
			else
				PCT_ClearWordsPathX(VLS_LCT_XM0, LOCATE_PYM0, msgCLEAR_W);
			if(MSGVDOSGL&(0x01<<SYSWINLK[1]))
				DrawString(VLS_LCT_XM2, LOCATE_PYM0, msgVLOSS);
			else
				PCT_ClearWordsPathX(VLS_LCT_XM2, LOCATE_PYM0, msgCLEAR_W);
			if(MSGVDOSGL&(0x01<<SYSWINLK[2]))
				DrawString(VLS_LCT_XM0, LOCATE_PYM2, msgVLOSS);
			else
				PCT_ClearWordsPathX(VLS_LCT_XM0, LOCATE_PYM2, msgCLEAR_W);
			if(MSGVDOSGL&(0x01<<SYSWINLK[3]))
				DrawString(VLS_LCT_XM2, LOCATE_PYM2, msgVLOSS);
			else
				PCT_ClearWordsPathX(VLS_LCT_XM2, LOCATE_PYM2, msgCLEAR_W);
			break;

		default:
			break;
	}
}
#endif
// ===========================================================================
//
// Show Control Mode OSD 
//
void PCT_ShowModeIcon(void)
{
	PCT_SetOSDDrawPage(WRPHX_PAGE0);
	// Show System Mode 0:S or 1:J
	switch(SYSMODE)
	{
		case JMODE:
			PCT_PreSetBackgroundColor(OSD_COL_BLU);
			PCT_PreSetForegroundColor(OSD_COL_100WHT);
			DrawString(1, 0, JMODEOSD);
			PCT_PreSetBackgroundColor(OSD_COL_CLR);
			break;	

		case SEQMODE:
		 	PCT_PreSetBackgroundColor(OSD_COL_BLU);
			PCT_PreSetForegroundColor(OSD_COL_100WHT);
			DrawString(1, 0, SEQMODEOSD);
			PCT_PreSetBackgroundColor(OSD_COL_CLR);
			break;

		case SMODE:
		 	break;
	}
}

// ===========================================================================
//
// Show Other OSD not Recviver Command in 50msec
//
void PCT_OSDActionForHS(void)
{
	PCT_SetOSDDrawPage(WRPHX_PAGE0);
#ifdef TW2835_FUNC_DEFINE  //Pinchi 20150324 add
	_ifBitSet(SYSWINATTR[0],BIT1)
#else
	ifBitSet(SYSWINATTR[0],BIT1)
#endif
	{
//		PCT_OSD_ActionPthX(SYSWINATTR);
		PCT_ShowMirrorIcon(SYSWINATTR);
		PCT_ShowSpeakIcon(SYSWINATTR);
		PCT_ShowIndicateIcon(SYSWINATTR);
	}
	PCT_EnfalshVLoss();//<960820-william>
	PCT_EnShowOSDPage(WRPHX_PAGE0);
}


// ===========================================================================
// END of File 
// ==========================================================================
