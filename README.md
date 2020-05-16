# PS/2 Keyboard to Tandy 1000A Computer Converter
## Scott Baker, [http://www.smbaker.com/](http://www.smbaker.com/)

I found a Tandy 1000A on eBay without a keyboard. I grew impatient and wanted to use it.
So I build an adapter to use a PS2 keyboard on a Tandy 1000A.

### Pin Assignments:

    PB0 - PS/2 data
    PB1 - PS/2 CLK
    PB2 - Tandy CLK
    PB3 - Tandy Data
    PB4 - Tandy Busy

### Custom Mappings

Some of the Tandy Keys are different from the PS2 keys...

* PS2 Break - Tandy Break
* PS2 Ctrl-Break - Tandy Break
* PS2 Scroll Lock - Tandy Hold
* PS2 Backslash - Tandy unshifted KP7 or KP4
* PS2 Backquote - Tandy unshifted KP8 or KP2

### Attribution:

* PS/2 Keyboard Library

      Interrupts: Interfacing a Microcontroller with a PS/2 Keyboard
      http://www.nerdkits.com/videos/interrupts_and_ps2_keyboard/

### License
Creative Commons Attribution-ShareAlike 4.0 International License (http://creativecommons.org/licenses/by-sa/4.0/)
