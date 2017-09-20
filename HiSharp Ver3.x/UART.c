//  **************************************************************************
//
//       Copyright (c) 1992-2006 Professonal Computer Technology Co., Ltd
//
//      All rights are reserved. Reproduction in whole or in parts is
//  prohibited without the prior written consent of the copyright owner.
//  --------------------------------------------------------------------------
//
//  Module: UART.C
//
//  Purpose: Implementation of UART.
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
#include "UART.h"
#include "Main.h"

//	------------------------------------
//			Macro Definitions
//	------------------------------------ 


//	------------------------------------
//			Type Definitions
//	------------------------------------


//	------------------------------------
//			Variables Definitions
//	------------------------------------
#define RS_RECV_MAX_BUFF 80
	
BYTE RS_RECVBUF[RS_RECV_MAX_BUFF];
BYTE RsRxRp,RsRxWp;


//	------------------------------------
//			Function Prototypes
//	------------------------------------

// ===========================================================================
//                      Parallel function description
// ===========================================================================
//
//		Initial UART  												   
//
void InitialUART (void)
{
	// Useing Interrupt RS
	PS=1;
	ES=1;

//	// Useing Interrupt Timer1
//	PT1=1;
//	ET1=1;

#if (TW2835_MCU == TW8816_MODEL_MEGAWIN)  //Pinchi 20150323 add
	TH1 = 0xf4; 				// 24M HZ
#elif (TW2835_MCU == TW8806_MODEL_WINBOND)
	TH1 = B9600;				// 40M HZ
#else
	TH1 = SET_BAUDRATE(9600);	// 22.118M HZ
#endif

	TR1 = 1; 					// Start timer 1

	RsRxRp = 0;
	RsRxWp = 0;
}

// ===========================================================================
//
//		Serial RX Check 												   
//
BYTE RS_RxReady (void)
{
	if( RsRxWp == RsRxRp ) return false;
	else return true;
}

//=============================================================================
//
//		Serial RX														   
//
BYTE RS_rx (void)
{
	register BYTE	ret;
		
	ES = 0;
	//Kane @HS 2007 0809 Ver3.5
	//if(RS_RECVBUF[RsRxRp+3]=='T' && RS_RECVBUF[RsRxRp+2]=='W' && RS_RECVBUF[RsRxRp+1]=='3'  && RS_RECVBUF[RsRxRp]=='T' )
	//	return TWCMD;
	ret = RS_RECVBUF[RsRxRp];
	RsRxRp++;
	if(RsRxRp >= RS_RECV_MAX_BUFF) 
		RsRxRp = 0;
	ES = 1;

	return ret;
}

//=============================================================================
//
//		Serial TX														   
//
void RS_tx (BYTE tx_buf)
{
	while(1) {
		if(TI) {
			SBUF = tx_buf;
			TI = 0;
			break;
		}
	}
}

// ===========================================================================
//
//		Serial Interrupt
//
void RS_interrupt(void) interrupt 4 using 1
{
	if( RI ) {					//--- Receive interrupt ----
		RI = 0;

		#if 1//ryan@20170914

		RS_RECVBUF[RsRxWp] = SBUF;
		RsRxWp++;
		if( RsRxWp >= RS_RECV_MAX_BUFF ) RsRxWp = 0;

		#else
		if(RsRxWp+1==RsRxRp) RsRxRp++;
		if(RsRxWp==RS_RECV_MAX_BUFF-1 && RsRxRp==0) RsRxRp++;
		if( RsRxRp >= RS_RECV_MAX_BUFF ) RsRxRp = 0;

		RS_RECVBUF[RsRxWp] = SBUF;
		RsRxWp++;
		if( RsRxWp >= RS_RECV_MAX_BUFF ) RsRxWp = 0;
		#endif
		
	}
}

// ===========================================================================
// END of File 
// ===========================================================================

