//  **************************************************************************
//
//       Copyright (c) 1992-2006 Professonal Computer Technology Co., Ltd
//
//      All rights are reserved. Reproduction in whole or in parts is
//  prohibited without the prior written consent of the copyright owner.
//  --------------------------------------------------------------------------
//
//  Module: TW28xx_Video.C
//
//  Purpose: Implementation of TW28xx Video.
//
//  Version: 0.01                                   2006/12/11 08:22¤U¤È
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
//	R0.01 2006/12/11 08:22¤U¤È Phoenix Chuang
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
#include "BusCtrl.h"
#include "CommandShell.h"
#include "Win_Table.h"
#include "Timer.h"//andy 20100209 add
#include "TW2835_Init.h"
#include "Main.h"

//	------------------------------------
//			Macro Definitions
//	------------------------------------ 
#define H_FILTER	0x0000

//	------------------------------------
//			Type Definitions
//	------------------------------------


//	------------------------------------
//			Variables Definitions
//	------------------------------------
code U16 XWinAttr_RegAddr[]	= {0x0111, 0x0119, 0x0121, 0x0129, 
							   0x0114, 0x011C, 0x0124, 0x012C };

code U16 XWinPOP_RegAddr[]	= {0x0110, 0x0118, 0x0120, 0x0128, 
							   0x0113, 0x011B, 0x0123, 0x012B };

code U16 YWinAttr_RegAddr[]	= {0x0161, 0x0164, 0x0167, 0x016A};


extern BYTE xdata Original_selwintype;//Kane @HS 2007 0724 Ver3.4

extern BYTE TW2837IDCheck;

//	------------------------------------
//			Function Prototypes
//	------------------------------------

// ===========================================================================
//                      Parallel function description
// ===========================================================================
//
// Auto Detectation Video Format 
//
U8 PCT_DetectVideoFormat(U8 _ch)
{
	register U8 tmpSta;
//	int _delay;
	// Waitting Color Lock
	//Kane Modified>>>>
#if 1
	tmpSta = 0; 

	if(TW2837IDCheck==TRUE)
		{
	if( (TW28_ReadByte(0, SENSORCHANNEL<<4)&0xC0) == 0x40) 
		{
		tmpSta = TW28_ReadByte(0, (_ch << 4)|0x0E);
		}

	if(tmpSta == 0)
		return NONE_SYSTEM;

	tmpSta &= 0x70;
	tmpSta >>= 4;

	if((tmpSta==0)||(tmpSta==3))
		{
		return NTSC;
		}
	else
		{
		return PAL;
			}
	
	//return ((tmpSta==0)||(tmpSta==3))  ? NTSC: PAL; 
		}
	else
		{
		if( (TW28_ReadByte(0, SENSORCHANNEL<<4)&0x0F) == 0x0F) 
			tmpSta = TW28_ReadByte(0, _ch << 4);
		
		if(tmpSta == 0)
			return NONE_SYSTEM;
		
		tmpSta &= 0xE0;
		tmpSta >>= 5;
		return (tmpSta>3)  ? NTSC: PAL; 

		}
#else
//	DELAY_FOR(150);
	tmpSta = TW28_ReadByte(0, _ch << 4);
	if( 0x0F != (tmpSta & 0x0F))
		return DEF_SYSTEM;
	tmpSta &= 0xE0;
	tmpSta >>= 5;
	return (tmpSta>3)  ? NTSC: PAL; 
#endif//if 0
	//Kane Modified<<<<
}

// ===========================================================================
//
// Setting Video Format 
//
void PCT_SetVideoFormat(U8 _dvc, U8 _ch, U8 _fmat)
{
	register U8 tmpSta, addr;
	
	_dvc = 0;
	addr = _ch << 4 | 0x01;
	tmpSta = TW28_ReadByte(0, addr);
	//Kane modified>>>>
	//tmpSta &= ~VIDEO_ADDR;
	tmpSta &= 0x8F;
	// Kane modified<<<<
	tmpSta |= _fmat;
	TW28_WriteByte(0, addr, tmpSta);
}

// ===========================================================================
//
// About X channel Video Mixing Control 
//

// Video Scale Setting
void PCT_SetChanelScale(U8 _ch, WRITE_REG_DATA *datptr)
{
	code U8 ScaleRgeAddr[]={0x83,0x84,0x81,0x82,
							0x93,0x94,0x91,0x92,
							0xA3,0xA4,0xA1,0xA2,
							0xB3,0xB4,0xB1,0xB2,
	};
	U8	*addrptr;
	register U16 value;

	#define HB GETHBYTE(value)
	#define LB GETLBYTE(value)
	
	addrptr = ScaleRgeAddr+_ch*4;
	value = datptr->addr;
	if(value != 0xFFFF) value += H_FILTER;
	TW28_WriteByte(0, *addrptr++, HB);
	TW28_WriteByte(0, *addrptr++, LB);
	datptr++;
	value = datptr->addr;
	TW28_WriteByte(0, *addrptr++, HB);
	TW28_WriteByte(0, *addrptr++, LB);
}

// Video scale Check 
void PCT_SetVideoHDelay(U8 _typ, PU8 _winch, PU8 _cattr)
{
	register U8 hdelay;
//Kane @HS 2007 0806 Ver3.4>>>>
//	if(Original_selwintype == _typ )//Kane @HS 2007 0724 Ver3.4
//		return;
////Kane @HS 2007 0806 Ver3.4<<<<
	BYTE* ptr_Video_HDelay;

if(TW2837IDCheck==TRUE)
	ptr_Video_HDelay=&Video_HDelay37[0];
else
	ptr_Video_HDelay=&Video_HDelay[0];

	switch(_typ){
		case VMIX_TYPE_N11:
		case VMIX_TYPE_P11:
		//Kane @HS 2007 0806 Ver3.4>>>>	
			//if(Original_selwintype == _typ)//Kane @HS 2007 0724 Ver3.4
			//break;
		//Kane @HS 2007 0806 Ver3.4<<<<
			hdelay = 0x08|SYSTYPE;
			hdelay |= (_cattr[0]&0x01)<<1;
			if(_winch[0]&0x01)
				hdelay |= WIN_RIGHT;	// Signal Channel 1,3
			else
				hdelay |= WIN_LEFT;		// Signal Channel 0,2
			if(TW28_ReadByte(0, (_winch[0]<<4)|0x02) != ptr_Video_HDelay[hdelay])//Kane @HS 2007 0808 Ver3.4
				TW28_WriteByte(0, (_winch[0]<<4)|0x02,ptr_Video_HDelay[hdelay]);
			break;

		case VMIX_TYPE_N21://andy
		case VMIX_TYPE_P21:
			// Type N,L,R
			hdelay = 0x08|WIN_RIGHT|SYSTYPE;	// WIN_RIGHT for Y Channel LEFT
			hdelay |= (_cattr[0]&0x01)<<1;
			if(TW28_ReadByte(0, (_winch[0]<<4)|0x02) != ptr_Video_HDelay[hdelay])//Kane @HS 2007 0808 Ver3.4
				TW28_WriteByte(0, (_winch[0]<<4)|0x02,ptr_Video_HDelay[hdelay]);
			// LEFT 
			hdelay = 0x08|WIN_LEFT|SYSTYPE;	// WIN_RIGHT for Y Channel LEFT
			hdelay |= (_cattr[1]&0x01)<<1;
			if(TW28_ReadByte(0, (_winch[1]<<4)|0x02) != ptr_Video_HDelay[hdelay])//Kane @HS 2007 0808 Ver3.4
				TW28_WriteByte(0, (_winch[1]<<4)|0x02,ptr_Video_HDelay[hdelay]);
			
			break;

		case VMIX_TYPE_N22:
		case VMIX_TYPE_P22:
			// LEFT 
			hdelay = WIN_LEFT|SYSTYPE;
			hdelay |= (_cattr[0]&0x01)<<1;
			if(TW28_ReadByte(0,( _winch[0]<<4)|0x02) != ptr_Video_HDelay[hdelay])//Kane @HS 2007 0808 Ver3.4
				TW28_WriteByte(0, (_winch[0]<<4)|0x02,ptr_Video_HDelay[hdelay]);
			// RIGHT
			hdelay = WIN_RIGHT|SYSTYPE;
			hdelay |= (_cattr[1]&0x01)<<1;
			if(TW28_ReadByte(0, (_winch[1]<<4)|0x02) != ptr_Video_HDelay[hdelay])//Kane @HS 2007 0808 Ver3.4
				TW28_WriteByte(0, (_winch[1]<<4)|0x02,ptr_Video_HDelay[hdelay]);
			break;
			
		case VMIX_TYPE_N31:
		case VMIX_TYPE_P31:
			// Type N,L,R
			hdelay = 0x08|WIN_RIGHT|SYSTYPE;	// WIN_RIGHT for Y Channel LEFT
			hdelay |= (_cattr[0]&0x01)<<1;
			if(TW28_ReadByte(0, (_winch[0]<<4)|0x02) != ptr_Video_HDelay[hdelay])//Kane @HS 2007 0808 Ver3.4
				TW28_WriteByte(0, (_winch[0]<<4)|0x02,ptr_Video_HDelay[hdelay]);
			// LEFT 
			hdelay = WIN_LEFT|SYSTYPE;
			hdelay |= (_cattr[1]&0x01)<<1;
			if(TW28_ReadByte(0, (_winch[1]<<4)|0x02) != ptr_Video_HDelay[hdelay])//Kane @HS 2007 0808 Ver3.4
				TW28_WriteByte(0, (_winch[1]<<4)|0x02,ptr_Video_HDelay[hdelay]);
			// RIGHT
			hdelay = WIN_RIGHT|SYSTYPE;
			hdelay |= (_cattr[2]&0x01)<<1;
			if(TW28_ReadByte(0, (_winch[2]<<4)|0x02) != ptr_Video_HDelay[hdelay])//Kane @HS 2007 0808 Ver3.4
				TW28_WriteByte(0, (_winch[2]<<4)|0x02,ptr_Video_HDelay[hdelay]);
			break;

		case VMIX_TYPE_N32:
		case VMIX_TYPE_P32:
			break;

		case VMIX_TYPE_N33:
		case VMIX_TYPE_P33:
			// Type L,R,R
			// LEFT 
			hdelay = WIN_LEFT|SYSTYPE;
			hdelay |= (_cattr[0]&0x01)<<1;
			if(TW28_ReadByte(0, (_winch[0]<<4)|0x02) != ptr_Video_HDelay[hdelay])//Kane @HS 2007 0808 Ver3.4
				TW28_WriteByte(0, (_winch[0]<<4)|0x02,ptr_Video_HDelay[hdelay]);
			// RIGHT
			hdelay = WIN_RIGHT|SYSTYPE;
			hdelay |= (_cattr[1]&0x01)<<1;
			if(TW28_ReadByte(0, (_winch[1]<<4)|0x02) != ptr_Video_HDelay[hdelay])//Kane @HS 2007 0808 Ver3.4
				TW28_WriteByte(0, (_winch[1]<<4)|0x02,ptr_Video_HDelay[hdelay]);
			// RIGHT
			hdelay = WIN_RIGHT|SYSTYPE;
			hdelay |= (_cattr[2]&0x01)<<1;
			if(TW28_ReadByte(0,( _winch[2]<<4)|0x02) != ptr_Video_HDelay[hdelay])//Kane @HS 2007 0808 Ver3.4
			TW28_WriteByte(0, (_winch[2]<<4)|0x02,ptr_Video_HDelay[hdelay]);
			break;

		case VMIX_TYPE_N34:
		case VMIX_TYPE_P34:
			// Type L,R,L
			// LEFT 
			hdelay = WIN_LEFT|SYSTYPE;
			hdelay |= (_cattr[0]&0x01)<<1;
			if(TW28_ReadByte(0, (_winch[0]<<4)|0x02) != ptr_Video_HDelay[hdelay])//Kane @HS 2007 0808 Ver3.4
				TW28_WriteByte(0, (_winch[0]<<4)|0x02,ptr_Video_HDelay[hdelay]);
			// RIGHT
			hdelay = WIN_RIGHT|SYSTYPE;
			hdelay |= (_cattr[1]&0x01)<<1;
			if(TW28_ReadByte(0, (_winch[1]<<4)|0x02) != ptr_Video_HDelay[hdelay])//Kane @HS 2007 0808 Ver3.4
				TW28_WriteByte(0, (_winch[1]<<4)|0x02,ptr_Video_HDelay[hdelay]);
			//Left
			hdelay = WIN_LEFT|SYSTYPE;
			hdelay |= (_cattr[2]&0x01)<<1;
			if(TW28_ReadByte(0, (_winch[2]<<4)|0x02) != ptr_Video_HDelay[hdelay])//Kane @HS 2007 0808 Ver3.4
				TW28_WriteByte(0, (_winch[2]<<4)|0x02,ptr_Video_HDelay[hdelay]);
			break;
			
		case VMIX_TYPE_N41:
		case VMIX_TYPE_P41:
			// Type L,R,L,R
			// LEFT 
			hdelay = WIN_LEFT|SYSTYPE;
			hdelay |= (_cattr[0]&0x01)<<1;
			if(TW28_ReadByte(0, (_winch[0]<<4)|0x02) != ptr_Video_HDelay[hdelay])//Kane @HS 2007 0808 Ver3.4
				TW28_WriteByte(0, (_winch[0]<<4)|0x02,ptr_Video_HDelay[hdelay]);
			// RIGHT
			hdelay = WIN_RIGHT|SYSTYPE;
			hdelay |= (_cattr[1]&0x01)<<1;
			if(TW28_ReadByte(0,( _winch[1]<<4)|0x02) != ptr_Video_HDelay[hdelay])//Kane @HS 2007 0808 Ver3.4
				TW28_WriteByte(0, (_winch[1]<<4)|0x02,ptr_Video_HDelay[hdelay]);
			// Left
			hdelay = WIN_LEFT|SYSTYPE;
			hdelay |= (_cattr[2]&0x01)<<1;
			if(TW28_ReadByte(0, (_winch[2]<<4)|0x02) != ptr_Video_HDelay[hdelay])//Kane @HS 2007 0808 Ver3.4
				TW28_WriteByte(0, (_winch[2]<<4)|0x02,ptr_Video_HDelay[hdelay]);
			// RIGHT
			hdelay = WIN_RIGHT|SYSTYPE;
			hdelay |= (_cattr[3]&0x01)<<1;
			if(TW28_ReadByte(0, (_winch[3]<<4)|0x02) != ptr_Video_HDelay[hdelay])//Kane @HS 2007 0808 Ver3.4
				TW28_WriteByte(0, (_winch[3]<<4)|0x02,ptr_Video_HDelay[hdelay]);
			break;

		default :
			break;
	}
}

// X Channel Video Mixing Control
void PCT_SetXVideoMixing(U8 _typ, PU8 _winch)
{
	WRITE_REG_DATA *wregptr;

	TW28_WriteByte(1, 0x10, (_winch[0]&0x03)|0x80);
	TW28_WriteByte(1, 0x18, (_winch[1]&0x03)|0x80);
	TW28_WriteByte(1, 0x20, (_winch[2]&0x03)|0x80);
	TW28_WriteByte(1, 0x28, (_winch[3]&0x03)|0x80);

	switch(_typ){
		case VMIX_TYPE_N11:
		case VMIX_TYPE_P11:
			//if(Original_selwintype == _typ)//Kane @HS 2007 0724 Ver3.4
			//break;

			wregptr = Init_Vido_W1+SYSTYPE*19;
			PCT_SetChanelScale(_winch[0], wregptr);
			TW28_WriteSTable(0, wregptr+2);
			break;

		case VMIX_TYPE_N21:
		case VMIX_TYPE_N22:
		case VMIX_TYPE_P21:
		case VMIX_TYPE_P22:
			wregptr = Init_Vido_W2+SYSTYPE*TYPE2_OFSET*2;
			wregptr += ((_typ&0x0F)-1)*TYPE2_OFSET;

			PCT_SetChanelScale(_winch[0], wregptr);
			PCT_SetChanelScale(_winch[1], wregptr);
			TW28_WriteSTable(0, wregptr+2);
			break;

		case VMIX_TYPE_N31:
		case VMIX_TYPE_N32:
		case VMIX_TYPE_N33:
		case VMIX_TYPE_N34:
		case VMIX_TYPE_P31:
		case VMIX_TYPE_P32:
		case VMIX_TYPE_P33:
		case VMIX_TYPE_P34:
			wregptr = Init_Vido_W3+SYSTYPE*TYPE3_OFSET*4;
			wregptr += ((_typ&0x0F)-1)*TYPE3_OFSET;

			PCT_SetChanelScale(_winch[0], wregptr+0);
			PCT_SetChanelScale(_winch[1], wregptr+2);
			PCT_SetChanelScale(_winch[2], wregptr+4);
			TW28_WriteSTable(0, wregptr+6);
			break;

		case VMIX_TYPE_N41:
		case VMIX_TYPE_P41:
			wregptr = Init_Vido_W4+SYSTYPE*19;
			PCT_SetChanelScale(_winch[0], wregptr);
			PCT_SetChanelScale(_winch[1], wregptr);
			PCT_SetChanelScale(_winch[2], wregptr);
			PCT_SetChanelScale(_winch[3], wregptr);
			TW28_WriteSTable(0, wregptr+2);
			break;

		default :
			break;
	}
}

// ===========================================================================
//
// About Y channel Video Mixing Control 
//
void PCT_SetYVideoMixing(U8 _typ)
{
	TW28_WriteSTable(0, Init_Vido_Y + _typ * YTYPE_OFSET);
}

// About Y channel Video Hdelay 
void PCT_RecompenseYHdelay (PU8 _chmiro)
{
	switch(TW28_ReadByte(0x01, 0x6C)){
	case 0x00:
		
		if(TW28_ReadByte(0, 0x02) != Video_HDelay[WIN_LEFT+((_chmiro[0]&BIT0)<<1)+SYSTYPE])//Kane @HS 2007 0808 Ver3.4
			TW28_WriteByte(0x00, 0x02, Video_HDelay[WIN_LEFT+((_chmiro[0]&BIT0)<<1)+SYSTYPE]);
		if(TW28_ReadByte(0, 0x12) != Video_HDelay[WIN_RIGHT+((_chmiro[1]&BIT0)<<1)+SYSTYPE])//Kane @HS 2007 0808 Ver3.4
			TW28_WriteByte(0x00, 0x12, Video_HDelay[WIN_RIGHT+((_chmiro[1]&BIT0)<<1)+SYSTYPE]);
		if(TW28_ReadByte(0, 0x22) != Video_HDelay[WIN_LEFT+((_chmiro[2]&BIT0)<<1)+SYSTYPE])//Kane @HS 2007 0808 Ver3.4
			TW28_WriteByte(0x00, 0x22, Video_HDelay[WIN_LEFT+((_chmiro[2]&BIT0)<<1)+SYSTYPE]);
		if(TW28_ReadByte(0, 0x32) != Video_HDelay[WIN_RIGHT+((_chmiro[3]&BIT0)<<1)+SYSTYPE])//Kane @HS 2007 0808 Ver3.4
			TW28_WriteByte(0x00, 0x32, Video_HDelay[WIN_RIGHT+((_chmiro[3]&BIT0)<<1)+SYSTYPE]);
		break;

	case 0x03:
		if(TW28_ReadByte(0, 0x02) != Video_HDelay[0x08+((_chmiro[0]&BIT0)<<1)+SYSTYPE])//William @HS 2007 0829 Ver3.4
			TW28_WriteByte(0x00, 0x02, Video_HDelay[0x08+((_chmiro[0]&BIT0)<<1)+SYSTYPE]);
		break;
		
	case 0x0C:
		if(TW28_ReadByte(0, 0x12) != Video_HDelay[0x08+((_chmiro[1]&BIT0)<<1)+SYSTYPE])//William @HS 2007 0829 Ver3.4
			TW28_WriteByte(0x00, 0x12, Video_HDelay[0x08+((_chmiro[1]&BIT0)<<1)+SYSTYPE]);
		break;
		
	case 0x30:
		if(TW28_ReadByte(0, 0x22) != Video_HDelay[0x08+((_chmiro[2]&BIT0)<<1)+SYSTYPE])//William @HS 2007 0829 Ver3.4
		TW28_WriteByte(0x00, 0x22, Video_HDelay[0x08+((_chmiro[2]&BIT0)<<1)+SYSTYPE]);
		break;
		
	case 0xC0:
		if(TW28_ReadByte(0, 0x32) !=Video_HDelay[0x08+((_chmiro[3]&BIT0)<<1)+SYSTYPE])//William @HS 2007 0829 Ver3.4
		TW28_WriteByte(0x00, 0x32, Video_HDelay[0x08+((_chmiro[3]&BIT0)<<1)+SYSTYPE]);
		break;
	}
}

// ===========================================================================
//
//	TW2835 Video Mixing last Modify for AC & RB
//
//Kane @HS 2007 0808 Ver3.4>>>>
#if 0  //Pinchi 20150324 disable for compiler warning
void PCT_VideoLastModify(void)
{
	register data U8 state=0;
	
	state += (SYSWINLK[0]&0x03);
	state += (SYSWINLK[1]&0x03)<<4;
	state += (SYSWINATTR[0]&BIT0)<<2;
	state += (SYSWINATTR[1]&BIT0)<<6;

	switch(state) {
		case 0x20:
		case 0x24:
			TW28_WriteSTable(0, VidoW2_ModifyACNM);
			break;

		case 0x60:
		case 0x64:
			//PCT_CheckSystem();			
			if((SYSTYPE&BIT0) ==NTSC)//Kane @HS 2007 0813 Cer3.4
				TW28_WriteSTable(0, VidoW2_ModifyACHM);
			else
				TW28_WriteSTable(0, VidoW2_ModifyACHM_PAL);
			break;

		case 0x13:
		case 0x53:
			PCT_WinPOPupCtrl(1);
			TW28_WriteSTable(0, VidoW2_ModifyRBNM);
			break;
		case 0x17:
		case 0x57:
			PCT_WinPOPupCtrl(1);
			TW28_WriteSTable(0, VidoW2_ModifyRBHM);
			break;
	}
}
#endif

//Kane @HS 2007 0808 Ver3.4<<<<
// ===========================================================================
//
//	TW2835 Attribute Set about Freeze for X Channel		 												   
//
void PCT_WinAttrCtrl(U8 _wid, U8 _attrsel, U8 _setval)
{
	#define PAGE GETHBYTE(XWinAttr_RegAddr[_wid])
	#define ADDR GETLBYTE(XWinAttr_RegAddr[_wid])

	register U8 dat;

	dat = TW28_ReadByte(PAGE, ADDR);
	_setval ? dat |= _attrsel : (dat &= ~_attrsel);
	TW28_WriteByte(PAGE, ADDR, dat);
}

// ===========================================================================
//
//	TW2835 Attribute Set about Freeze for X Channel		 												   
//
//extern void PutsP(BYTE * ptr);
//extern void RS_tx(BYTE tx_buf);
void PCT_WinAttrCtrlY(U8 _wid, U8 _attrsel, U8 _setval)
{
	#define YPAGE GETHBYTE(YWinAttr_RegAddr[_wid])
	#define YADDR GETLBYTE(YWinAttr_RegAddr[_wid])
	register U8 dat;
	
	dat = TW28_ReadByte(YPAGE, YADDR);
	_setval ? dat |= _attrsel : (dat &= ~_attrsel);
	TW28_WriteByte(YPAGE, YADDR, dat);


}

// ===========================================================================
//
//	TW2835 Attribute Set about Freeze		 												   
//
void PCT_WinAttrClear(U8 _attrsel)
{
	#define PAGE GETHBYTE(XWinAttr_RegAddr[_wid])
	#define ADDR GETLBYTE(XWinAttr_RegAddr[_wid])

	register  U8 _wid;
	register  U8 dat;

	for(_wid=0; _wid<8; _wid++) {
		dat = TW28_ReadByte(PAGE, ADDR);
		dat &= ~_attrsel;
		TW28_WriteByte(PAGE, ADDR, dat);
	}
}

// ===========================================================================
//
// TW2835 Window POP UP 
//
#if 0  //Pinchi 20150324 disable for compiler warning
void PCT_WinPOPupCtrl(U8 _wid)
{
	#define POPPAGE GETHBYTE(XWinPOP_RegAddr[_wid])
	#define POPADDR GETLBYTE(XWinPOP_RegAddr[_wid])

	register  U8 dat;

	dat = TW28_ReadByte(POPPAGE, POPADDR);
	dat |= BIT6;
	TW28_WriteByte(POPPAGE, POPADDR, dat);
}
#endif

// ===========================================================================
// END of File 
// ===========================================================================

