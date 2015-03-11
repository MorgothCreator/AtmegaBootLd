/*
 * BootLdV1.asm
 *
 *  Created: 1/27/2015 4:14:35 PM
 *   Author: eu
 */ 


// .Include "m328Pdef.inc"
#define CoreFrequ[8000000]
#define __RWEEPROM__
.Equ UartUsed                       = 0
.Equ BaudRate						= 38400
.Equ HexBufferLenght				= 100;43 Generic
.Equ BinBufferLength                = HexBufferLenght/2
.Equ TimeToWaitEnterInBootLoader    = 2
.Equ TimeToWaitReceiveChar          = (CoreFrequ/(CoreFrequ/(65536*11)))*TimeToWaitEnterInBootLoader
;---------------------------------------------------------------------------
;Intel hex definitions
.Equ Data_Record					= 0;Contains data and 16-bit address. The format described above.
.Equ EndOfFile_Record				= 1;A file termination record. No data. Has to be the last line of the file, only one per file permitted. Usually ':00000001FF'. Originally the End Of File record could contain a start address for the program being loaded, e.g. :00AB2F0125 would make a jump to address AB2F. This was convenient when programs were loaded from punched paper tape.
.Equ ExtendedSegmentAddress_Record	= 2;Segment-base address. Used when 16 bits are not enough, identical to 80x86 real mode addressing. The address specified by the 02 record is multiplied by 16 (shifted 4 bits left) and added to the subsequent 00 record addresses. This allows addressing of up to a megabyte of address space. The address field of this record has to be 0000, the byte count is 02 (the segment is 16-bit). The least significant hex digit of the segment address is always 0.
.Equ StartSegmentAddress_Record     = 3;For 80x86 processors, it specifies the initial content of the CS:IP registers. The address field is 0000, the byte count is 04, the first two bytes are the CS value, the latter two are the IP value.
.Equ ExtendedLinearAddress_Record	= 4;Allowing for fully 32 bit addressing. The address field is 0000, the byte count is 02. The two data bytes represent the upper 16 bits of the 32 bit address, when combined with the address of the 00 type record.
.Equ StartLinearAddress_Record		= 5;The address field is 0000, the byte count is 04. The 4 data bytes represent the 32-bit value loaded into the EIP register of the 80386 and higher CPU.
;---------------------------------------------------------------------------
;Errors 
.Equ Error_LineDefError             = 'a'
.Equ Error_SecondHexCharNotFound    = 'b'
.Equ Error_CheckSum                 = 'c'
.Equ Error_LineMismach              = 'd'
.Equ Error_NoMemorySelected         = 'e'
;---------------------------------------------------------------------------
.Include "BoardDefinitions.asm"
.Include "IO_Uarts.inc"
.Include "IO_Port.inc"
;***************************************************************************
;Macro section
.Macro SubiWord
	Subi @0,Low(@4)
	Sbci @1,Byte2(@4)
	Sbci @2,Byte3(@4)
	Sbci @3,Byte4(@4)
.EndM
;***************************************************************************
.Dseg
.Org SRAM_START
FlashPageBuffer:                    .Byte PAGESIZE*2
RxHexBuffer:						.Byte HexBufferLenght
RxBinBuffer:                        .Byte BinBufferLength
ExtendedSegmentAddressRecord_:		.Byte 3
RegPageInBuffer:					.Byte 3
RegFlashEEPromWriteMode:            .Byte 1
.Cseg
;***************************************************************************
//.Org 00
//	Jmp UserProgramReset
//.Org INT_VECTORS_SIZE
//UserProgramReset:
//	SetPortBit DirLedG,LedG
//	SetPortBit PortLedG,LedG
//Idle0000:
//	Wdr
//	Rjmp Idle0000
;***************************************************************************
//#define Uart0Enabled
.Org FLASHEND - 511
;***************************************************************************
BootLoaderInit:
	Ldi R16,Low(RAMEND)
	Out Spl,R16
	Ldi R16,High(RAMEND)
	Out Sph,R16
;---------------------------------------------------------------------------
;Init Virtual registri
	Rcall ClearBuff
;***************************************************************************
;Init Used Uart
.if UartUsed == 0
	Ldi R16,(1<<RXEN0)|(1<<TXEN0)
	_WritePort UCSR0B,R16
	Ldi R16,High((CoreFrequ/16/BaudRate)-1)
	_WritePort UBRR0H,R16
	Ldi R16,Low((CoreFrequ/16/BaudRate)-1)
	_WritePort UBRR0L,R16
;-------------------------
.elif UartUsed == 1
	Ldi R16,(1<<RXEN1)|(1<<TXEN1)
	_WritePort UCSR1B,R16
	Ldi R16,High((CoreFrequ/16/BaudRate)-1)
	_WritePort UBRR1H,R16
	Ldi R16,Low((CoreFrequ/16/BaudRate)-1)
	_WritePort UBRR1L,R16
;-------------------------
.elif UartUsed == 2
	Ldi R16,(1<<RXEN2)|(1<<TXEN2)
	_WritePort UCSR2B,R16
	Ldi R16,High((CoreFrequ/16/BaudRate)-1)
	_WritePort UBRR2H,R16
	Ldi R16,Low((CoreFrequ/16/BaudRate)-1)
	_WritePort UBRR2L,R16
;-------------------------
.elif UartUsed == 3
	Ldi R16,(1<<RXEN3)|(1<<TXEN3)
	_WritePort UCSR3B,R16
	Ldi R16,High((CoreFrequ/16/BaudRate)-1)
	_WritePort UBRR3H,R16
	Ldi R16,Low((CoreFrequ/16/BaudRate)-1)
	_WritePort UBRR3L,R16
.endif
;***************************************************************************
	Rcall LoadTimeoutTime
LoopWaitReceiveCharsToEnterInBootLoader:
	Set
	Wdr
	Rcall Inline_UartForceReceiveChar_
	Brtc NoReceivedCharInWaitToEnterInBootloader
	Cpi R20,0x0D
	Breq VerifyIfIsLineToEnterInBootLoader
	Rcall RxPushCharInBuffer
NoReceivedCharInWaitToEnterInBootloader:
	Rcall SubWordR16
	Brne LoopWaitReceiveCharsToEnterInBootLoader
//.if UartUsed == 0
//	Inline_Uart0FlashConstStrSend ResponseToAbortBootLoader
//.elif UartUsed == 1
//	Inline_Uart1FlashConstStrSend ResponseToAbortBootLoader
//.elif UartUsed == 2
//	Inline_Uart2FlashConstStrSend ResponseToAbortBootLoader
//.elif UartUsed == 3
//	Inline_Uart3FlashConstStrSend ResponseToAbortBootLoader
//.endif
	Rjmp ReturnInUserProgram
;---------------------------------------------------------------------------
VerifyIfIsLineToEnterInBootLoader:
	Set
#if defined(_M128DEF_INC_) || defined(_M1280DEF_INC_) || defined(_M1281DEF_INC_) || defined(_M1284PDEF_INC_) || defined(_M2560DEF_INC_) || defined(_M2561DEF_INC_)
	Ldi Zl,Byte3(EnterBootLoaderStrCommand*2)
	Out RAMPZ,Zl
#endif
	Ldi Zl,Low(EnterBootLoaderStrCommand*2)
	Ldi Zh,Byte2(EnterBootLoaderStrCommand*2)
	Ldi Xl,Low(RxHexBuffer)
	Ldi Xh,High(RxHexBuffer)
	Rcall CompRamVarStrToFlashConstStr
	Brtc NoEnterToBotLoaderCommandFound
	Rcall BootLoader
NoEnterToBotLoaderCommandFound:
	Rcall ClearBuff; RxHexBuffer,HexBufferLenght
	Rjmp LoopWaitReceiveCharsToEnterInBootLoader
;***************************************************************************
;***************************************************************************
BootLoader:
//Alea:
	//_SetPortBit DirLedY,LedY
	//_SetPortBit PortLedY,LedY
	//Rjmp Alea
//	Ldi Zl,Low(ResponseToEnterInBootLoader*2)
//	Ldi Zh,High(ResponseToEnterInBootLoader*2)
//	Lpm Yl,Z+
//	Lpm Yh,Z+
//LoopUartFlashConstStrSend:
//	Wdr
//	Lpm R25,Z+
//	Rcall SendResponse
//	Sbiw Yl:Yh,1
//	Brne LoopUartFlashConstStrSend
;---------------------------------------------------------------------------
;Push hex chars to buffer
	Clr R16
	Sts RegPageInBuffer+0,R16
	Sts RegPageInBuffer+1,R16
	Sts RegPageInBuffer+2,R16
	Ser R16
	Sts RegFlashEEPromWriteMode,R16
	Rcall ReadPageInBuffer
	Rcall ClearExtendedAdressVariable
ReceiveHexLine:
	Rcall ClearBuff; RxHexBuffer,HexBufferLenght
	Ldi R25,'k'
	Rcall SendResponse
	Rcall LoadTimeoutTime
LoopWaitHexChar:
	Set
	Wdr
	Rcall Inline_UartForceReceiveChar_
	Brtc NoReceivedCharInWaitReceiveHexChar
	Cpi R20,0x0D
	Breq ProcessReceivedLine
	Rcall RxPushCharInBuffer
NoReceivedCharInWaitReceiveHexChar:
	Rcall SubWordR16
	Brne LoopWaitHexChar
	Rjmp ReturnInUserProgram
;---------------------------------------------------------------------------
;---------------------------------------------------------------------------
ProcessReceivedLine:
	Set
#if defined(_M128DEF_INC_) || defined(_M1280DEF_INC_) || defined(_M1281DEF_INC_) || defined(_M1284PDEF_INC_) || defined(_M2560DEF_INC_) || defined(_M2561DEF_INC_)
	Ldi Zl,Byte3(EnteringFlashModeStrCommend*2)
	_WritePort RAMPZ,Zl
#endif
	Ldi Zl,Low(EnteringFlashModeStrCommend*2)
	Ldi Zh,High(EnteringFlashModeStrCommend*2)
	Ldi Xl,Low(RxHexBuffer)
	Ldi Xh,High(RxHexBuffer)
	Rcall CompRamVarStrToFlashConstStr
	Brtc NoFlashWriteSelectionFound
	Ldi R16,0
	Sts RegFlashEEPromWriteMode,R16
	Rcall ClearExtendedAdressVariable
	Rjmp ReceiveHexLine
;---------------------------------------------------------------------------
NoFlashWriteSelectionFound:
	Set
#if defined(_M128DEF_INC_) || defined(_M1280DEF_INC_) || defined(_M1281DEF_INC_) || defined(_M1284PDEF_INC_) || defined(_M2560DEF_INC_) || defined(_M2561DEF_INC_)
	Ldi Zl,Byte3(EnteringEEPromModeStrCommend*2)
	Out RAMPZ,Zl
#endif
	Ldi Zl,Low(EnteringEEPromModeStrCommend*2)
	Ldi Zh,High(EnteringEEPromModeStrCommend*2)
	Ldi Xl,Low(RxHexBuffer)
	Ldi Xh,High(RxHexBuffer)
	Rcall CompRamVarStrToFlashConstStr
	Brtc NoEEPromWriteSelectionFound
	Ldi R16,1
	Sts RegFlashEEPromWriteMode,R16
	Rcall ClearExtendedAdressVariable
	Rjmp ReceiveHexLine
;---------------------------------------------------------------------------
NoEEPromWriteSelectionFound:
	Set
#if defined(_M128DEF_INC_) || defined(_M1280DEF_INC_) || defined(_M1281DEF_INC_) || defined(_M1284PDEF_INC_) || defined(_M2560DEF_INC_) || defined(_M2561DEF_INC_)
	Ldi Zl,Byte3(EnteringExitStrCommend*2)
	Out RAMPZ,Zl
#endif
	Ldi Zl,Low(EnteringExitStrCommend*2)
	Ldi Zh,High(EnteringExitStrCommend*2)
	Ldi Xl,Low(RxHexBuffer)
	Ldi Xh,High(RxHexBuffer)
	Rcall CompRamVarStrToFlashConstStr
	Brtc NoExitCommandFound
	Ldi R25,'f'
	Rcall SendResponse
	Rcall SaveBuffer
	Rjmp ReturnInUserProgram
;---------------------------------------------------------------------------
NoExitCommandFound:
	Set
	Rcall ConvertHexLineToByteLine
	Brts NoErrorFoundInreCeivedLine
	Ldi R25,Error_SecondHexCharNotFound;Error second hex char not found
	Rcall SendResponse
	Rjmp ReturnInUserProgram
NoErrorFoundInreCeivedLine:
	Ldi Yl,Low(RxBinBuffer)
	Ldi Yh,High(RxBinBuffer)
	Ld R2,Y+;Number of Bytes in Bin buffer
	Ld R3,Y+;Number of data bytes in buffer
	Mov R22,R2
	Subi R22,5
	Cp R3,R22
	Breq LineAndNumberOfDataIsMach
	Ldi R25,Error_LineMismach
	Rcall SendResponse
	Rjmp ReturnInUserProgram
LineAndNumberOfDataIsMach:
	Ld R5,Y+;High address to write data
	Ld R4,Y+;Low address to write data
	Ld R21,Y+;Line function
	Mov R6,R3
	Add R6,R4
	Add R6,R5
	Add R6,R21
;---------------------------------------------------------------------------
	Cpi R21,Data_Record
	Brne No_Data_Record_LineFound
	Lds Zl,ExtendedSegmentAddressRecord_+0
	Lds Zh,ExtendedSegmentAddressRecord_+1
#if defined(_M128DEF_INC_) || defined(_M1280DEF_INC_) || defined(_M1281DEF_INC_) || defined(_M1284PDEF_INC_) || defined(_M2560DEF_INC_) || defined(_M2561DEF_INC_)
	Push R16
	Lds R16,ExtendedSegmentAddressRecord_+2
	Push R17
	Clr R17
#endif
	Add Zl,R4
	Adc Zh,R5
#if defined(_M128DEF_INC_) || defined(_M1280DEF_INC_) || defined(_M1281DEF_INC_) || defined(_M1284PDEF_INC_) || defined(_M2560DEF_INC_) || defined(_M2561DEF_INC_)
	Adc R16,R17
	Pop R17
	_WritePort RAMPZ,R16
	Pop R16
#endif
	Rcall WriteDataInPage
	Rjmp ReceiveHexLine
No_Data_Record_LineFound:
;---------------------------------------------------------------------------
	Cpi R21,EndOfFile_Record
	Brne No_EndOfFile_Record_LineFound
	Rcall GoToEndOfLineAndVerifyChecksum
	Rjmp ReceiveHexLine
No_EndOfFile_Record_LineFound:
;---------------------------------------------------------------------------
	Cpi R21,ExtendedSegmentAddress_Record
	Brne No_ExtendedSegmentAddress_Record_LineFound
	Ld R14,Y+
	Ld R13,Y+
	Clr R15
	Ldi R16,4
LoopConvertExtendedAdress:
	Lsl R13
	Rol R14
	Rol R15
	Dec R16
	Brne LoopConvertExtendedAdress
	Sts ExtendedSegmentAddressRecord_+0,R13
	Sts ExtendedSegmentAddressRecord_+1,R14
	Sts ExtendedSegmentAddressRecord_+2,R15
	Rjmp ReceiveHexLine
No_ExtendedSegmentAddress_Record_LineFound:
;---------------------------------------------------------------------------
	//Cpi R21,StartSegmentAddress_Record
	//Brne No_StartSegmentAddress_Record_LineFound
	//Rcall ClearExtendedAdressVariable
	//Rjmp ReceiveHexLine
//No_StartSegmentAddress_Record_LineFound:
;---------------------------------------------------------------------------
	Ldi R25,Error_LineDefError;Error Line definition not found
	Rcall SendResponse
	Rjmp ReturnInUserProgram
;***************************************************************************
;***************************************************************************
;***************************************************************************
;General routines
WriteDataInPage:
#ifdef LedBootL
	_SetPortBit DirLedBootL,LedBootL
	_SetPortBit PortLedBootL,LedBootL
#endif
	Lds R16,RegFlashEEPromWriteMode
	Cpi R16,0
	Breq IdWriteToFlash
	Cpi R16,1
	Breq IdWriteToEEProm
	Ldi R25,Error_NoMemorySelected
	Rcall SendResponse
	Rcall ReturnInUserProgram
IdWriteToFlash:
IdWriteToEEProm:
LoopWriteLineInPage:
	Ld R21,Y+
	Add R6,R21
	Lds R16,RegFlashEEPromWriteMode
	Cpi R16,0
	Brne ThisIsEEPromWriteMode
	Rcall AppendByteInPage
	Rjmp ReturnFromFlashWriteByte
ThisIsEEPromWriteMode:
	Movw Xl:Xh,Zl:Zh
	Mov R16,R21
	Rcall _RWEEPROM
ReturnFromFlashWriteByte:
	Adiw Zl:Zh,1
	Dec R22
	Brne LoopWriteLineInPage
	Rcall GoToEndOfLineAndVerifyChecksum
#ifdef LedBootL
	_ClrPortBit DirLedBootL,LedBootL
	_ClrPortBit PortLedBootL,LedBootL
#endif
	Ret
;***************************************************************************
AppendByteInPage:
	Push R14
	Push R15
	Push Zl
	Push Zh
	//Push Zl
	Mov R23,Zl
.if PAGESIZE == 32
	Andi R23,0b00111111
.elif PAGESIZE == 64
	Andi R23,0b01111111
.endif
	//Mov R23,Zl
	//Pop Zl
.if PAGESIZE == 32
	Andi Zl,0b11000000
.elif PAGESIZE == 64
	Andi Zl,0b10000000
.elif PAGESIZE == 128
	Clr Zl
.endif
#if defined(_M128DEF_INC_) || defined(_M1280DEF_INC_) || defined(_M1281DEF_INC_) || defined(_M1284PDEF_INC_) || defined(_M2560DEF_INC_) || defined(_M2561DEF_INC_)
	_ReadPort R14,RAMPZ
#endif
	Lds R24,RegPageInBuffer+0
	Lds R25,RegPageInBuffer+1
#if defined(_M128DEF_INC_) || defined(_M1280DEF_INC_) || defined(_M1281DEF_INC_) || defined(_M1284PDEF_INC_) || defined(_M2560DEF_INC_) || defined(_M2561DEF_INC_)
	Lds R15,RegPageInBuffer+2
#endif
	Cp R24,Zl
	Cpc R25,Zh
#if defined(_M128DEF_INC_) || defined(_M1280DEF_INC_) || defined(_M1281DEF_INC_) || defined(_M1284PDEF_INC_) || defined(_M2560DEF_INC_) || defined(_M2561DEF_INC_)
	Cpc R15,R14
#endif
	Breq ThePointedPageIsTheSameWithPageFromBuffer
	Sts RegPageInBuffer+0,Zl
	Sts RegPageInBuffer+1,Zh
#if defined(_M128DEF_INC_) || defined(_M1280DEF_INC_) || defined(_M1281DEF_INC_) || defined(_M1284PDEF_INC_) || defined(_M2560DEF_INC_) || defined(_M2561DEF_INC_)
	Sts RegPageInBuffer+2,R14
#endif
	Movw Zl:Zh,R24:R25
#if defined(_M128DEF_INC_) || defined(_M1280DEF_INC_) || defined(_M1281DEF_INC_) || defined(_M1284PDEF_INC_) || defined(_M2560DEF_INC_) || defined(_M2561DEF_INC_)
	_WritePort RAMPZ,R15
#endif
	Rcall Write_page
	Rcall ReadPageInBuffer
ThePointedPageIsTheSameWithPageFromBuffer:
	Ldi Xl,Low(FlashPageBuffer)
	Ldi Xh,High(FlashPageBuffer)
	Clr R0
	Add Xl,R23
	Adc Xh,R0
	St X,R21	
	Pop Zh
	Pop Zl
	Pop R15
	Pop R14
	Ret
;***************************************************************************
SaveBuffer:
	Lds Zl,RegPageInBuffer+0
	Lds Zh,RegPageInBuffer+1
#if defined(_M128DEF_INC_) || defined(_M1280DEF_INC_) || defined(_M1281DEF_INC_) || defined(_M1284PDEF_INC_) || defined(_M2560DEF_INC_) || defined(_M2561DEF_INC_)
	Push R15
	Lds R15,RegPageInBuffer+2
	_WritePort RAMPZ,R15
	Pop R15
#endif
	Rcall Write_page
	Ret
;***************************************************************************
Inline_UartForceReceiveChar_:
.if UartUsed == 0
.if RegUCSR0A == Sram
	_ReadPort R20,UCSR0A
	Sbrs R20, RXC0
	Rjmp ReturnFromInline_Uart0ForceReceiveChar
.elif RegUCSR0A == Port
	Sbis UCSR0A, RXC0
	Rjmp ReturnFromInline_Uart0ForceReceiveChar
.endif
	_ReadPort R20,UDR0
	Rjmp ReturnFromInline_Uart0ForceReceiveChar_
ReturnFromInline_Uart0ForceReceiveChar:
	Clt
ReturnFromInline_Uart0ForceReceiveChar_:
;---------------------
.elif UartUsed == 1
.if RegUCSR1A == Sram
	_ReadPort R20,UCSR1A
	Sbrs R20, RXC1
	Rjmp ReturnFromInline_Uart1ForceReceiveChar
.elif RegUCSR1A == Port
	Sbis UCSR1A, RXC1
	Rjmp ReturnFromInline_Uart1ForceReceiveChar
.endif
	_ReadPort R20,UDR1
	Rjmp ReturnFromInline_Uart1ForceReceiveChar_
ReturnFromInline_Uart1ForceReceiveChar:
	Clt
ReturnFromInline_Uart1ForceReceiveChar_:
;---------------------
.elif UartUsed == 2
.if RegUCSR2A == Sram
	_ReadPort R20,UCSR2A
	Sbrs R20, RXC2
	Rjmp ReturnFromInline_Uart2ForceReceiveChar
.elif RegUCSR2A == Port
	Sbis UCSR2A, RXC2
	Rjmp ReturnFromInline_Uart2ForceReceiveChar
.endif
	_ReadPort R20,UDR2
	Rjmp ReturnFromInline_Uart2ForceReceiveChar_
ReturnFromInline_Uart2ForceReceiveChar:
	Clt
ReturnFromInline_Uart2ForceReceiveChar_:
;---------------------
.elif UartUsed == 3
.if RegUCSR3A == Sram
	Lds R20,UCSR3A
	Sbrs R20, RXC3
	Rjmp ReturnFromInline_Uart3ForceReceiveChar
.elif RegUCSR3A == Port
	Sbis UCSR3A, RXC3
	Rjmp ReturnFromInline_Uart3ForceReceiveChar
.endif
	_ReadPort R20,UDR3
	Rjmp ReturnFromInline_Uart3ForceReceiveChar_
ReturnFromInline_Uart3ForceReceiveChar:
	Clt
ReturnFromInline_Uart3ForceReceiveChar_:
;---------------------
.endif
	Ret
;***************************************************************************
ClearBuff:
	//Push R16
	Ldi Xl,Low(RxHexBuffer)
	Ldi Xh,Byte2(RxHexBuffer)
	Ldi Yl,Low(HexBufferLenght)
	Ldi Yh,High(HexBufferLenght)
	Clr R16
LoopClearBuffer:
	St X+,R16
	Sbiw Yl:Yh,1
	Brne LoopClearBuffer
	//Pop R16
	Ret
;***************************************************************************
ReadPageInBuffer:
	Push R21
	Lds Zl,RegPageInBuffer+0
	Lds Zh,RegPageInBuffer+1
#if defined(_M128DEF_INC_) || defined(_M1280DEF_INC_) || defined(_M1281DEF_INC_) || defined(_M1284PDEF_INC_) || defined(_M2560DEF_INC_) || defined(_M2561DEF_INC_)
	Push R15
	Lds R15,RegPageInBuffer+2
	Out RAMPZ,R15
	Pop R15
#endif
	Ldi Xl,Low(FlashPageBuffer)
	Ldi Xh,High(FlashPageBuffer)
	Ldi R24,Low(PAGESIZE*2) ;init loop variable
	Ldi R25,High(PAGESIZE*2) ;not required for PAGESIZEB<=256
.if PAGESIZE == 32
	Andi Zl,0b11000000
.elif PAGESIZE == 64
	Andi Zl,0b10000000
.elif PAGESIZE == 128
	Clr Zl//Andi Zl,0b10000000
.endif
LoopReaPageFromPageToBuffer:
#if defined(_M128DEF_INC_) || defined(_M1280DEF_INC_) || defined(_M1281DEF_INC_) || defined(_M1284PDEF_INC_) || defined(_M2560DEF_INC_) || defined(_M2561DEF_INC_)
	Elpm R21,Z+
#else
	Lpm R21,Z+
#endif
	St X+,R21
	Sbiw R24:R25,1
	Brne LoopReaPageFromPageToBuffer
	Pop R21
	Ret
;***************************************************************************
ClearExtendedAdressVariable:
	Clr R16
	Sts ExtendedSegmentAddressRecord_+0,R16
	Sts ExtendedSegmentAddressRecord_+1,R16
	Sts ExtendedSegmentAddressRecord_+2,R16
	Ret
;***************************************************************************
SendResponse:
.if UartUsed == 0
.if RegUCSR0A == Port
USART0_Transmit:
	Sbis UCSR0A,UDRE0
	Rjmp USART0_Transmit
.elif RegUCSR0A == Sram
USART0_Transmit:
	_ReadPort R16,UCSR0A
	Sbrs R16,UDRE0
	Rjmp USART0_Transmit
.endif
	_WritePort UDR0,R25
;------------------------
.elif UartUsed == 1
.if RegUCSR1A == Port
USART1_Transmit:
	Sbis UCSR1A,UDRE1
	Rjmp USART1_Transmit
.elif RegUCSR1A == Sram
USART1_Transmit:
	_ReadPort R16,UCSR1A
	Sbrs R16,UDRE1
	Rjmp USART1_Transmit
.endif
	_WritePort UDR1,R25
;------------------------
.elif UartUsed == 2
.if RegUCSR2A == Port
USART2_Transmit:
	Sbis UCSR2A,UDRE2
	Rjmp USART2_Transmit
.elif RegUCSR2A == Sram
USART2_Transmit:
	_ReadPort R16,UCSR2A
	Sbrs R16,UDRE2
	Rjmp USART2_Transmit
.endif
	_WritePort UDR2,R25
;------------------------
.elif UartUsed == 3
.if RegUCSR3A == Port
USART3_Transmit:
	Sbis UCSR3A,UDRE3
	Rjmp USART3_Transmit
.elif RegUCSR3A == Sram
USART3_Transmit:
	_ReadPort R16,UCSR3A
	Sbrs R16,UDRE3
	Rjmp USART3_Transmit
.endif
	_WritePort UDR3,R25
.endif
	Ret
;***************************************************************************
SubWordR16:
	SubiWord R16,R17,R18,R19,1
	Ret
;***************************************************************************
GoToEndOfLineAndVerifyChecksum:
	Cpi R22,0
	Brne NoEndOfFile
	Rjmp EndOfFile
NoEndOfFile:
	Ld R21,Y+
	Add R6,R21
	Dec R22
	Brne NoEndOfFile
EndOfFile:
	Ld R21,Y
	Neg R6
	Cp R6,R21
	Breq NoErrorOnEndOfLine
	Ldi R25,Error_CheckSum
	Rcall SendResponse
	Rjmp ReturnInUserProgram
NoErrorOnEndOfLine:
	Ret
;***************************************************************************
ConvertHexLineToByteLine:
	Ldi Xl,Low(RxHexBuffer)
	Ldi Xh,High(RxHexBuffer)
	Ldi Yl,Low(RxBinBuffer+1)
	Ldi Yh,High(RxBinBuffer+1)
	Clr R23
	Ld R21,X+
	Adiw Xl:Xh,1
	Inc R21
LoopConvertLineFromHexToChar:
IsNotHexChar:
	Dec R21
	Breq EndOfLineInConvertFromHexToChar
	Ld R20,X+
	Set
	Rcall CheckIfIsHexCharAndConvert
	Brtc IsNotHexChar
	Ldi R22,16
	Mul R20,R22
	Dec R21
	Breq EndOfLineInConvertFromHexToChar
	Ld R20,X+
	Set
	Rcall CheckIfIsHexCharAndConvert
	Brtc ErrNoSecondHexChar
	Add R0,R20
	St Y+,R0
	Inc R23
	Rjmp LoopConvertLineFromHexToChar
EndOfLineInConvertFromHexToChar:
	Sts RxBinBuffer,R23
	Ret
ErrNoSecondHexChar:
	Clt
	Ret
;***************************************************************************
CheckIfIsHexCharAndConvert:
	Subi R20,'0'
	Cpi R20,':'-'0'
	Brlo CharIsLower
	Subi R20,'@'-'9'
	Cpi R20,16
	Brlo CharIsLower
	Clc
CharIsLower:
	Ret
;***************************************************************************
RxPushCharInBuffer:
	Ldi Xl,Low(RxHexBuffer)
	Ldi Xh,Byte2(RxHexBuffer)
	Ld R21,X+
	Clr R0
	Add Xl,R21
	Adc Xh,R0
	St X,R20
	Inc R21
	Cpi R21,HexBufferLenght
	Brne NoOutOfRxPushBuffer
	Clt
	Ret
NoOutOfRxPushBuffer:
	Sts RxHexBuffer,R21
	Ret
;***************************************************************************
CompRamVarStrToFlashConstStr:
	Ld R22,X+
#if defined(_M128DEF_INC_) || defined(_M1280DEF_INC_) || defined(_M1281DEF_INC_) || defined(_M1284PDEF_INC_) || defined(_M2560DEF_INC_) || defined(_M2561DEF_INC_)
	Elpm R21,Z+
#else
	Lpm R21,Z+
#endif
	Cp R22,R21
	Brne RxCommandNotFound
LoopCompRamVarStrToFlashConstStr:
	Ld R22,X+
#if defined(_M128DEF_INC_) || defined(_M1280DEF_INC_) || defined(_M1281DEF_INC_) || defined(_M1284PDEF_INC_) || defined(_M2560DEF_INC_) || defined(_M2561DEF_INC_)
	Elpm R23,Z+
#else
	Lpm R23,Z+
#endif
	Cp R22,R23
	Brne RxCommandNotFound
	Dec R21
	Brne LoopCompRamVarStrToFlashConstStr
	Rjmp ReturnCompRamVarStrToFlashConstStr
RxCommandNotFound:
	Clt
ReturnCompRamVarStrToFlashConstStr:
	Ret
;***************************************************************************
LoadTimeoutTime:
	Ldi R16,Low(TimeToWaitReceiveChar)
	Ldi R17,Byte2(TimeToWaitReceiveChar)
	Ldi R18,Byte3(TimeToWaitReceiveChar)
	Ldi R19,Byte4(TimeToWaitReceiveChar)
	Ret
;***************************************************************************
ReturnInUserProgram:
	Clr R16
.if UartUsed == 0
	_WritePort UCSR0B,R16
;------------------
.elif UartUsed == 1
	_WritePort UCSR1B,R16
;------------------
.elif UartUsed == 2
	_WritePort UCSR2B,R16
;------------------
.elif UartUsed == 3
	_WritePort UCSR3B,R16
;------------------
.endif
#if defined(_M48DEF_INC_)||defined(_M48PDEF_INC_)||defined(_M48PADEF_INC_)||defined(_M88DEF_INC_)||defined(_M88PDEF_INC_)||defined(_M88PADEF_INC_)||defined(_M8DEF_INC_)||defined(_M8ADEF_INC_)||defined(_M8HVADEF_INC_)
	Rjmp 0
#else
	Jmp 0
#endif
;***************************************************************************
.ifdef SELFPRGEN
.Equ SPMEN = SELFPRGEN
.endif

.ifdef EEPE
.Equ EEWE = EEPE
.endif

.ifdef EEMPE
.Equ EEMWE = EEMPE
.endif

;Z = Adress to write data
Write_page:
.if PAGESIZE == 32
	Andi Zl,0b11000000
.elif PAGESIZE == 64
	Andi Zl,0b10000000
.elif PAGESIZE == 128
	Clr Zl
.endif
	Ldi Xl,Low(FlashPageBuffer)
	Ldi Xh,High(FlashPageBuffer)
; Page Erase
#if defined(_M48DEF_INC_)||defined(_M48PDEF_INC_)||defined(_M88DEF_INC_)||defined(_M88PDEF_INC_)||defined(_M168DEF_INC_)||defined(_M168PDEF_INC_)
	Ldi R16, (1<<PGERS) | (1<<SELFPRGEN)
#else
	Ldi R16, (1<<PGERS) | (1<<SPMEN)
#endif
	Rcall Do_spm
; re-enable the RWW section
#if defined(_M48DEF_INC_)||defined(_M48PDEF_INC_)||defined(_M88DEF_INC_)||defined(_M88PDEF_INC_)||defined(_M168DEF_INC_)||defined(_M168PDEF_INC_)
	Ldi R16, (1<<RWWSRE) | (1<<SELFPRGEN)
#else
	Ldi R16, (1<<RWWSRE) | (1<<SPMEN)
#endif
	Rcall Do_spm
; transfer data from RAM to Flash page buffer
	Ldi R24, Low(PAGESIZE) ;init loop variable
	Ldi R25, High(PAGESIZE) ;not required for PAGESIZEB<=256
Wrloop:
	Ld R0, X+
	Ld R1, X+
#if defined(_M48DEF_INC_)||defined(_M48PDEF_INC_)||defined(_M88DEF_INC_)||defined(_M88PDEF_INC_)||defined(_M168DEF_INC_)||defined(_M168PDEF_INC_)
	Ldi R16, (1<<SELFPRGEN)
#else
	Ldi R16, (1<<SPMEN)
#endif
	Rcall Do_spm
	Adiw Zh:Zl, 2
	Sbiw R24:R25, 1 ;use subi for PAGESIZEB<=256
	Brne Wrloop
; execute Page Write
	Subi Zl, Low(PAGESIZE*2) ;restore pointer
	Sbci Zh, High(PAGESIZE*2) ;not required for PAGESIZEB<=256
#if defined(_M48DEF_INC_)||defined(_M48PDEF_INC_)||defined(_M88DEF_INC_)||defined(_M88PDEF_INC_)||defined(_M168DEF_INC_)||defined(_M168PDEF_INC_)
	Ldi R16, (1<<PGWRT) | (1<<SELFPRGEN)
#else
	Ldi R16, (1<<PGWRT) | (1<<SPMEN)
#endif
	Rcall Do_spm
; re-enable the RWW section
#if defined(_M48DEF_INC_)||defined(_M48PDEF_INC_)||defined(_M88DEF_INC_)||defined(_M88PDEF_INC_)||defined(_M168DEF_INC_)||defined(_M168PDEF_INC_)
	Ldi R16, (1<<RWWSRE) | (1<<SELFPRGEN)
#else
	Ldi R16, (1<<RWWSRE) | (1<<SPMEN)
#endif
	Rcall Do_spm
; read back and check, optional
	Ldi R24, Low(PAGESIZE*2) ;init loop variable
	Ldi R25, High(PAGESIZE*2) ;not required for PAGESIZEB<=256
	Subi Xl, Low(PAGESIZE*2) ;restore pointer
	Sbci Xh, High(PAGESIZE*2)
Rdloop:
#if defined(_M128DEF_INC_) || defined(_M128ADEF_INC_) || defined(_M1280DEF_INC_) || defined(_M1281DEF_INC_) || defined(_M1284PDEF_INC_) || defined(_M2560DEF_INC_) || defined(_M2561DEF_INC_)
	Elpm R0, Z+
#else
	Lpm R0, Z+
#endif
	Ld R1, X+
	Cpse R0, R1
	Rjmp ErrorWritepage
	Sbiw R24:R25, 1 ;use subi for PAGESIZEB<=256
	Brne Rdloop
; return to RWW section
; verify that RWW section is safe to read
Return:
#if defined(_M48DEF_INC_)||defined(_M48PDEF_INC_)||defined(_M88DEF_INC_)||defined(_M88PDEF_INC_)||defined(_M168DEF_INC_)||defined(_M168PDEF_INC_)||defined(_M328DEF_INC_)||defined(_M328PDEF_INC_)  || defined(_M64DEF_INC_) || defined(_M64ADEF_INC_) || defined(_M64C1DEF_INC_) || defined(_M64M1DEF_INC_) || defined(_M640DEF_INC_) || defined(_M128DEF_INC_) || defined(_M128ADEF_INC_) || defined(_M1280DEF_INC_) || defined(_M1281DEF_INC_) || defined(_M1284PDEF_INC_) || defined(_M2560DEF_INC_) || defined(_M2561DEF_INC_)
	_ReadPort R17, SPMCSR
#else
	_ReadPort R17, SPMCR
#endif
	Sbrs R17, RWWSB ; If RWWSB is set, the RWW section is not ready yet
	Ret
; re-enable the RWW section
#if defined(_M48DEF_INC_)||defined(_M48PDEF_INC_)||defined(_M88DEF_INC_)||defined(_M88PDEF_INC_)||defined(_M168DEF_INC_)||defined(_M168PDEF_INC_)
	Ldi R16, (1<<RWWSRE) | (1<<SELFPRGEN)
#else
	Ldi R16, (1<<RWWSRE) | (1<<SPMEN)
#endif
	Rcall Do_spm
	Rjmp Return
Do_spm:
; check for previous SPM complete
Wait_spm:
	Wdr
#if defined(_M48DEF_INC_)||defined(_M48PDEF_INC_)||defined(_M88DEF_INC_)||defined(_M88PDEF_INC_)||defined(_M168DEF_INC_)||defined(_M168PDEF_INC_) ||defined(_M328DEF_INC_)||defined(_M328PDEF_INC_) || (_M64DEF_INC_) || defined(_M64ADEF_INC_) || defined(_M64C1DEF_INC_) || defined(_M64M1DEF_INC_) || defined(_M640DEF_INC_) || defined(_M128DEF_INC_) || defined(_M128ADEF_INC_) || defined(_M1280DEF_INC_) || defined(_M1281DEF_INC_) || defined(_M1284PDEF_INC_) || defined(_M2560DEF_INC_) || defined(_M2561DEF_INC_)
	_ReadPort R17, SPMCSR
#else
	_ReadPort R17, SPMCR
#endif
#if defined(_M48DEF_INC_)||defined(_M48PDEF_INC_)||defined(_M88DEF_INC_)||defined(_M88PDEF_INC_)||defined(_M168DEF_INC_)||defined(_M168PDEF_INC_)
	Sbrc R17, SELFPRGEN
#else
	Sbrc R17, SPMEN
#endif
	Rjmp Wait_spm
; input: spmcrval determines SPM action
; disable interrupts if enabled, store status
	In R18, SREG
	Cli
; check that no EEPROM write access is present
Wait_ee:
	Wdr
#if defined(_M88DEF_INC_)||defined(_M88PDEF_INC_)||defined(_M168DEF_INC_)||defined(_M168PDEF_INC_)||defined(_M640DEF_INC_) || defined(_M1280DEF_INC_) || defined(_M1281DEF_INC_) || defined(_M1284PDEF_INC_) || defined(_M2560DEF_INC_) || defined(_M2561DEF_INC_)
	Sbic EECR,EEPE 
#else
	Sbic EECR, EEWE
#endif
	Rjmp Wait_ee
; SPM timed sequence
#if defined(_M48DEF_INC_)||defined(_M48PDEF_INC_)||defined(_M88DEF_INC_)||defined(_M88PDEF_INC_)||defined(_M168DEF_INC_)||defined(_M168PDEF_INC_)||defined(_M328DEF_INC_)||defined(_M328PDEF_INC_) || defined(_M64DEF_INC_) || defined(_M64ADEF_INC_) || defined(_M64C1DEF_INC_) || defined(_M64M1DEF_INC_) || defined(_M640DEF_INC_) || defined(_M128DEF_INC_) || defined(_M128ADEF_INC_) || defined(_M1280DEF_INC_) || defined(_M1281DEF_INC_) || defined(_M1284PDEF_INC_) || defined(_M2560DEF_INC_) || defined(_M2561DEF_INC_)
	_WritePort SPMCSR, R16
#else
	_WritePort SPMCR, R16
#endif
	Spm
; restore SREG (to enable interrupts if originally enabled)
	Out SREG, R18
	Ret
ErrorWritepage:
	Clt
	Ret
.Include "IO_Internal_EEProm.asm"
;***************************************************************************
;***************************************************************************
;Constants
EnterBootLoaderStrCommand:
.db ((EndEnterBootLoaderStrCommand*2)-(EnterBootLoaderStrCommand*2))-2,"BootInit",255
EndEnterBootLoaderStrCommand:
;---------------------------------------------------------------------------
//ResponseToEnterInBootLoader:
//.dw ((EndResponseToEnterInBootLoader*2)-(ResponseToEnterInBootLoader*2))-3
//.db "***Morgoth HexBootLoader V1.0 Started***",13,255
//.db "BootOk",13,255
//EndResponseToEnterInBootLoader:
//;---------------------------------------------------------------------------
//ResponseToAbortBootLoader:
//.dw ((EndResponseToAbortBootLoader*2)-(ResponseToAbortBootLoader*2))-2
//.db"Starting user program ...",13
//EndResponseToAbortBootLoader:
;---------------------------------------------------------------------------
EnteringFlashModeStrCommend:
.db ((EndEnteringFlashModeStrCommend*2)-(EnteringFlashModeStrCommend*2))-2,"FlashW",255
EndEnteringFlashModeStrCommend:
;---------------------------------------------------------------------------
EnteringEEPromModeStrCommend:
.db ((EndEnteringEEPromModeStrCommend*2)-(EnteringEEPromModeStrCommend*2))-1,"EEPromW"
EndEnteringEEPromModeStrCommend:
;---------------------------------------------------------------------------
EnteringExitStrCommend:
.db ((EndEnteringExitStrCommend*2)-(EnteringExitStrCommend*2))-2,"Exit",255
EndEnteringExitStrCommend:
;---------------------------------------------------------------------------
;***************************************************************************
;***************************************************************************
