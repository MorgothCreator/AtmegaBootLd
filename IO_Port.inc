;***************************************************************************
;* I/O Ports Driver
;*
;* File Name            :"IO_Port.inc"
;* Location             :"Drivers/IO_Port.inc"
;* Title                :Port Macro Driver and utility ( Bit & Port manipulation )
;* Date                 :02.09.2009
;* Version              :1.0
;* Target MCU           :All ATmega Mictocontroller
;* AUTHOR		:Gheorghiu Iulian
;* 			 Romania
;* 			 morgoth2600@gmail.com
;* 			 http://digitalelectronicsandprograming.blogspot.com/
;* 			 http://avrdevboardshop.hostzi.com/
;*
;* DESCRIPTION:
;*  This is a driver ( Macro format ) to working with I/O Ports and I/O Port Bit manipilation
;*
;***************************************************************************
#ifndef _DocMessages_Driver_Port_Macro_
#define _DocMessages_Driver_Port_Macro_
#ifndef __DocMessages_Driver_Port_Macro__
#message "************To see libraries documentation for Driver_Port_Macro type: #define __DocMessages_Driver_Port_Macro__"
#endif
#endif
;----------------------------
#ifndef __Driver_Port_Macro__
#define __Driver_Port_Macro__
#ifdef __DocMessages_Driver_Port_Macro__
#message ">>Driver_Port_Macro Imported"
#message "--->>Disponible macros in 'Lib_Convert' library:"
#message "------>>_SetPortBit ( _SetPortBit PORTA,Bit )"
#message "------>>_ClrPortBit ( _ClrPortBit PORTA,Bit )"
#message "------>>_Set2PortBit ( _Set2PortBit PORTA,Bit,Bit )"
#message "------>>_Clr2PortBit ( _Clr2PortBit PORTA,Bit,Bit )"
#message "------>>_Set3PortBit ( _Set3PortBit PORTA,Bit,Bit,Bit )"
#message "------>>_Clr3PortBit ( _Clr3PortBit PORTA,Bit,Bit,Bit )"
#message "------>>_Set4PortBit ( _Set4PortBit PORTA,Bit,Bit,Bit,Bit )"
#message "------>>_Clr4PortBit ( _Clr4PortBit PORTA,Bit,Bit,Bit,Bit )"
#message "------>>_Set5PortBit ( _Set5PortBit PORTA,Bit,Bit,Bit,Bit,Bit )"
#message "------>>_Clr5PortBit ( _Clr5PortBit PORTA,Bit,Bit,Bit,Bit,Bit )"
#message "------>>_Set6PortBit ( _Set6PortBit PORTA,Bit,Bit,Bit,Bit,Bit,Bit )"
#message "------>>_Clr6PortBit ( _Clr6PortBit PORTA,Bit,Bit,Bit,Bit,Bit,Bit )"
#message "------>>_Set7PortBit ( _Set7PortBit PORTA,Bit,Bit,Bit,Bit,Bit,Bit,Bit )"
#message "------>>_Clr7PortBit ( _Clr7PortBit PORTA,Bit,Bit,Bit,Bit,Bit,Bit,Bit )"
#message "------>>_JmpPortBitSet ( _JmpPortBitSet PORTA,Bit,LabelToJump )"
#message "------>>_JmpPortBitClr ( _JmpPortBitClr PORTA,Bit,LabelToJump )"
#message "------>>_ReadPortBitAppendInReg ( _ReadPortBitAppendInReg Reg,RegBit,Port,PortBit )"
#message "------>>_ReadRegBitAppendInPort ( _ReadRegBitAppendInPort Port,PortBit,Reg,RegBit )"
#message "------>>_WritePortConst ( _WritePortConst PORTA,Byte )"
#message "------>>_WritePort ( _WritePort PORTA,Reg )"
#message "------>>_ReadPort ( _ReadPort Reg,PORTA )"
#endif
;***************************************************************************
.ifndef True
.Equ True 						= 1
.endif
;----------------------------------------
.ifndef False
.Equ False 						= 0
.endif
;----------------------------------------
.ifndef Sram
.Equ Sram 						= 2
.endif
;----------------------------------------
.ifndef Port
.Equ Port 						= 1
.endif
;----------------------------------------
.ifndef Null
.Equ Null 						= 0
.endif
;########################################################
;#               Port 1bit manipulation                 #
;########################################################
.Macro _SetPortBit
.if @0 > 0x3F
	Push R16
	Lds R16,@0
	Sbr R16,1<<@1
	Sts @0,R16
	Pop R16
.elif @0 > 0x1F
	Push R16
	In R16,@0
	Sbr R16,1<<@1
	Out @0,R16
	Pop R16
.else
	Sbi @0,@1
.endif
.EndM
;---------------------------------------------------------
.Macro _ClrPortBit
.if @0 > 0x3F
	Push R16
	Lds R16,@0
	Cbr R16,1<<@1
	Sts @0,R16
	Pop R16
.elif @0 > 0x1F
	Push R16
	In R16,@0
	Cbr R16,1<<@1
	Out @0,R16
	Pop R16
.else
	Cbi @0,@1
.endif
.EndM
;########################################################
;#               Port 2bit manipulation                 #
;########################################################
.Macro _Set2PortBit
.if @0 > 0x3F
	Push R16
	Lds R16,@0
	Sbr R16,(1<<@1)|(1<<@2)
	Sts @0,R16
	Pop R16
.elif @0 > 0x1F
	Push R16
	In R16,@0
	Sbr R16,(1<<@1)|(1<<@2)
	Out @0,R16
	Pop R16
.else
	Sbi @0,@1
	Sbi @0,@2
.endif
.EndM
;---------------------------------------------------------
.Macro _Clr2PortBit
.if @0 > 0x3F
	Push R16
	Lds R16,@0
	Cbr R16,(1<<@1)|(1<<@2)
	Sts @0,R16
	Pop R16
.elif @0 > 0x1F
	Push R16
	In R16,@0
	Cbr R16,(1<<@1)|(1<<@2)
	Out @0,R16
	Pop R16
.else
	Cbi @0,@1
	Cbi @0,@2
.endif
.EndM
;########################################################
;#               Port 3bit manipulation                 #
;########################################################
.Macro _Set3PortBit
.if @0 > 0x3F
	Push R16
	Lds R16,@0
	Sbr R16,(1<<@1)|(1<<@2)|(1<<@3)
	Sts @0,R16
	Pop R16
.elif @0 > 0x1F
	Push R16
	In R16,@0
	Sbr R16,(1<<@1)|(1<<@2)|(1<<@3)
	Out @0,R16
	Pop R16
.else
	Sbi @0,@1
	Sbi @0,@2
	Sbi @0,@3
.endif
.EndM
;---------------------------------------------------------
.Macro _Clr3PortBit
.if @0 > 0x3F
	Push R16
	Lds R16,@0
	Cbr R16,(1<<@1)|(1<<@2)|(1<<@3)
	Sts @0,R16
	Pop R16
.elif @0 > 0x1F
	Push R16
	In R16,@0
	Cbr R16,(1<<@1)|(1<<@2)|(1<<@3)
	Out @0,R16
	Pop R16
.else
	Cbi @0,@1
	Cbi @0,@2
	Cbi @0,@3
.endif
.EndM
;########################################################
;#               Port 4bit manipulation                 #
;########################################################
.Macro _Set4PortBit
.if @0 > 0x3F
	Push R16
	Lds R16,@0
	Sbr R16,(1<<@1)|(1<<@2)|(1<<@3)|(1<<@4)
	Sts @0,R16
	Pop R16
.elif @0 > 0x1F
	Push R16
	In R16,@0
	Sbr R16,(1<<@1)|(1<<@2)|(1<<@3)|(1<<@4)
	Out @0,R16
	Pop R16
.else
	Sbi @0,@1
	Sbi @0,@2
	Sbi @0,@3
	Sbi @0,@4
.endif
.EndM
;---------------------------------------------------------
.Macro _Clr4PortBit
.if @0 > 0x3F
	Push R16
	Lds R16,@0
	Cbr R16,(1<<@1)|(1<<@2)|(1<<@3)|(1<<@4)
	Sts @0,R16
	Pop R16
.elif @0 > 0x1F
	Push R16
	In R16,@0
	Cbr R16,(1<<@1)|(1<<@2)|(1<<@3)|(1<<@4)
	Out @0,R16
	Pop R16
.else
	Cbi @0,@1
	Cbi @0,@2
	Cbi @0,@3
	Cbi @0,@4
.endif
.EndM
;########################################################
;#               Port 5bit manipulation                 #
;########################################################
.Macro _Set5PortBit
.if @0 > 0x3F
	Push R16
	Lds R16,@0
	Sbr R16,(1<<@1)|(1<<@2)|(1<<@3)|(1<<@4)|(1<<@5)
	Sts @0,R16
	Pop R16
.elif @0 > 0x1F
	Push R16
	In R16,@0
	Sbr R16,(1<<@1)|(1<<@2)|(1<<@3)|(1<<@4)|(1<<@5)
	Out @0,R16
	Pop R16
.else
	Sbi @0,@1
	Sbi @0,@2
	Sbi @0,@3
	Sbi @0,@4
	Sbi @0,@5
.endif
.EndM
;---------------------------------------------------------
.Macro _Clr5PortBit
.if @0 > 0x3F
	Push R16
	Lds R16,@0
	Cbr R16,(1<<@1)|(1<<@2)|(1<<@3)|(1<<@4)|(1<<@5)
	Sts @0,R16
	Pop R16
.elif @0 > 0x1F
	Push R16
	In R16,@0
	Cbr R16,(1<<@1)|(1<<@2)|(1<<@3)|(1<<@4)|(1<<@5)
	Out @0,R16
	Pop R16
.else
	Cbi @0,@1
	Cbi @0,@2
	Cbi @0,@3
	Cbi @0,@4
	Cbi @0,@5
.endif
.EndM
;########################################################
;#               Port 6bit manipulation                 #
;########################################################
.Macro _Set6PortBit
.if @0 > 0x3F
	Push R16
	Lds R16,@0
	Sbr R16,(1<<@1)|(1<<@2)|(1<<@3)|(1<<@4)|(1<<@5)|(1<<@6)
	Sts @0,R16
	Pop R16
.elif @0 > 0x1F
	Push R16
	In R16,@0
	Sbr R16,(1<<@1)|(1<<@2)|(1<<@3)|(1<<@4)|(1<<@5)|(1<<@6)
	Out @0,R16
	Pop R16
.else
	Sbi @0,@1
	Sbi @0,@2
	Sbi @0,@3
	Sbi @0,@4
	Sbi @0,@5
	Sbi @0,@6
.endif
.EndM
;---------------------------------------------------------
.Macro _Clr6PortBit
.if @0 > 0x3F
	Push R16
	Lds R16,@0
	Cbr R16,(1<<@1)|(1<<@2)|(1<<@3)|(1<<@4)|(1<<@5)|(1<<@6)
	Sts @0,R16
	Pop R16
.elif @0 > 0x1F
	Push R16
	In R16,@0
	Cbr R16,(1<<@1)|(1<<@2)|(1<<@3)|(1<<@4)|(1<<@5)|(1<<@6)
	Out @0,R16
	Pop R16
.else
	Cbi @0,@1
	Cbi @0,@2
	Cbi @0,@3
	Cbi @0,@4
	Cbi @0,@5
	Cbi @0,@6
.endif
.EndM
;########################################################
;#               Port 7bit manipulation                 #
;########################################################
.Macro _Set7PortBit
.if @0 > 0x3F
	Push R16
	Lds R16,@0
	Sbr R16,(1<<@1)|(1<<@2)|(1<<@3)|(1<<@4)|(1<<@5)|(1<<@6)|(1<<@7)
	Sts @0,R16
	Pop R16
.else
	Push R16
	In R16,@0
	Sbr R16,(1<<@1)|(1<<@2)|(1<<@3)|(1<<@4)|(1<<@5)|(1<<@6)|(1<<@7)
	Out @0,R16
	Pop R16
.endif
.EndM
;---------------------------------------------------------
.Macro _Clr7PortBit
.if @0 > 0x3F
	Push R16
	Lds R16,@0
	Cbr R16,(1<<@1)|(1<<@2)|(1<<@3)|(1<<@4)|(1<<@5)|(1<<@6)|(1<<@7)
	Sts @0,R16
	Pop R16
.else
	Push R16
	In R16,@0
	Cbr R16,(1<<@1)|(1<<@2)|(1<<@3)|(1<<@4)|(1<<@5)|(1<<@6)|(1<<@7)
	Out @0,R16
	Pop R16
.endif
.EndM
;########################################################
;#               Port bit read and jump                 #
;########################################################
.Macro _JmpPortBitSet
.if @0 > 0x3F
	Push R16
	Lds R16,@0
	Sbrc R16,@1
	Rjmp GetBit1
	Pop R16
	Rjmp GetBit0
GetBit1:
	Pop R16
	Rjmp @2
GetBit0:
.elif @0 > 0x1F
	Push R16
	In R16,@0
	Sbrc R16,@1
	Rjmp GetBit1
	Pop R16
	Rjmp GetBit0
GetBit1:
	Pop R16
	Rjmp @2
GetBit0:
.else
	Sbic @0,@1
	Rjmp @2
.endif
.EndM
;********************************************************
.Macro _JmpPortBitClr
.if @0 > 0x3F
	Push R16
	Lds R16,@0
	Sbrs R16,@1
	Rjmp GetBit1
	Pop R16
	Rjmp GetBit0
GetBit1:
	Pop R16
	Rjmp @2
GetBit0:
.elif @0 > 0x1F
	Push R16
	In R16,@0
	Sbrs R16,@1
	Rjmp GetBit1
	Pop R16
	Rjmp GetBit0
GetBit1:
	Pop R16
	Rjmp @2
GetBit0:
.else
	Sbis @0,@1
	Rjmp @2
.endif
.EndM
;########################################################
;#                 Bit read & Append                    #
;########################################################
.Macro _ReadPortBitAppendInReg
	Push @0
.if @2 > 0x3F
	Lds @0,@2
.else
	In @0,@2
.endif
	Bst @0,@3
	Pop @0
	Bld @0,@2
.Endm
;********************************************************
.Macro _ReadRegBitAppendInPort
	Bst @2,@3
	Push @2
.if @0 > 0x3F
	Lds @2,@0
.else
	In @2,@0
.endif
	Bld @2,@1
.if @0 > 0x3F
	Sts @0,@1
.else
	Out @0,@1
.endif
	Pop @2
.Endm
;########################################################
;#                  Port 8bit in/out                    #
;########################################################
.Macro _WritePortConst
	Push R16
	Ldi R16,@1
.if @0 > 0x3F
	Sts @0,R16
.else
	Out @0,R16
.endif
	Pop R16
.EndM
;---------------------------------------------------------
.Macro _WritePort
.if @0 > 0x3F
	Sts @0,@1
.else
	Out @0,@1
.endif
.EndM
;---------------------------------------------------------
.Macro _ReadPort
.if @1 > 0x3F
	Lds @0,@1
.else
	In @0,@1
.endif
.EndM
;********************************************************
#endif


