IntelHexParser
==============

C++ Intel Hex Parser

This was forked from original project that only supported 0x0 and 0x1 record types.
The IntelHexParser library automatically handles the parsing of files in the Intel Hex File Format.  This project was originally started as part of a AVR I2C Bootloader and then moved to a seperate library.  The library currently is only compiled to a dynamic library (*.so).  More information on how to use the library can be found in INSTALL.

We will add support for 0x03 and other additions like computing 2-s complement crc for
reformatting compiled hex files that we need to generate a combined hex for our anykey-bootloader project
https://github.com/w-A-L-L-e/anykey-bootloader

Also we will statically link and add some commandline params as we need a commandline conversion tool, not a library to incorporate somewhere...
Basically we want to load in ihex files and change the bytes per line on the fly to combine different formats etc.
https://en.wikipedia.org/wiki/Intel_HEX

By no means coded cleanly. Just some quick hacks during lunchtime in order to combine some hex files...


