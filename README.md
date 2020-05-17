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

### Bill of materials:

* X2 ... MINIDIN6_PE ... 6-pin minidin PS/2 jack ... digikey CP-2460-ND (the ones in the prototype came from eBay -- cheaper in quantity)
* X1 ... DIN-8 ... 8 pin din connector ... digikey CP-7080-ND
* U1 ... ATINY85 ... microcontroller ... digikey ATTINY85-20PU-ND
* JP1, JP2 ... 0.100 headers ... any old 0.100 header
* R2, R3 ... 4.7 K resistor
* R7 ... 150 ohm resistor
* C5, C6 ... 0.1uF monolithic ceramic capacitor
* C7, C7_1 ... 0.01uF monolithic ceramic capacitor, optional
* C4 ... 10uF electrolytyic cap, go for 10V or more to be safe
* F1 or F2 ... 1 amp pico-fuse, or a PTC fuse, or just wire it across if you're feeling lucky
* L1, L2 ... 47 microhenry inductor, do not buy, just wire it across

If you want to build yourself an 8-pin DIN cable for connecting the adapter to your Tandy 1000, then also pick up a pair of CP-1080-ND from digikey. You can also buy 8-pin DIN cables premade on ebay and amazon, and this would save you some wiring effort. I made my own. Also note that the 8th (center) pin is not used, so a 7 pin PIN cable may work just as well.

Note on terminology - The "big" round Tandy connectors are DIN connectors. The "small" round PS2 connectors are mini-DIN connectors. So make sure to get yourself the right connectors.

### Programming

I programmed the ATTINY85 using a minipro programmer that I bought on ebay. You'll find two files, one of the files holds the fuses. The other file holds the code. The github repo includes a screenshot of the fuse settings.

### Eagle and Gerber files

These are checked in. Note that the 0.3 design has not been fabricated. It's functionally identical to the 0.1 design that I built in the youtube video, but with obsolete (and occasionally misleading) components removed. I recommend you build the 0.3 design, not the 0.1 design.

### Attribution:

* PS/2 Keyboard Library

      Interrupts: Interfacing a Microcontroller with a PS/2 Keyboard
      http://www.nerdkits.com/videos/interrupts_and_ps2_keyboard/

### License
Creative Commons Attribution-ShareAlike 4.0 International License (http://creativecommons.org/licenses/by-sa/4.0/)
