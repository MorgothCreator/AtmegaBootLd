;***************************************************************************
;* Internal EEProm driver
;*
;* File Name            :"IO_Internal_EEProm.asm"
;* Title                :Internal EEProm driver
;* Date                 :02.11.2009
;* Version              :1.0
;* Target MCU           :All ATmega Mictocontroller
;* AUTHOR		:Gheorghiu Iulian
;* 			 Romania
;* 			 morgoth2600@gmail.com
;* 			 http://sites.google.com/site/asmatmegaprograming/
;* 			 http://avrdevboardshop.hostzi.com/
;*
;* DESCRIPTION:
;*  This is a universal driver for internal EEProm memory
;*
;***************************************************************************
#ifndef __IntEEProm__
#define __IntEEProm__
#ifndef _DocMessages_IO_Internal_EEProm_Macro_
#define _DocMessages_IO_Internal_EEProm_Macro_
#ifndef __DocMessages_IO_Internal_EEProm_Macro__
#message "************To see libraries documentation for IO_Internal_EEProm_Macro, type: #define __DocMessages_IO_Internal_EEProm_Macro__"
#endif
#endif
;----------------------------
#ifdef __DocMessages_IO_Internal_EEProm_Macro__
#message ">>IO_Internal_EEProm Imported"
#message ">>>>>>>>For use ( _RDEEPROM: ) Routine Type ( #define __RDEEPROM__ ) ( Xl:Xh = Address to read, R16 = Read byte )"
#message ">>>>>>>>For use ( _RWEEPROM: ) Routine Type ( #define __RWEEPROM__ ) ( Xl:Xh = Address to write, R16 = Byte to write )"
#endif
;%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
;%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
;%%%%%%%%%                        Internal EEProm                            %%%%%%%%%
;%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
;%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
.Include "IO_Port.inc"
;****************************************************************************************************************
;.Def Data  = R16
;.Def AdrH  = Xh
;.Def AdrL  = Xl
#if defined(_M48DEF_INC_)||defined(_M48PDEF_INC_)||defined(_M88DEF_INC_)||defined(_M88PDEF_INC_)||defined(_M168DEF_INC_)||defined(_M168PDEF_INC_)||defined _M1281DEF_INC_ || defined _M2561DEF_INC_ || defined _M640DEF_INC_ || defined _M1280DEF_INC_ || defined _M2560DEF_INC_
#ifdef __RDEEPROM__
_RDEEPROM:
	_JmpPortBitSet EECR,EEPE,_RDEEPROM
#if defined(_M48DEF_INC_)||defined(_M48ADEF_INC_)||defined(_M48PDEF_INC_)||defined(_M48PADEF_INC_)
#else
	_WritePort EEARH, Xh
#endif
	_WritePort EEARL,Xl
	_SetPortBit EECR,EERE
	_ReadPort R16,EEDR
	Ret
#endif
;--------------------------------------------------------------
#ifdef __RWEEPROM__
_RWEEPROM:
	Wdr
	_JmpPortBitSet EECR,EEPE ,_RWEEPROM
#if defined(_M48DEF_INC_)||defined(_M48ADEF_INC_)||defined(_M48PDEF_INC_)||defined(_M48PADEF_INC_)
#else
	_WritePort EEARH, Xh
#endif
	_WritePort EEARL,Xl
	_WritePort EEDR,R16
	_SetPortBit EECR,EEMPE
	_SetPortBit EECR,EEPE
	Ret
#endif
#else
;****************************************************************************************************************
#ifdef __RDEEPROM__
_RDEEPROM:
	_JmpPortBitSet EECR,EEWE,_RDEEPROM
	_WritePort EEARH, Xh
	_WritePort EEARL, Xl
	_SetPortBit EECR,EERE
	_ReadPort R16,EEDR
	Ret
#endif
;--------------------------------------------------------------
#ifdef __RWEEPROM__
_RWEEPROM:
	Wdr
	_JmpPortBitSet EECR,EEWE,_RWEEPROM
	_WritePort EEARH, Xh
	_WritePort EEARL, Xl
	_WritePort EEDR,R16
	_SetPortBit EECR,EEMWE
	_SetPortBit EECR,EEWE
	Ret
#endif
#endif
;****************************************************************************************************************
#endif
