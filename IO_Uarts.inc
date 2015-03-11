;***************************************************************************
;* Uarts Macro Driver
;*
;* File Name            :"UartsDriver_Macro.asm"
;* Title                : Uarts Macro Driver
;* Date                 : 2.09.2009
;* Version              : 1.0;First released
;* Target MCU           : All
;* AUTHOR		        : Gheorghiu Iulian
;* 			 Romania
;* 			 morgoth2600@gmail.com
;* 			 http://sites.google.com/site/asmatmegaprograming/
;* 			 http://avrdevboardshop.hostzi.com/
;*
;* DESCRIPTION:
;*  This is a driver for working with all Uarts from one ATmega Microcontroller
;*
;***************************************************************************
;User definitions:
;True
;False
;Null
;Tx_Rx_Disabled
;Tx_Enabled
;Rx_Enabled
;Tx_Rx_Enabled
;Tx_Rx_Udre_Int_Disabled
;Tx_Int_Enabled
;Rx_Int_Enabled
;Tx_Rx_Int_Enabled
;Udre_Int_Enabled
;Tx_Udre_Int_Enabled
;Rx_Udre_Int_Enabled
;Tx_Rx_Udre_Int_Enabled
;Even_Parity
;Odd_Parity
;***************************************************************************
;User macros Uart0
;Inline_Uart0Setup True,19200,Tx_Rx_Disabled,Tx_Rx_Udre_Int_Disabled,8,False,1,False,False
;Inline_Uart0Baut BautRate
;Inline_Uart0U2xEnable True or False
;Inline_Uart0BautU2x BautRate
;Inline_Uart0BitsNr BitsNumber(5,6,7,8 or 9)
;Inline_Uart0Parity True or False
;Inline_Uart0StopBits StopBitsNumber(1 or 2)
;Inline_Uart0SincEnable True or False
;Inline_Uart0MultiprocesorEnable True or False
;Inline_Uart0RxIntEnable True or False
;Inline_Uart0TxIntEnable True or False
;Inline_Uart0UdreIntEnable True or False
;Inline_Uart0TxEnable True or False
;Inline_Uart0RxEnable True or False
;Inline_Uart0SendRegChar R1
;Inline_Uart0SendConstChar 1 (Constant)
;Inline_Uart0ReceiveChar R16
;Inline_Uart0FlashConstStrSend MsgFlash (Constant)
;Inline_Uart0RamConstStrSend MsgRam (Constant)
;Inline_Uart0RamVarStrSend X,Y or Z
;Inline_Uart0ForceReceiveChar R16;Flag T = 0 if char not received
;Inline_Uart0StrSend Constant string to be sended (max 256Bytes)
;User macros Uart1
;Inline_Uart1Setup True,19200,Tx_Rx_Disabled,Tx_Rx_Udre_Int_Disabled,8,False,1,False,False
;Inline_Uart1Baut BautRate
;Inline_Uart1U2xEnable True or False
;Inline_Uart1BautU2x BautRate
;Inline_Uart1BitsNr BitsNumber(5,6,7,8 or 9)
;Inline_Uart1Parity True or False
;Inline_Uart1StopBits StopBitsNumber(1 or 2)
;Inline_Uart1SincEnable True or False
;Inline_Uart1MultiprocesorEnable True or False
;Inline_Uart1RxIntEnable True or False
;Inline_Uart1TxIntEnable True or False
;Inline_Uart1UdreIntEnable True or False
;Inline_Uart1TxEnable True or False
;Inline_Uart1RxEnable True or False
;Inline_Uart1SendRegChar R1
;Inline_Uart1SendConstChar 1 (Constant)
;Inline_Uart1ReceiveChar R16
;Inline_Uart1FlashConstStrSend MsgFlash (Constant)
;Inline_Uart1RamConstStrSend MsgRam (Constant)
;Inline_Uart1RamVarStrSend X,Y or Z
;Inline_Uart1ForceReceiveChar R16;Flag T = 0 if char not received
;Inline_Uart1StrSend Constant string to be sended (max 256Bytes)
;User macros Uart2
;Inline_Uart2Setup True,19200,Tx_Rx_Disabled,Tx_Rx_Udre_Int_Disabled,8,False,1,False,False
;Inline_Uart2Baut BautRate
;Inline_Uart2U2xEnable True or False
;Inline_Uart2BautU2x BautRate
;Inline_Uart2BitsNr BitsNumber(5,6,7,8 or 9)
;Inline_Uart2Parity True or False
;Inline_Uart2StopBits StopBitsNumber(1 or 2)
;Inline_Uart2SincEnable True or False
;Inline_Uart2MultiprocesorEnable True or False
;Inline_Uart2RxIntEnable True or False
;Inline_Uart2TxIntEnable True or False
;Inline_Uart2UdreIntEnable True or False
;Inline_Uart2TxEnable True or False
;Inline_Uart2RxEnable True or False
;Inline_Uart2SendRegChar R1
;Inline_Uart2SendConstChar 1 (Constant)
;Inline_Uart2ReceiveChar R16
;Inline_Uart2FlashConstStrSend MsgFlash (Constant)
;Inline_Uart2RamConstStrSend MsgRam (Constant)
;Inline_Uart2RamVarStrSend X,Y or Z
;Inline_Uart2ForceReceiveChar R16;Flag T = 0 if char not received
;Inline_Uart2StrSend Constant string to be sended (max 256Bytes)
;User macros Uart3
;Inline_Uart3Setup True,19200,Tx_Rx_Disabled,Tx_Rx_Udre_Int_Disabled,8,False,1,False,False
;Inline_Uart3Baut BautRate
;Inline_Uart3U2xEnable True or False
;Inline_Uart3BautU2x BautRate
;Inline_Uart3BitsNr BitsNumber(5,6,7,8 or 9)
;Inline_Uart3Parity True or False
;Inline_Uart3StopBits StopBitsNumber(1 or 2)
;Inline_Uart3SincEnable True or False
;Inline_Uart3MultiprocesorEnable True or False
;Inline_Uart3RxIntEnable True or False
;Inline_Uart3TxIntEnable True or False
;Inline_Uart3UdreIntEnable True or False
;Inline_Uart3TxEnable True or False
;Inline_Uart3RxEnable True or False
;Inline_Uart3SendRegChar R1
;Inline_Uart3SendConstChar 1 (Constant)
;Inline_Uart3ReceiveChar R16
;Inline_Uart3FlashConstStrSend MsgFlash (Constant)
;Inline_Uart3RamConstStrSend MsgRam (Constant)
;Inline_Uart3RamVarStrSend X,Y or Z
;Inline_Uart3ForceReceiveChar R16;Flag T = 0 if char not received
;Inline_Uart3StrSend Constant string to be sended (max 256Bytes)
	//Rjmp DefaultSetupDriverUart
;********************************************************************************************************************************************************
#ifndef __IO_Uarts_Macro__
#define __IO_Uarts_Macro__
#define __IO_UartsAsm__
#ifndef __DocMessages_IO_Uarts_Macro__
#define _DocMessages_IO_Uarts_Macro_
#ifndef __DocMessages_IO_Uarts_Macro__
#message "************To see libraries documentation for IO_Uarts_Macro, type: #define __DocMessages_IO_Uarts_Macro__"
#endif
#endif
;********************************************************************************************************************************************************
#ifndef CoreFrequ
#error "(CoreFrequ): Not defined"
#else
#if defined(_M8HVADEF_INC_)||defined(_M16M1DEF_INC_)||defined(_M16HVADEF_INC_)||defined(_M32M1DEF_INC_)||defined(_M32C1DEF_INC_)||defined(_M32HVBDEF_INC_)||defined(_M406DEF_INC_)||defined(_M64M1DEF_INC_)||defined(_M64C1DEF_INC_)||defined(_USB82DEF_INC_)||defined(_USB162DEF_INC_)||defined(_AT86RF401DEF_INC_)
#warning "No uarts on:" __PART_NAME__
#else
#if defined(_1200DEF_INC_)||defined(_2313DEF_INC_)||defined(_2323DEF_INC_)||defined(_4413DEF_INC_)||defined(_4433DEF_INC_)||defined(_4434DEF_INC_)||defined(_8515DEF_INC_)||defined(_TN10DEF_INC_)||defined(_TN11DEF_INC_)||defined(_TN12DEF_INC_)||defined(_TN13DEF_INC_)||defined(_TN13ADEF_INC_)||defined(_TN15DEF_INC_)||defined(_TN22DEF_INC_)||defined(_TN24DEF_INC_)||defined(_TN24ADEF_INC_)||defined(_TN25DEF_INC_)||defined(_TN26DEF_INC_)||defined(_TN28DEF_INC_)||defined(_TN43DEF_INC_)||defined(_TN44DEF_INC_)||defined(_TN44ADEF_INC_)||defined(_TN45DEF_INC_)||defined(_TN48DEF_INC_)||defined(_TN84DEF_INC_)||defined(_TN85DEF_INC_)||defined(_TN87DEF_INC_)||defined(_TN88DEF_INC_)||defined(_TN167DEF_INC_)||defined(_TN261DEF_INC_)||defined(_TN461DEF_INC_)||defined(_TN861DEF_INC_)||defined(_TN2313DEF_INC_)
#warning "Unsupported micro-controller:" __PART_NAME__
#else
;********************************************************************************************************************************************************
.ifndef Sram
.Equ Sram = 2
.endif
;----------------------------------------
.ifndef Port
.Equ Port = 1
.endif
;----------------------------------------
.ifndef Null
.Equ Null = 0
.endif
;----------------------------------------
.ifndef URXC0addr
.Equ URXC0addr  = URXCaddr
.endif
;----------------------------------------
.ifndef UDRE0addr
.Equ UDRE0addr  = UDREaddr
.endif
;********************************************************************************************************************************************************
#if defined(_M8DEF_INC_)||defined(_M8ADEF_INC_)||defined(_M16DEF_INC_)||defined(_M16ADEF_INC_)||defined(_M32DEF_INC_)||defined(_M32ADEF_INC_)||defined(_M323ADEF_INC_)
.ifndef UDR0
.Equ	UDR0	= UDR 
.endif
.Equ	UCSR0A	= UCSRA
.Equ	UCSR0B	= UCSRB
.Equ	UCSR0C	= UCSRC
.Equ	UBRR0L	= UBRRL
.Equ	UBRR0H	= UBRRH

.Equ RegUBRR0H 	= Port
.Equ RegUBRR0L 	= Port
.Equ RegUCSR0A 	= Port
.Equ RegUCSR0B 	= Port
.Equ RegUCSR0C 	= Port
.Equ RegUDR0   	= Port

#define Uart0Exist
#endif
;----------------------------------------
#if defined(_M48DEF_INC_)||defined(_M48PDEF_INC_)||defined(_M48PADEF_INC_)||defined(_M88DEF_INC_)||defined(_M88PDEF_INC_)||defined(_M88PADEF_INC_)||defined(_M165DEF_INC_)||defined(_M165PDEF_INC_)||defined(_M168DEF_INC_)||defined(_M168PDEF_INC_)||defined(_M168PADEF_INC_)||defined(_M169DEF_INC_)||defined(_M169PDEF_INC_)||defined(_M325DEF_INC_)||defined(_M325PDEF_INC_)||defined(_M328DEF_INC_)||defined(_M328PDEF_INC_)||defined(_M329DEF_INC_)||defined(_M644DEF_INC_)||defined(_M644PDEF_INC_)||defined(_M645DEF_INC_)||defined(_M3250DEF_INC_)||defined(_M3250PDEF_INC_)||defined(_M3290DEF_INC_)||defined(_M3290PDEF_INC_)||defined(_M6450DEF_INC_)||defined(_M6490DEF_INC_)
.Equ RegUBRR0H 	= Sram
.Equ RegUBRR0L 	= Sram
.Equ RegUCSR0A 	= Sram
.Equ RegUCSR0B 	= Sram
.Equ RegUCSR0C 	= Sram
.Equ RegUDR0   	= Sram

#define Uart0Exist
#endif
;----------------------------------------
#if defined(_M16U2DEF_INC_)||defined(_M16U4DEF_INC_)||defined(_M32U2DEF_INC_)||defined(_M32U4DEF_INC_)||defined(_M32U6DEF_INC_)||defined(_USB646DEF_INC_)||defined(_USB647DEF_INC_)||defined(_USB1286DEF_INC_)||defined(_USB2567DEF_INC_)
.Equ RegUBRR1H 	= Sram
.Equ RegUBRR1L 	= Sram
.Equ RegUCSR1A 	= Sram
.Equ RegUCSR1B 	= Sram
.Equ RegUCSR1C 	= Sram
.Equ RegUDR1   	= Sram

#define Uart1Exist
#endif
;----------------------------------------
#if defined(_M163DEF_INC_);||defined(_M164PADEF_INC_)
.Equ U2X0      	= U2X
.Equ MPCM0     	= MPCM
.Equ TXEN0     	= TXEN
.Equ RXEN0     	= RXEN
.Equ TXCIE0    	= TXCIE
.Equ RXCIE0    	= RXCIE
.Equ UMSEL0    	= Null
.Equ USBS0     	= Null
.Equ UPM00     	= Null
.Equ UPM01     	= Null
.Equ UCSZ00    	= Null
.Equ UCSZ01    	= Null
.Equ UCSZ02    	= Null
.Equ UDRIE0    	= Null

.ifndef UDR0
.Equ	UDR0	= UDR 
.endif
.Equ	UCSR0A	= UCSRA
.Equ	UCSR0B	= UCSRB
.Equ	UBRR0L	= UBRR
.Equ	UBRR0H	= UBRRHI

.Equ RegUBRR0H 	= Port
.Equ RegUBRR0L 	= Port
.Equ RegUCSR0A 	= Port
.Equ RegUCSR0B 	= Port
.Equ RegUCSR0C 	= Null
.Equ RegUDR0   	= Port

#define Uart0Exist
#endif
;----------------------------------------
#if defined(_M161DEF_INC_);||defined(_M164PADEF_INC_)
.Equ UMSEL0    	= Null
.Equ USBS0     	= Null
.Equ UPM00     	= Null
.Equ UPM01     	= Null
.Equ UCSZ00    	= Null
.Equ UCSZ01    	= Null
.Equ UCSZ02    	= Null
.Equ UDRIE0    	= Null

.Equ	UBRR0L	= UBRR0
.Equ	UBRR0H	= UBRRHI

.Equ RegUBRR0H 	= Port
.Equ RegUBRR0L 	= Port
.Equ RegUCSR0A 	= Port
.Equ RegUCSR0B 	= Port
.Equ RegUCSR0C 	= Null
.Equ RegUDR0   	= Port

.Equ	UBRR1L	= UBRR1
.Equ	UBRR1H	= UBRRHI

.Equ RegUBRR1H 	= Port
.Equ RegUBRR1L 	= Port
.Equ RegUCSR1A 	= Port
.Equ RegUCSR1B 	= Port
.Equ RegUCSR1C 	= Null
.Equ RegUDR1   	= Port

#define Uart0Exist
#define Uart1Exist
#endif
;----------------------------------------
#if defined(_M162DEF_INC_);||defined(_M164PADEF_INC_)
.Equ RegUBRR0H 	= Port
.Equ RegUBRR0L 	= Port
.Equ RegUCSR0A 	= Port
.Equ RegUCSR0B 	= Port
.Equ RegUCSR0C 	= Port
.Equ RegUDR0   	= Port

.Equ RegUBRR1H 	= Port
.Equ RegUBRR1L 	= Port
.Equ RegUCSR1A 	= Port
.Equ RegUCSR1B 	= Port
.Equ RegUCSR1C 	= Port
.Equ RegUDR1   	= Port

#define Uart0Exist
#define Uart1Exist
#endif
;----------------------------------------
#if defined(_M164PDEF_INC_)||defined(_M164PADEF_INC_)||defined(_M324PDEF_INC_)||defined(_M324PADEF_INC_)||defined(_M1281DEF_INC_)||defined(_M1284PDEF_INC_)||defined(_M2561DEF_INC_)||defined(_CAN32DEF_INC_)||defined(_CAN64DEF_INC_)||defined(_CAN128DEF_INC_)
.Equ RegUBRR0H 	= Sram
.Equ RegUBRR0L 	= Sram
.Equ RegUCSR0A 	= Sram
.Equ RegUCSR0B 	= Sram
.Equ RegUCSR0C 	= Sram
.Equ RegUDR0   	= Sram

.Equ RegUBRR1H 	= Sram
.Equ RegUBRR1L 	= Sram
.Equ RegUCSR1A 	= Sram
.Equ RegUCSR1B 	= Sram
.Equ RegUCSR1C 	= Sram
.Equ RegUDR1   	= Sram

#define Uart0Exist
#define Uart1Exist
#endif
;----------------------------------------
#if defined(_M64DEF_INC_)||defined(_M64ADEF_INC_)||defined(_M128DEF_INC_)||defined(_M128ADEF_INC_)
.Equ RegUBRR0H 	= Sram
.Equ RegUBRR0L 	= Port
.Equ RegUCSR0A 	= Port
.Equ RegUCSR0B 	= Port
.Equ RegUCSR0C 	= Sram
.Equ RegUDR0   	= Port

.Equ RegUBRR1H 	= Sram
.Equ RegUBRR1L 	= Sram
.Equ RegUCSR1A 	= Sram
.Equ RegUCSR1B 	= Sram
.Equ RegUCSR1C 	= Sram
.Equ RegUDR1   	= Sram

#define Uart0Exist
#define Uart1Exist
#endif
;----------------------------------------
#if defined(_M640DEF_INC_)||defined(_M1280DEF_INC_)||defined(_M2560DEF_INC_)
.Equ RegUBRR0H 	= Sram
.Equ RegUBRR0L 	= Sram
.Equ RegUCSR0A 	= Sram
.Equ RegUCSR0B 	= Sram
.Equ RegUCSR0C 	= Sram
.Equ RegUDR0   	= Sram

.Equ RegUBRR1H 	= Sram
.Equ RegUBRR1L 	= Sram
.Equ RegUCSR1A 	= Sram
.Equ RegUCSR1B 	= Sram
.Equ RegUCSR1C 	= Sram
.Equ RegUDR1   	= Sram

.Equ RegUBRR2H 	= Sram
.Equ RegUBRR2L 	= Sram
.Equ RegUCSR2A 	= Sram
.Equ RegUCSR2B 	= Sram
.Equ RegUCSR2C 	= Sram
.Equ RegUDR2   	= Sram

.Equ RegUBRR3H 	= Sram
.Equ RegUBRR3L 	= Sram
.Equ RegUCSR3A 	= Sram
.Equ RegUCSR3B 	= Sram
.Equ RegUCSR3C 	= Sram
.Equ RegUDR3   	= Sram

#define Uart0Exist
#define Uart1Exist
#define Uart2Exist
#define Uart3Exist
#endif
;----------------------------------------
#if defined(_PWM2DEF_INC_)||defined(_PWM2BDEF_INC_)||defined(_PWM3DEF_INC_)||defined(_PWM3BDEF_INC_)||defined(_PWM216DEF_INC_)||defined(_PWM316DEF_INC_)
.ifndef UDR0
.Equ	UDR0	= UDR 
.endif
.Equ	UCSR0A	= UCSRA
.Equ	UCSR0B	= UCSRB
.Equ	UCSR0C	= UCSRC
.Equ	UBRR0L	= UBRRL
.Equ	UBRR0H	= UBRRH

.Equ RegUBRR0H 	= Sram
.Equ RegUBRR0L 	= Sram
.Equ RegUCSR0A 	= Sram
.Equ RegUCSR0B 	= Sram
.Equ RegUCSR0C 	= Sram
.Equ RegUDR0   	= Sram

#define Uart0Exist
#endif
;********************************************************************************************************************************************************
; UCSR1A - USART Control and Status Register A
.ifndef MPCM0
.equ	MPCM0	= 0	; Multi-processor Communication Mode
.endif
.ifndef U2X0
.equ	U2X0	= 1	; Double the USART transmission speed
.endif
.ifndef UPE0
.equ	UPE0	= 2	; Parity Error
.endif
.ifndef DOR0
.equ	DOR0	= 3	; Data overRun
.endif
.ifndef FE0
.equ	FE0		= 4	; Framing Error
.endif
.ifndef UDRE0
.equ	UDRE0	= 5	; USART Data Register Empty
.endif
.ifndef TXC0
.equ	TXC0	= 6	; USART Transmitt Complete
.endif
.ifndef RXC0
.equ	RXC0	= 7	; USART Receive Complete
.endif

; UCSR1B - USART Control and Status Register B
.ifndef TXB80
.equ	TXB80	= 0	; Transmit Data Bit 8
.endif
.ifndef RXB80
.equ	RXB80	= 1	; Receive Data Bit 8
.endif
.ifndef UCSZ02
.equ	UCSZ02	= 2	; Character Size
.endif
.ifndef TXEN0
.equ	TXEN0	= 3	; Transmitter Enable
.endif
.ifndef RXEN0
.equ	RXEN0	= 4	; Receiver Enable
.endif
.ifndef UDRIE0
.equ	UDRIE0	= 5	; USART Data register Empty Interrupt Enable
.endif
.ifndef TXCIE0
.equ	TXCIE0	= 6	; TX Complete Interrupt Enable
.endif
.ifndef RXCIE0
.equ	RXCIE0	= 7	; RX Complete Interrupt Enable
.endif

; UCSR1C - USART Control and Status Register C
.ifndef UCPOL0
.equ	UCPOL0	= 0	; Clock Polarity
.endif
.ifndef UCSZ00
.equ	UCSZ00	= 1	; Character Size
.endif
.ifndef UCSZ01
.equ	UCSZ01	= 2	; Character Size
.endif
.ifndef USBS0
.equ	USBS0	= 3	; Stop Bit Select
.endif
.ifndef UPM00
.equ	UPM00	= 4	; Parity Mode Bit 0
.endif
.ifndef UPM01
.equ	UPM01	= 5	; Parity Mode Bit 1
.endif
.ifndef UMSEL0
.equ	UMSEL0	= 6	; USART Mode Select
.endif
.ifndef URSEL0
.equ	URSEL0	= 7	; USART Mode Select
.endif
;********************************************************************************************************************************************************
;#if defined(_M8DEF_INC_)||defined(_M88DEF_INC_)||defined(_M88PDEF_INC_)||defined(_M88PADEF_INC_)||defined(_M64DEF_INC_)
//#ifndef _Uart1_Driver_Service_
//#define _Uart1_Driver_Service_
;********************************************************************************************************************************************************
.ifndef True
.Equ True 						= 1
.endif
;----------------------------------------
.ifndef False
.Equ False 						= 0
.endif
;----------------------------------------
.ifndef Byte
.Equ Byte         = 1
.endif
;----------------------------------------
.ifndef Half
.Equ Half         = 2
.endif
;----------------------------------------
.ifndef Word
.Equ Word         = 4
.endif
;----------------------------------------
.ifndef Extend48
.Equ Extend48     = 6
.endif
;----------------------------------------
.ifndef Loong64
.Equ Loong64      = 8
.endif
;----------------------------------------
.ifndef Tx_Rx_Disabled
.Equ Tx_Rx_Disabled 			= 0
.endif
;----------------------------------------
.ifndef Tx_Enabled
.Equ Tx_Enabled 				= 1
.endif
;----------------------------------------
.ifndef Rx_Enabled
.Equ Rx_Enabled 				= 2
.endif
;----------------------------------------
.ifndef Tx_Rx_Enabled
.Equ Tx_Rx_Enabled 				= 3
.endif
;----------------------------------------
.ifndef Tx_Rx_Udre_Int_Disabled
.Equ Tx_Rx_Udre_Int_Disabled 	= 0
.endif
;----------------------------------------
.ifndef Tx_Int_Enabled
.Equ Tx_Int_Enabled 			= 1
.endif
;----------------------------------------
.ifndef Rx_Int_Enabled
.Equ Rx_Int_Enabled 			= 2
.endif
;----------------------------------------
.ifndef Tx_Rx_Int_Enabled
.Equ Tx_Rx_Int_Enabled 			= 3
.endif
;----------------------------------------
.ifndef Udre_Int_Enabled
.Equ Udre_Int_Enabled 			= 4
.endif
;----------------------------------------
.ifndef Tx_Udre_Int_Enabled
.Equ Tx_Udre_Int_Enabled 		= 5
.endif
;----------------------------------------
.ifndef Rx_Udre_Int_Enabled
.Equ Rx_Udre_Int_Enabled 		= 6
.endif
;----------------------------------------
.ifndef Tx_Rx_Udre_Int_Enabled
.Equ Tx_Rx_Udre_Int_Enabled 	= 7
.endif
;----------------------------------------
.ifndef Even_Parity
.Equ Even_Parity 				= 1
.endif
;----------------------------------------
.ifndef Odd_Parity
.Equ Odd_Parity 				= 2
.endif
;********************************************************************************************************************************************************
;@0 = False0 Uart2X
;@1 = Baut rate
;@2 = 0 Tx-Rx Disable,1 Tx Enable,2 Rx Enable,3 Tx-Rx enable
;@3 = 0 Tx-Rx InteruptDisable,1 InteruptTx Enable,2 InteruptRx Enable,3 InteruptTx-Rx enable, With UDRIE Disabled
;     4 Tx-Rx InteruptDisable,5 InteruptTx Enable,6 InteruptRx Enable,7 InteruptTx-Rx enable, With UDRIE Enabled
;@4 = 5 5Bits,6 6Bits,7 7Bits,8 8Bits,9 9Bits,
;@5 = False Parity Disabled,1 Enabled Even Parity,2Enabled Odd Parity
;@6 = 1 1Stop bit,2 2Stop bit
;@7 = False Asincronus Mode,True Sincronus Mode
;@8 = False No multi-procesor comunication mode,True Multi-procesor comunication mode
;----------------------------------------
.Macro Inline_UartSetup
	Push R16
	Push R17
;----------------------------------------
.if @1 == 0
	Ldi R16,High((CoreFrequ/16/@2)-1)
.ifdef URSEL@0
	Cbr R16,1<<URSEL@0
.endif
.if RegUBRR@0H == Sram
	Sts UBRR@0H,R16
.elif RegUBRR@0H == Port
	Out UBRR@0H,R16
.endif
	Ldi R16,Low((CoreFrequ/16/@2)-1)
.if RegUBRR@0L == Sram
	Sts UBRR@0L,R16
.elif RegUBRR@0L == Port
	Out UBRR@0L,R16
.endif
.elif @1 == 1
	Ldi R16,High((CoreFrequ/8/@2)-1)
.ifdef URSEL@0
	Cbr R16,1<<URSEL@0
.endif
.if RegUBRR@0H == Sram
	Sts UBRR@0H,R16
.elif RegUBRR@0H == Port
	Out UBRR@0H,R16
.endif
	Ldi R16,Low((CoreFrequ/8/@2)-1)
.if RegUBRR@0L == Sram
	Sts UBRR@0L,R16
.elif RegUBRR@0L == Port
	Out UBRR@0L,R16
.endif
.endif
;----------------------------------------
.if RegUCSR@0A == Sram
	Lds R16,UCSR@0A
.elif RegUCSR@0A == Port
	In R16,UCSR@0A
.endif
.if @1 == True
	Sbr R16,1<<U2X0
.elif @1 == False
	Cbr R16,1<<U2X0
.endif
;----------------------------------------
.if @9 == True
	Sbr R16,1<<MPCM0
.elif @9 == False
	Cbr R16,1<<MPCM0
.endif
.if RegUCSR@0A == Sram
	Sts UCSR@0A,R16
.elif RegUCSR@0A == Port
	Out UCSR@0A,R16
.endif
;----------------------------------------
.if RegUCSR@0B == Sram
	Lds R16,UCSR@0B
.elif RegUCSR@0B == Port
	In R16,UCSR@0B
.endif
.if @3 == 0
	Cbr R16,1<<TXEN0 | 1<<RXEN0
.elif @3 == 1
	Sbr R16,1<<TXEN0
	Cbr R16,1<<RXEN0
.elif @3 == 2
	Cbr R16,1<<TXEN0
	Sbr R16,1<<RXEN0
.elif @3 == 3
	Sbr R16,1<<TXEN0 | 1<<RXEN0
.endif
;----------------------------------------
.if @4 == 0
	Cbr R16,1<<TXCIE0 | 1<<RXCIE0 | 1<<UDRIE0
.elif @4 == 1
	Sbr R16,1<<TXCIE0
	Cbr R16,1<<RXCIE0 | 1<<UDRIE0
.elif @4 == 2
	Cbr R16,1<<TXCIE0 | 1<<UDRIE0
	Sbr R16,1<<RXCIE0
.elif @4 == 3
	Sbr R16,1<<TXCIE0 | 1<<RXCIE0
	Cbr R16,1<<UDRIE0
.elif @4 == 4
	Cbr R16,1<<TXCIE0 | 1<<RXCIE0
	Sbr R16,1<<UDRIE0
.elif @4 == 5
	Sbr R16,1<<TXCIE0 | 1<<UDRIE0
	Cbr R16,1<<RXCIE0
.elif @4 == 6
	Cbr R16,1<<TXCIE0 | 1<<RXCIE0
	Sbr R16,1<<RXCIE0
.elif @4 == 7
	Sbr R16,1<<TXCIE0 | 1<<RXCIE0 | 1<<UDRIE0
.endif
;----------------------------------------
.if RegUCSR@0C == Sram
#if defined(_M8DEF_INC_)||defined(_M8ADEF_INC_)||defined(_M16DEF_INC_)||defined(_M16ADEF_INC_)||defined(_M162DEF_INC_)||defined(_M32DEF_INC_)||defined(_M32ADEF_INC_)||defined(_M323DEF_INC_)
	Lds R17,UBRR@0H
#endif
	Lds R17,UCSR@0C
.elif RegUCSR@0C == Port
#if defined(_M8DEF_INC_)||defined(_M8ADEF_INC_)||defined(_M16DEF_INC_)||defined(_M16ADEF_INC_)||defined(_M162DEF_INC_)||defined(_M32DEF_INC_)||defined(_M32ADEF_INC_)||defined(_M323DEF_INC_)
	In R17,UBRR@0H
#endif
	In R17,UCSR@0C
.endif
.if @5 == 5
	Cbr R16,1<<UCSZ02 | 1<<UCSZ01 | 1<<UCSZ00
.elif @5 == 6
	Cbr R16,1<<UCSZ02 | 1<<UCSZ01
	Sbr R17,1<<UCSZ00
.elif @5 == 7
	Cbr R16,1<<UCSZ02 | 1<<UCSZ00
	Sbr R17,1<<UCSZ01
.elif @5 == 8
	Cbr R16,1<<UCSZ02
	Sbr R17,1<<UCSZ01 | 1<<UCSZ00
.elif @5 == 9
	Sbr R16,1<<UCSZ02 | 1<<UCSZ01 | 1<<UCSZ00
.endif
.if RegUCSR@0B == Sram
	Sts UCSR@0B,R16
.elif RegUCSR@0B == Port
	Out UCSR@0B,R16
.endif
;----------------------------------------
.if @6 == 0
	Cbr R17,1<<UPM00 | 1<<UPM01
.elif @6 == 1
	Cbr R17,1<<UPM00
	Sbr R17,1<<UPM01
.elif @6 == 2
	Sbr R17,1<<UPM00 | 1<<UPM01
.endif
;----------------------------------------
.if @7 == 1
	Cbr R17,1<<USBS0
.elif @7 == 2
	Sbr R17,1<<USBS0
.endif
;----------------------------------------
.if @8 == False
	Cbr R17,1<<UMSEL0
.elif @8 == True
	Sbr R17,1<<UMSEL0
.endif
;----------------------------------------
.ifdef URSEL@0
	Sbr R16,1<<URSEL@0
.endif
.if RegUCSR@0C == Sram
	Sts UCSR@0C,R17
.elif RegUCSR@0C == Port
	Out UCSR@0C,R17
.endif
	Pop R17
	Pop R16
.EndM
;********************************************************************************************************************************************************
.Macro Inline_UartBaut
	Push R16
	Ldi R16,High((CoreFrequ/16/@1)-1)
.ifdef URSEL@0
	Cbr R16,1<<URSEL@0
.endif
.if RegUBRR@0H == Sram
	Sts UBRR@0H,R16
.elif RegUBRR@0H == Port
	Out UBRR@0H,R16
.endif
	Ldi R16,Low((CoreFrequ/16/@1)-1)
.if RegUBRR@0L == Sram
	Sts UBRR@0L,R16
.elif RegUBRR@0L == Port
	Out UBRR@0L,R16
.endif
	Pop R16
.EndM
;----------------------------------------
.Macro Inline_UartBautU2X
	Push R16
	Ldi R16,High((CoreFrequ/8/@1)-1)
.ifdef URSEL@0
	Cbr R16,1<<URSEL@0
.endif
.if RegUBRR@0H == Sram
	Sts UBRR@0H,R16
.elif RegUBRR@0H == Port
	Out UBRR@0H,R16
.endif
	Ldi R16,Low((CoreFrequ/8/@1)-1)
.if RegUBRR@0L == Sram
	Sts UBRR@0L,R16
.elif RegUBRR@0L == Port
	Out UBRR@0L,R16
.endif
	Pop R16
.EndM
;********************************************************************************************************************************************************
.Macro Inline_UartTxEnable
	Push R16
.if RegUCSR@0B == Sram
	Lds R16,UCSR@0B
.elif RegUCSR@0B == Port
	In R16,UCSR@0B
.endif
.if @1 == True
	Sbr R16,1<<TXEN0
.elif @1 == False
	Cbr R16,1<<TXEN0
.endif
.if RegUCSR@0B == Sram
	Sts UCSR@0B,R16
.elif RegUCSR@0B == Port
	Out UCSR@0B,R16
.endif
	Pop R16
.EndM
;********************************************************************************************************************************************************
.Macro Inline_UartRxEnable
	Push R16
.if RegUCSR@0B == Sram
	Lds R16,UCSR@0B
.elif RegUCSR@0B == Port
	In R16,UCSR@0B
.endif
.if @1 == True
	Sbr R16,1<<RXEN0
.elif @1 == False
	Cbr R16,1<<RXEN0
.endif
.if RegUCSR@0B == Sram
	Sts UCSR@0B,R16
.elif RegUCSR@0B == Port
	Out UCSR@0B,R16
.endif
	Pop R16
.EndM
;********************************************************************************************************************************************************
.Macro Inline_UartTxIntEnable
	Push R16
.if RegUCSR@0B == Sram
	Lds R16,UCSR@0B
.elif RegUCSR@0B == Port
	In R16,UCSR@0B
.endif
.if @1 == True
	Sbr R16,1<<TXCIE0
.elif @1 == False
	Cbr R16,1<<TXCIE0
.endif
.if RegUCSR@0B == Sram
	Sts UCSR@0B,R16
.elif RegUCSR@0B == Port
	Out UCSR@0B,R16
.endif
	Pop R16
.EndM
;********************************************************************************************************************************************************
.Macro Inline_UartRxIntEnable
	Push R16
.if RegUCSR@0B == Sram
	Lds R16,UCSR@0B
.elif RegUCSR@0B == Port
	In R16,UCSR@0B
.endif
.if @1 == True
	Sbr R16,1<<RXCIE0
.elif @1 == False
	Cbr R16,1<<RXCIE0
.endif
.if RegUCSR@0B == Sram
	Sts UCSR@0B,R16
.elif RegUCSR@0B == Port
	Out UCSR@0B,R16
.endif
	Pop R16
.EndM
;********************************************************************************************************************************************************
.Macro Inline_UartUdreIntEnable
	Push R16
.if RegUCSR@0B == Sram
	Lds R16,UCSR@0B
.elif RegUCSR@0B == Port
	In R16,UCSR@0B
.endif
.if @1 == True
	Sbr R16,1<<UDRIE0
.elif @1 == False
	Cbr R16,1<<UDRIE0
.endif
.if RegUCSR@0B == Sram
	Sts UCSR@0B,R16
.elif RegUCSR@0B == Port
	Out UCSR@0B,R16
.endif
	Pop R16
.EndM
;********************************************************************************************************************************************************
.Macro Inline_UartU2xEnable
	Push R16
.if RegUCSR@0A == Sram
	Lds R16,UCSR@0A
.elif RegUCSR@0A == Port
	In R16,UCSR@0A
.endif
.if @1 == True
	Sbr R16,1<<U2X0
.elif @1 == False
	Cbr R16,1<<U2X0
.endif
.if RegUCSR@0A == Sram
	Sts UCSR@0A,R16
.elif RegUCSR@0A == Port
	Out UCSR@0A,R16
.endif
	Pop R16
.EndM
;********************************************************************************************************************************************************
.Macro Inline_UartBitsNr
	Push R16
	Push R17
.if RegUCSR@0B == Sram
	Lds R16,UCSR@0B
.elif RegUCSR@0B == Port
	In R16,UCSR@0B
.endif
.if RegUCSR@0C == Sram
#if defined(_M8DEF_INC_)||defined(_M8ADEF_INC_)||defined(_M16DEF_INC_)||defined(_M16ADEF_INC_)||defined(_M162DEF_INC_)||defined(_M32DEF_INC_)||defined(_M32ADEF_INC_)||defined(_M323DEF_INC_)
	Lds R17,UBRR@0H
#endif
	Lds R17,UCSR@0C
.elif RegUCSR@0C == Port
#if defined(_M8DEF_INC_)||defined(_M8ADEF_INC_)||defined(_M16DEF_INC_)||defined(_M16ADEF_INC_)||defined(_M162DEF_INC_)||defined(_M32DEF_INC_)||defined(_M32ADEF_INC_)||defined(_M323DEF_INC_)
	In R17,UBRR@0H
#endif
	In R17,UCSR@0C
.endif
.if @1 == 5
	Cbr R16,1<<UCSZ02 | 1<<UCSZ01 | 1<<UCSZ00
.elif @1 == 6
	Cbr R16,1<<UCSZ02 | 1<<UCSZ01
	Sbr R17,1<<UCSZ00
.elif @1 == 7
	Cbr R16,1<<UCSZ02 | 1<<UCSZ00
	Sbr R17,1<<UCSZ01
.elif @1 == 8
	Cbr R16,1<<UCSZ02
	Sbr R17,1<<UCSZ01 | 1<<UCSZ00
.elif @1 == 9
	Sbr R16,1<<UCSZ02 | 1<<UCSZ01 | 1<<UCSZ00
.endif
.ifdef URSEL@0
	Sbr R16,1<<URSEL@0
.endif
.if RegUCSR@0C == Sram
	Sts UCSR@0C,R17
.elif RegUCSR@0C == Port
	Out UCSR@0C,R17
.endif
.if RegUCSR@0B == Sram
	Sts UCSR@0B,R16
.elif RegUCSR@0B == Port
	Out UCSR@0B,R16
.endif
	Pop R17
	Pop R16
.EndM
;********************************************************************************************************************************************************
.Macro Inline_UartParity
	Push R16
.if RegUCSR@0C == Sram
#if defined(_M8DEF_INC_)||defined(_M8ADEF_INC_)||defined(_M16DEF_INC_)||defined(_M16ADEF_INC_)||defined(_M162DEF_INC_)||defined(_M32DEF_INC_)||defined(_M32ADEF_INC_)||defined(_M323DEF_INC_)
	Lds R16,UBRR@0H
#endif
	Lds R16,UCSR@0C
.elif RegUCSR@0C == Port
#if defined(_M8DEF_INC_)||defined(_M8ADEF_INC_)||defined(_M16DEF_INC_)||defined(_M16ADEF_INC_)||defined(_M162DEF_INC_)||defined(_M32DEF_INC_)||defined(_M32ADEF_INC_)||defined(_M323DEF_INC_)
	In R16,UBRR@0H
#endif
	In R16,UCSR@0C
.endif
.if @1 == 0
	Cbr R16,1<<UPM00 | 1<<UPM01
.elif @1 == 1
	Cbr R16,1<<UPM00
	Sbr R16,1<<UPM01
.elif @1 == 2
	Sbr R16,1<<UPM00 | 1<<UPM01
.endif
.ifdef URSEL@0
	Sbr R16,1<<URSEL@0
.endif
.if RegUCSR@0C == Sram
	Sts UCSR@0C,R16
.elif RegUCSR@0C == Port
	Out UCSR@0C,R16
.endif
	Pop R16
.EndM
;********************************************************************************************************************************************************
.Macro Inline_UartStopBits
	Push R16
.if RegUCSR@0C == Sram
#if defined(_M8DEF_INC_)||defined(_M8ADEF_INC_)||defined(_M16DEF_INC_)||defined(_M16ADEF_INC_)||defined(_M162DEF_INC_)||defined(_M32DEF_INC_)||defined(_M32ADEF_INC_)||defined(_M323DEF_INC_)||defined(_M64DEF_INC_)||defined(_M128ADEF_INC_)||defined(_M256ADEF_INC_)
	Lds R16,UBRR@0H
#endif
	Lds R16,UCSR@0C
.elif RegUCSR@0C == Port
#if defined(_M8DEF_INC_)||defined(_M8ADEF_INC_)||defined(_M16DEF_INC_)||defined(_M16ADEF_INC_)||defined(_M162DEF_INC_)||defined(_M32DEF_INC_)||defined(_M32ADEF_INC_)||defined(_M323DEF_INC_)||defined(_M64DEF_INC_)||defined(_M128ADEF_INC_)||defined(_M256ADEF_INC_)
	In R16,UBRR@0H
#endif
	In R16,UCSR@0C
.endif
.if @1 == 1
	Cbr R16,1<<USBS0
.elif @1 == 2
	Sbr R16,1<<USBS0
.endif
.ifdef URSEL@0
	Sbr R16,1<<URSEL@0
.endif
.if RegUCSR@0C == Sram
	Sts UCSR@0C,R16
.elif RegUCSR@0C == Port
	Out UCSR@0C,R16
.endif
	Pop R16
.EndM
;********************************************************************************************************************************************************
.Macro Inline_UartSincEnable
	Push R16
.if RegUCSR@0C == Sram
#if defined(_M8DEF_INC_)||defined(_M8ADEF_INC_)||defined(_M16DEF_INC_)||defined(_M16ADEF_INC_)||defined(_M162DEF_INC_)||defined(_M32DEF_INC_)||defined(_M32ADEF_INC_)||defined(_M323DEF_INC_)
	Lds R16,UBRR@0H
#endif
	Lds R16,UCSR@0C
.elif RegUCSR@0C == Port
#if defined(_M8DEF_INC_)||defined(_M8ADEF_INC_)||defined(_M16DEF_INC_)||defined(_M16ADEF_INC_)||defined(_M162DEF_INC_)||defined(_M32DEF_INC_)||defined(_M32ADEF_INC_)||defined(_M323DEF_INC_)
	In R16,UBRR@0H
#endif
	In R16,UCSR@0C
.endif
.if @1 == True
	Sbr R16,1<<UMSEL0
.elif @1 == False
	Cbr R16,1<<UMSEL0
.endif
.ifdef URSEL@0
	Sbr R16,1<<URSEL@0
.endif
.if RegUCSR@0C == Sram
	Sts UCSR@0C,R16
.elif RegUCSR@0C == Port
	Out UCSR@0C,R16
.endif
	Pop R16
.EndM
;********************************************************************************************************************************************************
.Macro Inline_UartMultiprocesorEnable
	Push R16
.if RegUCSR@0A == Sram
	Lds R16,UCSR@0A
.elif RegUCSR@0A == Port
	In R16,UCSR@0A
.endif
.if @1 == True
	Sbr R16,1<<MPCM0
.elif @1 == False
	Cbr R16,1<<MPCM0
.endif
.if RegUCSR@0A == Sram
	Sts UCSR@0A,R16
.elif RegUCSR@0A == Port
	Out UCSR@0A,R16
.endif
	Pop R16
.EndM
;********************************************************************************************************************************************************
#ifdef Uart0Exist
#ifdef Uart0RxFifoSize
.Dseg
Uart0RxFifoFlags:              .Byte 1
Uart0RxFifo:                   .Byte Uart0RxFifoSize + 6
.Equ Uart0RxFifoSize_          = Uart0RxFifoSize
.Cseg
#endif
;-----------------
#ifdef Uart0TxFifoSize
.Dseg
Uart0TxFifoFlags:              .Byte 1
Uart0TxFifo:                   .Byte Uart0TxFifoSize + 6
.Equ Uart0TxFifoSize_          = Uart0TxFifoSize
.Cseg
#endif
#endif
;-----------------
#ifdef Uart1Exist
#ifdef Uart1RxFifoSize
.Dseg
Uart1RxFifoFlags:              .Byte 1
Uart1RxFifo:                   .Byte Uart1RxFifoSize + 6
.Equ Uart1RxFifoSize_          = Uart1RxFifoSize
.Cseg
#endif
;-----------------
#ifdef Uart1TxFifoSize
.Dseg
Uart1TxFifoFlags:              .Byte 1
Uart1TxFifo:                   .Byte Uart1TxFifoSize + 6
.Equ Uart1TxFifoSize_          = Uart1TxFifoSize
.Cseg
#endif
#endif
;-----------------
#ifdef Uart2Exist
#ifdef Uart2RxFifoSize
.Dseg
Uart2RxFifoFlags:              .Byte 1
Uart2RxFifo:                   .Byte Uart2RxFifoSize + 6
.Equ Uart2RxFifoSize_          = Uart2RxFifoSize
.Cseg
#endif
;-----------------
#ifdef Uart2TxFifoSize
.Dseg
Uart2TxFifoFlags:              .Byte 1
Uart2TxFifo:                   .Byte Uart2TxFifoSize + 6
.Equ Uart2TxFifoSize_          = Uart2TxFifoSize
.Cseg
#endif
#endif
;-----------------
#ifdef Uart3Exist
#ifdef Uart3RxFifoSize
.Dseg
Uart3RxFifoFlags:              .Byte 1
Uart3RxFifo:                   .Byte Uart3RxFifoSize + 6
.Equ Uart3RxFifoSize_          = Uart3RxFifoSize
.Cseg
#endif
;-----------------
#ifdef Uart3TxFifoSize
.Dseg
Uart3TxFifoFlags:              .Byte 1
Uart3TxFifo:                   .Byte Uart3TxFifoSize + 6
.Equ Uart3TxFifoSize_          = Uart3TxFifoSize
.Cseg
#endif
#endif
;-----------------
.Macro URXCaddr_Interupt
	Push R16
	In R16,SREG
	Push R16
	Push R17
	Push Xl
	Push Xh
;-----------------
.if RegUDR@0 == Sram
	Lds R17,UDR@0
.elif RegUDR@0 == Port
	In R17,UDR@0
.endif
;-----------------
	Lds Xl,Uart@0RxFifo + Uart@0FifoCountRx + 0
	Lds Xh,Uart@0RxFifo + Uart@0FifoCountRx + 1
	Adiw Xl:Xh,1
	Cpi Xl,Low(Uart@0RxFifoSize_)
	Brne Uart@0FifoNotFullUart@0FifoCountRx
	Cpi Xh,High(Uart@0RxFifoSize_)
	Brne Uart@0FifoNotFullUart@0FifoCountRx
	Lds R16,Uart@0RxFifoFlags
	Sbr R16,1<<UartRxFifoOverflow
	Sts Uart@0RxFifoFlags,R16
	Inline_Uart@0RxIntEnable True
	Rjmp Uart@0FifoFullUart@0FifoCountRx
Uart@0FifoNotFullUart@0FifoCountRx:
	Sts Uart@0RxFifo + Uart@0FifoCountRx + 0,Xl
	Sts Uart@0RxFifo + Uart@0FifoCountRx + 1,Xh
;-----------------
	Lds Xl,Uart@0RxFifo + Uart@0PushCountRx + 0
	Lds Xh,Uart@0RxFifo + Uart@0PushCountRx + 1
	Adiw Xl:Xh,1
	Cpi Xl,Low(Uart@0RxFifoSize_)
	Brne Uart@0SkipResetUart@0PushCountRx
	Cpi Xh,High(Uart@0RxFifoSize_)
	Brne Uart@0SkipResetUart@0PushCountRx
	Clr Xl
	Clr Xh
Uart@0SkipResetUart@0PushCountRx:
;-----------------
	Sts Uart@0RxFifo + Uart@0PushCountRx + 0,Xl
	Sts Uart@0RxFifo + Uart@0PushCountRx + 1,Xh
	Subi Xl,Low(-(Uart@0RxFifo + 6))
	Sbci Xh,High(-(Uart@0RxFifo + 6))
	St X,R17
;-----------------
Uart@0FifoFullUart0FifoCountRx:
	Pop Xh
	Pop Xl
	Pop R17
	Pop R16
	Out SREG,R16
	Pop R16
.EndM
;********************************************************************************************************************************************************
.Macro UDREaddr_Interupt
	Push R16
	In R16,SREG
	Push R16
	Push Xl
	Push Xh
;-----------------
	Lds Xl,Uart@0TxFifo + Uart@0FifoCountTx + 0
	Lds Xh,Uart@0TxFifo + Uart@0FifoCountTx + 1
	Cpi Xl,0
	Brne Uart@0FifoNotEmptyUart@0FifoCountTx
	Cpi Xh,0
	Brne Uart@0FifoNotEmptyUart@0FifoCountTx
	Lds R16,Uart@0TxFifoFlags
	Sbr R16,1<<UartTxFifoEmpty
	Sts Uart@0TxFifoFlags,R16
	Inline_Uart@0UdreIntEnable False
	Rjmp Uart@0FifoEmptyUart@0FifoCountTx
Uart@0FifoNotEmptyUart@0FifoCountTx:
	Sbiw Xl:Xh,1
	Sts Uart@0TxFifo + Uart@0FifoCountTx + 0,Xl
	Sts Uart@0TxFifo + Uart@0FifoCountTx + 1,Xh
;-----------------
	Lds Xl,Uart@0TxFifo + Uart@0PopCountTx + 0
	Lds Xh,Uart@0TxFifo + Uart@0PopCountTx + 1
	Adiw Xl:Xh,1
	Cpi Xl,Low(Uart@0TxFifoSize_)
	Brne Uart@0SkipResetUart@0PopCountTx
	Cpi Xh,High(Uart@0TxFifoSize_)
	Brne Uart@0SkipResetUart@0PopCountTx
	Clr Xl
	Clr Xh
Uart@0SkipResetUart@0PopCountTx:
;-----------------
	Sts Uart@0TxFifo + Uart@0PopCountTx + 0,Xl
	Sts Uart@0TxFifo + Uart@0PopCountTx + 1,Xh
	Subi Xl,Low(-(Uart@0TxFifo + 6))
	Sbci Xh,High(-(Uart@0TxFifo + 6))
	Ld R16,X
;-----------------
.if RegUDR@0 == Sram
	Sts UDR@0,R16
.elif RegUDR@0 == Port
	Out UDR@0,R16
.endif
;-----------------
Uart@0FifoEmptyUart@0FifoCountTx:
	Pop Xh
	Pop Xl
	Pop R16
	Out SREG,R16
	Pop R16
.EndM
;********************************************************************************************************************************************************
#ifdef Uart0Exist
#ifndef Uart0Enabled
//#message ">>>>>>For enable Uart0 macros please define ( Uart0Enabled ) constant. Ex: #define Uart0Enabled"
#endif
.Macro Inline_Uart0U2xEnable
	Inline_UartU2xEnable 0,@0
.EndM
.Macro Inline_Uart0Baut
	Inline_UartBaut 0,@0
.EndM
.Macro Inline_Uart0BautU2x
	Inline_UartBautU2x 0,@0
.EndM
.Macro Inline_Uart0BitsNr
	Inline_UartBitsNr 0,@0
.EndM
.Macro Inline_Uart0Parity
	Inline_UartParity 0,@0
.EndM
.Macro Inline_Uart0StopBits
	Inline_UartStopBits 0,@0
.EndM
.Macro Inline_Uart0SincEnable
	Inline_UartSincEnable 0,@0
.EndM
.Macro Inline_Uart0MultiprocesorEnable
	Inline_UartMultiprocesorEnable 0,@0
.EndM
.Macro Inline_Uart0RxIntEnable
	Inline_UartRxIntEnable 0,@0
.EndM
.Macro Inline_Uart0TxIntEnable
	Inline_UartTxIntEnable 0,@0
.EndM
.Macro Inline_Uart0UdreIntEnable
	Inline_UartUdreIntEnable 0,@0
.EndM
.Macro Inline_Uart0TxEnable
	Inline_UartTxEnable 0,@0
.EndM
.Macro Inline_Uart0RxEnable
	Inline_UartRxEnable 0,@0
.EndM
.Macro Inline_Uart0SendRegChar
	Inline_UartSendRegChar 0,@0
.EndM
.Macro Inline_Uart0SendConstChar
	Inline_UartSendConstChar 0,@0
.EndM
.Macro Inline_Uart0ReceiveChar
	Inline_UartReceiveChar 0,@0
.EndM
.Macro Inline_Uart0FlashConstStrSend
	Inline_UartFlashConstStrSend 0,@0
.EndM
.Macro Inline_Uart0RamConstStrSend
	Inline_UartRamConstStrSend 0,@0
.EndM
.Macro Inline_Uart0RamVarStrSend
	Inline_UartRamVarStrSend 0,@0
.EndM
.Macro Inline_Uart0Setup
	Inline_UartSetup 0,@0,@1,@2,@3,@4,@5,@6,@7,@8;Default Setup
.EndM
.Macro Inline_Uart0ForceReceiveChar
	Inline_UartForceReceiveChar 0,@0
.EndM
.Macro Inline_Uart0StrSend
    Inline_UartStrSend 0,@0
.EndM
;----------------------------------------
#ifndef Uart0RxFifoSize
//#message ">>>>>>If you want to enable FOFO for Uart0 Rx Please define ( Uart0RxFifoSize ) constant. Ex: '#define Uart0RxFifoSize[10]'"
#endif
#ifndef Uart0TxFifoSize
//#message ">>>>>>If you want to enable FOFO for Uart0 Tx Please define ( Uart0TxFifoSize ) constant. Ex: '#define Uart0TxFifoSize[10]'"
#endif
;----------------------------------------
#ifdef Uart0RxFifoSize
Uart0SkipRxInteruptVectors:
.Org URXC0addr
#if defined(_M48DEF_INC_)||defined(_M48PDEF_INC_)||defined(_M48PADEF_INC_)||defined(_M8DEF_INC_)||defined(_M8ADEF_INC_)||defined(_M8HVADEF_INC_)||defined(_M88DEF_INC_)||defined(_M88PDEF_INC_)||defined(_M88PADEF_INC_)
	Rjmp URXC0addr_Interupt
#else
	Jmp URXC0addr_Interupt
#endif
.Org Uart0SkipRxInteruptVectors
;-----------------
	Clr R16
	Sts Uart0RxFifoFlags,R16
	Sts Uart0RxFifo+0,R16
	Sts Uart0RxFifo+1,R16
	Sts Uart0RxFifo+2,R16
	Sts Uart0RxFifo+3,R16
	Sts Uart0RxFifo+4,R16
	Sts Uart0RxFifo+5,R16
;-----------------
.Equ Uart0PushCountRx          = 0
.Equ Uart0PushCountRxLength    = 2
.Equ Uart0PopCountRx           = Uart0PushCountRx + Uart0PushCountRxLength
.Equ Uart0PopCountRxLength     = 2
.Equ Uart0FifoCountRx		   = Uart0PopCountRx + Uart0PopCountRxLength
.Equ Uart0FifoCountLenghtRx    = 2

.Equ UartRxFifoOverflow        = 0
;-----------------
URXC0addr_Interupt:
	URXCaddr_Interupt 0
	Reti
#endif
;----------------------------------------
#ifdef Uart0TxFifoSize
Uart0SkipTxInteruptVectors:
.Org UDRE0addr
#if defined(_M48DEF_INC_)||defined(_M48PDEF_INC_)||defined(_M48PADEF_INC_)||defined(_M8DEF_INC_)||defined(_M8ADEF_INC_)||defined(_M8HVADEF_INC_)||defined(_M88DEF_INC_)||defined(_M88PDEF_INC_)||defined(_M88PADEF_INC_)
	Rjmp UDRE0addr_Interupt
#else
	Jmp UDRE0addr_Interupt
#endif
.Org Uart0SkipTxInteruptVectors
;-----------------
	Clr R16
	Sts Uart0TxFifoFlags,R16
	Sts Uart0TxFifo+0,R16
	Sts Uart0TxFifo+1,R16
	Sts Uart0TxFifo+2,R16
	Sts Uart0TxFifo+3,R16
	Sts Uart0TxFifo+4,R16
	Sts Uart0TxFifo+5,R16
;-----------------
.Equ Uart0PushCountTx          = 0
.Equ Uart0PushCountTxLength    = 2
.Equ Uart0PopCountTx           = Uart0PushCountTx + Uart0PushCountTxLength
.Equ Uart0PopCountTxLength     = 2
.Equ Uart0FifoCountTx          = Uart0PopCountTx + Uart0PopCountTxLength
.Equ Uart0FifoCountLenghtTx    = 2

.Equ UartTxFifoEmpty           = 0
;-----------------
UDRE0addr_Interupt:
	UDREaddr_Interupt 0
	Reti
#endif
;----------------------------------------
#endif
;********************************************************************************************************************************************************
;********************************************************************************************************************************************************
#ifdef Uart1Exist
#ifndef Uart1Enabled
//#message ">>>>>>For enable Uart1 macros please define ( Uart1Enabled ) constant. Ex: #define Uart1Enabled"
#endif
.Macro Inline_Uart1U2xEnable
	Inline_UartU2xEnable 1,@0
.EndM
.Macro Inline_Uart1Baut
	Inline_UartBaut 1,@0
.EndM
.Macro Inline_Uart1BautU2x
	Inline_UartBautU2x 1,@0
.EndM
.Macro Inline_Uart1BitsNr
	Inline_UartBitsNr 1,@0
.EndM
.Macro Inline_Uart1Parity
	Inline_UartParity 1,@0
.EndM
.Macro Inline_Uart1StopBits
	Inline_UartStopBits 1,@0
.EndM
.Macro Inline_Uart1SincEnable
	Inline_UartSincEnable 1,@0
.EndM
.Macro Inline_Uart1MultiprocesorEnable
	Inline_UartMultiprocesorEnable 1,@0
.EndM
.Macro Inline_Uart1RxIntEnable
	Inline_UartRxIntEnable 1,@0
.EndM
.Macro Inline_Uart1TxIntEnable
	Inline_UartTxIntEnable 1,@0
.EndM
.Macro Inline_Uart1UdreIntEnable
	Inline_UartUdreIntEnable 1,@0
.EndM
.Macro Inline_Uart1TxEnable
	Inline_UartTxEnable 1,@0
.EndM
.Macro Inline_Uart1RxEnable
	Inline_UartRxEnable 1,@0
.EndM
.Macro Inline_Uart1SendRegChar
	Inline_UartSendRegChar 1,@0
.EndM
.Macro Inline_Uart1SendConstChar
	Inline_UartSendConstChar 1,@0
.EndM
.Macro Inline_Uart1ReceiveChar
	Inline_UartReceiveChar 1,@0
.EndM
.Macro Inline_Uart1FlashConstStrSend
	Inline_UartFlashConstStrSend 1,@0
.EndM
.Macro Inline_Uart1RamConstStrSend
	Inline_UartRamConstStrSend 1,@0
.EndM
.Macro Inline_Uart1RamVarStrSend
	Inline_UartRamVarStrSend 1,@0
.EndM
.Macro Inline_Uart1Setup
	Inline_UartSetup 1,@0,@1,@2,@3,@4,@5,@6,@7,@8;Default Setup
.EndM
.Macro Inline_Uart1ForceReceiveChar
	Inline_UartForceReceiveChar 1,@0
.EndM
.Macro Inline_Uart1StrSend
    Inline_UartStrSend 1,@0
.EndM
#endif
;********************************************************************************************************************************************************
;********************************************************************************************************************************************************
#ifdef Uart2Exist
#ifndef Uart2Enabled
#message ">>>>>>For enable Uart2 macros please define ( Uart2Enabled ) constant. Ex: #define Uart2Enabled"
#endif
.Macro Inline_Uart2U2xEnable
	Inline_UartU2xEnable 2,@0
.EndM
.Macro Inline_Uart2Baut
	Inline_UartBaut 2,@0
.EndM
.Macro Inline_Uart2BautU2x
	Inline_UartBautU2x 2,@0
.EndM
.Macro Inline_Uart2BitsNr
	Inline_UartBitsNr 2,@0
.EndM
.Macro Inline_Uart2Parity
	Inline_UartParity 2,@0
.EndM
.Macro Inline_Uart2StopBits
	Inline_UartStopBits 2,@0
.EndM
.Macro Inline_Uart2SincEnable
	Inline_UartSincEnable 2,@0
.EndM
.Macro Inline_Uart2MultiprocesorEnable
	Inline_UartMultiprocesorEnable 2,@0
.EndM
.Macro Inline_Uart2RxIntEnable
	Inline_UartRxIntEnable 2,@0
.EndM
.Macro Inline_Uart2TxIntEnable
	Inline_UartTxIntEnable 2,@0
.EndM
.Macro Inline_Uart2UdreIntEnable
	Inline_UartUdreIntEnable 2,@0
.EndM
.Macro Inline_Uart2TxEnable
	Inline_UartTxEnable 2,@0
.EndM
.Macro Inline_Uart2RxEnable
	Inline_UartRxEnable 2,@0
.EndM
.Macro Inline_Uart2SendRegChar
	Inline_UartSendRegChar 2,@0
.EndM
.Macro Inline_Uart2SendConstChar
	Inline_UartSendConstChar 2,@0
.EndM
.Macro Inline_Uart2ReceiveChar
	Inline_UartReceiveChar 2,@0
.EndM
.Macro Inline_Uart2FlashConstStrSend
	Inline_UartFlashConstStrSend 2,@0
.EndM
.Macro Inline_Uart2RamConstStrSend
	Inline_UartRamConstStrSend 2,@0
.EndM
.Macro Inline_Uart2RamVarStrSend
	Inline_UartRamVarStrSend 2,@0
.EndM
.Macro Inline_Uart2Setup
	Inline_UartSetup 2,@0,@1,@2,@3,@4,@5,@6,@7,@8;Default Setup
.EndM
.Macro Inline_Uart2ForceReceiveChar
	Inline_UartForceReceiveChar 2,@0
.EndM
.Macro Inline_Uart2StrSend
    Inline_UartStrSend 2,@0
.EndM
#endif
;********************************************************************************************************************************************************
;********************************************************************************************************************************************************
#ifdef Uart3Exist
#ifndef Uart1Enabled
#message ">>>>>>For enable Uart3 macros please define ( Uart3Enabled ) constant. Ex: #define Uart3Enabled"
#endif
.Macro Inline_Uart3U2xEnable
	Inline_UartU2xEnable 3,@0
.EndM
.Macro Inline_Uart3Baut
	Inline_UartBaut 3,@0
.EndM
.Macro Inline_Uart3BautU2x
	Inline_UartBautU2x 3,@0
.EndM
.Macro Inline_Uart3BitsNr
	Inline_UartBitsNr 3,@0
.EndM
.Macro Inline_Uart3Parity
	Inline_UartParity 3,@0
.EndM
.Macro Inline_Uart3StopBits
	Inline_UartStopBits 3,@0
.EndM
.Macro Inline_Uart3SincEnable
	Inline_UartSincEnable 3,@0
.EndM
.Macro Inline_Uart3MultiprocesorEnable
	Inline_UartMultiprocesorEnable 3,@0
.EndM
.Macro Inline_Uart3RxIntEnable
	Inline_UartRxIntEnable 3,@0
.EndM
.Macro Inline_Uart3TxIntEnable
	Inline_UartTxIntEnable 3,@0
.EndM
.Macro Inline_Uart3UdreIntEnable
	Inline_UartUdreIntEnable 3,@0
.EndM
.Macro Inline_Uart3TxEnable
	Inline_UartTxEnable 3,@0
.EndM
.Macro Inline_Uart3RxEnable
	Inline_UartRxEnable 3,@0
.EndM
.Macro Inline_Uart3SendRegChar
	Inline_UartSendRegChar 3,@0
.EndM
.Macro Inline_Uart3SendConstChar
	Inline_UartSendConstChar 3,@0
.EndM
.Macro Inline_Uart3ReceiveChar
	Inline_UartReceiveChar 3,@0
.EndM
.Macro Inline_Uart3FlashConstStrSend
	Inline_UartFlashConstStrSend 3,@0
.EndM
.Macro Inline_Uart3RamConstStrSend
	Inline_UartRamConstStrSend 3,@0
.EndM
.Macro Inline_Uart3RamVarStrSend
	Inline_UartRamVarStrSend 3,@0
.EndM
.Macro Inline_Uart3Setup
	Inline_UartSetup 3,@0,@1,@2,@3,@4,@5,@6,@7,@8;Default Setup
.EndM
.Macro Inline_Uart3ForceReceiveChar
	Inline_UartForceReceiveChar 3,@0
.EndM
.Macro Inline_Uart3StrSend
    Inline_UartStrSend 3,@0
.EndM
#endif
;********************************************************************************************************************************************************
;********************************************************************************************************************************************************
;********************************************************************************************************************************************************
;********************************************************************************************************************************************************
.Macro Inline_UartSendConstChar; @0 = uart number,@1 Char to send
	Push R16
.if RegUCSR@0A == Port
USART@0_Transmit:
	Sbis UCSR@0A,UDRE@0
	Rjmp USART@0_Transmit
.elif RegUCSR@0A == Sram
USART@0_Transmit:
	Lds R16,UCSR@0A
	Sbrs R16,UDRE@0
	Rjmp USART@0_Transmit
.endif
	Ldi R16,@1
#if defined(_M8DEF_INC_)||defined(_M8ADEF_INC_)||defined(_M16DEF_INC_)||defined(_M16ADEF_INC_)||defined(_M32DEF_INC_)||defined(_M32ADEF_INC_)||defined(_M323ADEF_INC_)
.if RegUDR@0 == Sram
	Sts UDR,R16
.elif RegUDR@0 == Port
	Out UDR,R16
.endif
#else
.if RegUDR@0 == Sram
	Sts UDR@0,R16
.elif RegUDR@0 == Port
	Out UDR@0,R16
.endif
	Pop R16
#endif
.EndM
;----------------------------------------
.Macro Inline_UartSendRegChar; @0 = uart number,@1 Char to send In R0 to R31
USART_Transmit:
.Set _USART_Transmit = USART_Transmit
.if RegUCSR@0A == Port
USART@0_Transmit:
	Sbis UCSR@0A,UDRE@0
	Rjmp USART@0_Transmit
.elif RegUCSR@0A == Sram
	Push @1
USART@0_Transmit:
	Lds @1,UCSR@0A
	Sbrs @1,UDRE@0
	Rjmp USART@0_Transmit
	Pop @1
.endif
	//_JmpPortBitClr UCSR@0A,UDRE@0,_USART_Transmit
	_WritePort UDR@0,@1
#if defined(_M8DEF_INC_)||defined(_M8ADEF_INC_)||defined(_M16DEF_INC_)||defined(_M16ADEF_INC_)||defined(_M32DEF_INC_)||defined(_M32ADEF_INC_)||defined(_M323ADEF_INC_)
.if RegUDR@0 == Sram
	Sts UDR,@1
.elif RegUDR@0 == Port
	Out UDR,@1
.endif
#else
.if RegUDR@0 == Sram
	Sts UDR@0,@1
.elif RegUDR@0 == Port
	Out UDR@0,@1
.endif
#endif
.EndM
;********************************************************************************************************************************************************
.Macro Inline_UartReceiveChar
.if RegUCSR@0A == Sram
	Push R16
USART@0_Receive:
	Wdr
	Lds R16,UCSR@0A
	Sbrs R16, RXC@0
	Rjmp USART@0_Receive
	Pop R16
.elif RegUCSR@0A == Port
USART@0_Receive:
	Wdr
	Sbis UCSR@0A, RXC@0
	Rjmp USART@0_Receive
.endif
#if defined(_M8DEF_INC_)||defined(_M8ADEF_INC_)||defined(_M16DEF_INC_)||defined(_M16ADEF_INC_)||defined(_M32DEF_INC_)||defined(_M32ADEF_INC_)||defined(_M323ADEF_INC_)
.if RegUDR@0 == Sram
	Lds @1,UDR
.elif RegUDR@0 == Port
	In @1,UDR
.endif
#else
.if RegUDR@0 == Sram
	Lds @1,UDR@0
.elif RegUDR@0 == Port
	In @1,UDR@0
.endif
#endif
.EndM
;********************************************************************************************************************************************************
.Macro Inline_UartForceReceiveChar
.if RegUCSR@0A == Sram
	Push @1
	Lds @1,UCSR@0A
	Sbrs @1, RXC@0
	Rjmp ReturnFromInline_Uart@0ForceReceiveChar
	Pop @1
.elif RegUCSR@0A == Port
	Sbis UCSR@0A, RXC@0
	Rjmp ReturnFromInline_Uart@0ForceReceiveChar
.endif
#if defined(_M8DEF_INC_)||defined(_M8ADEF_INC_)||defined(_M16DEF_INC_)||defined(_M16ADEF_INC_)||defined(_M32DEF_INC_)||defined(_M32ADEF_INC_)||defined(_M323ADEF_INC_)
.if RegUDR@0 == Sram
	Lds @1,UDR
.elif RegUDR@0 == Port
	In @1,UDR
.endif
#else
.if RegUDR@0 == Sram
	Lds @1,UDR@0
.elif RegUDR@0 == Port
	In @1,UDR@0
.endif
#endif
	Rjmp ReturnFromInline_Uart@0ForceReceiveChar_
ReturnFromInline_Uart@0ForceReceiveChar:
.if RegUCSR@0A == Sram
	Pop @1
.endif
	Clt
ReturnFromInline_Uart@0ForceReceiveChar_:
.EndM
;********************************************************************************************************************************************************
;String Description
;LowStringDimension,HighStringDimension,String
.Macro Inline_UartFlashConstStrSend
	Push R0
	Push Yl
	Push Yh
	Push Zl
	Push Zh
	Ldi Zl,Low(@1*2)
	Ldi Zh,High(@1*2)
	Lpm Yl,Z+
	Lpm Yh,Z+
LoopUartFlashConstStrSend:
	Wdr
	Lpm R0,Z+
	Inline_UartSendRegChar @0,R0
	Sbiw Yl:Yh,1
	Brne LoopUartFlashConstStrSend
	Pop Zh
	Pop Zl
	Pop Yh
	Pop Yl
	Pop R0
.EndM
;********************************************************************************************************************************************************
;String Description
;LowMaxStringDimension,HighMaxStringDimension,LowStringDimension,HighStringDimension,String
.Macro Inline_UartRamConstStrSend
	Push R0
	Push Yl
	Push Yh
	Push Zl
	Push Zh
	Ldi Zl,Low(@1*2)
	Ldi Zh,High(@1*2)
	Adiw Zl:Zh,2
	Ld Yl,Z+
	Ld Yh,Z+
LoopUartFlashConstStrSend:
	Ld R0,Z+
	Inline_UartSendRegChar @0,R0
	Sbiw Yl:Yh,1
	Brne LoopUartFlashConstStrSend
	Pop Zh
	Pop Zl
	Pop Yh
	Pop Yl
	Pop R0
.EndM
;********************************************************************************************************************************************************
;String Description
;LowMaxStringDimension,HighMaxStringDimension,LowStringDimension,HighStringDimension,String
.Macro Inline_UartRamVarStrSend
	Push R0
	Push R24
	Push R25
	Push @1l
	Push @1h
	Adiw @1l:@1h,2
	Ld R24,@1+
	Ld R25,@1+
LoopUartFlashConstStrSend:
	Ld R0,@1+
	Inline_UartSendRegChar @0,R0
	Sbiw R24:R25,1
	Brne LoopUartFlashConstStrSend
	Pop @1h
	Pop @1l
	Pop R25
	Pop R24
	Pop R0
.EndM
;********************************************************************************************************************************************************
.Macro Inline_UartStrSend
    Rjmp _Uart_Const_StringLocation_End
_Uart_Const_StringLocation:
.if (((STRLEN(@1))/2)*2) == STRLEN(@1)
.db @1
.else
.db @1,255
.endif
_Uart_Const_StringLocation_End:
	Push R16
	Push R17
	Push Zl
	Push Zh
	Ldi R17,STRLEN(@1)
	Ldi Zl,Low(_Uart_Const_StringLocation*2)
	Ldi Zh,High(_Uart_Const_StringLocation*2)
_Loop_UartsSendConst:
	Wdr
    Lpm R16,Z+
    Inline_UartSendRegChar @0,R16
    Dec R17
	Brne _Loop_UartsSendConst
	Pop Zh
	Pop Zl
	Pop R17
    Pop R16
.EndM
;********************************************************************************************************************************************************
;********************************************************************************************************************************************************
;********************************************************************************************************************************************************
;********************************************************************************************************************************************************
;********************************************************************************************************************************************************
;********************************************************************************************************************************************************
;********************************************************************************************************************************************************
;********************************************************************************************************************************************************
;********************************************************************************************************************************************************
;********************************************************************************************************************************************************
;DriverUarts
;********************************************************************************************************************************************************
//Uart1Driver:;Offsets
	;Rcall SetupDriverUart;Setup Interface
	;Rjmp EndDriverUart
	;Rjmp SetupDriverUart;Setup Interface
;********************************************************************************************************************************************************
;********************************************************************************************************************************************************
;********************************************************************************************************************************************************
DefaultSetupDriverUart:
#ifdef Uart0Exist
	//Inline_Uart0Setup True,19200,Tx_Rx_Enabled,Tx_Rx_Udre_Int_Disabled,8,False,1,False,False;Default Setup
#endif
#ifdef Uart1Exist
	//Inline_Uart1Setup True,19200,Tx_Rx_Disabled,Tx_Rx_Udre_Int_Disabled,8,False,1,False,False;Default Setup
#endif
#ifdef Uart2Exist
	//Inline_Uart2Setup True,19200,Tx_Rx_Disabled,Tx_Rx_Udre_Int_Disabled,8,False,1,False,False;Default Setup
#endif
#ifdef Uart3Exist
	//Inline_Uart3Setup True,19200,Tx_Rx_Disabled,Tx_Rx_Udre_Int_Disabled,8,False,1,False,False;Default Setup
#endif
	;Ret
;********************************************************************************************************************************************************
EndDriverUart:
#endif
#endif
#endif
#endif
//#endif
