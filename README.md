# AtmegaBootLd

# The project has been moved here https://git.morgothdisk.com

A very tiny fast bootloader in hex data transfer mode.

This is the first public release.

Ia a very fast botloader that receive intel hex data format, 
it is developed in ASM language to obtain a very small bootloader,
with a maximum size of 512Words/1024Bytes.


This bootloader receive intel hex lines from a intel hex file with status response of every received line, 
this bootloader can work with a serial adapter or using a bluetooth or Xbee transceiver.

Aditional this bootloader can receive several commands:

1) "BootInit" this is the expected word to enter in bootloader, the bootloader wait for this word for about two seconds until hi jump to aplication.

2) "FlashW" this is the word that indicate to bootloader that the next received data will be put in FLASH app memory.

3) "EEPromW" this is the word that indicate to bootloader that the next received data will be put in EEPROM memory.

4) "Exit" this is the word that indicate to bootloader that all data has been transmited and to jump to loaded application.

The boot loader report on every line the status chars:

1) 'a' line definition error.

2) 'b' second hex char not found.

3) 'c' checksum error.

4) 'd' line mismach.

5) 'e' no memory selected.

6) 'k' received line is OK and has been writed on buffer.


This bootloader work with flash memory in buffered page mode, 
all received data will be writed into a buffer until is received a request to write to another page, 
when is received a write to another page the bootloader will write the buffered data into flash page 
and will load to buffer the requested write page, in this mode the bootloader will not write directly to flash 
but append data on flash.


The same principle is with EEPROM but without buffering because EEPROM support byte write mode.
