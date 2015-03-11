# AtmegaBootLd
A very tiny fast bootloader in hex data transfer mode.

This is the first public release.
Ia a very fast botloader that receive intel hex data format, 
it is developed in ASM language to obtain a very tiny bootloader,
with a maximum size of 512Words or 1024Bytes.


This bootloader receive intel hex lines from a intel hex file with status response of every received line.

Aditional this bootloader can receive several commands:

1) "BootInit" this is the expected word to enter in bootloader, the bootloader wait for this word for about two seconds until hi jump to aplication.

2) "FlashW" this is the wort that indicate to bootloader that the next received data will be put in flash app memory.

3) "EEPromW" this is the word that indicate to bootloader that the next received data will be put in eeprom memory.

4) "Exit" this is the word that indicate to bootloader that all data has been transmited and to jump to loaded application.

The boot loader report on every line the status chars:

1) 'a' line definition error.

2) 'b' second hex char not found.

3) 'c' checksum error.

4) 'd' line mismach.

5) 'e' no memory selected.

6) 'k' received line is OK and has been writed on buffer.


This bootloader work on flash memory with pages, 
all received data will be writed into a buffer until are received a request to write in another page, 
when is received a write to another page the bootloader will write the buffer data into flash page 
and will load to buffer the request write page, in this mode the bootloader not write directly to flash 

but append data on flash.


The same principle is with eeprom but without buffering.
