# PS/2 Keyboard MIDI Controller
## Scott Baker, [http://www.smbaker.com/](http://www.smbaker.com/)

This program implements a receiver for a PS/2 keyboard, decodes the scan keys,
and sends them out as a midi notes at 31,250 baud. The purpose is to implement
a simple way to play notes on a midi module from a PS/2 keyboard.

I am not a musician, I make no claim to have picked the notes in a 
particularly sensible manner. I started each major line of the keyboard with
middle C, and assigned a different instrument to each line. The modifier keys
and other specials (shift, control, arrows, etc) are assigned to percussion 
instruments. 

This is based extensively on other peoples' work, see the attribution section below.
I found a PS/2 keyboard library and a soft-uart library and hooked them together.

### Pin Assignments:

    PB0 - PS/2 data
    PB1 - PS/2 CLK
    PB2 - Tandy CLK
    PB3 - Tandy Data
    PB4 - Tandy Busy

### Attribution:

* ATTiny85 UART Library 

      The Garage Lab
      https://github.com/thegaragelab/tinytemplate
      Creative Commons Attribution-ShareAlike 4.0 International License (http:// creativecommons.org/licenses/by-sa/4.0/)

* PS/2 Keyboard Library

      Interrupts: Interfacing a Microcontroller with a PS/2 Keyboard
      http://www.nerdkits.com/videos/interrupts_and_ps2_keyboard/

### License
Creative Commons Attribution-ShareAlike 4.0 International License (http://creativecommons.org/licenses/by-sa/4.0/)
