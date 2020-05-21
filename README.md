zx81-ps2-keyboard
=================

This quick project grew out of a suggestion on the Spectrum Next Facebook group. This adapts a ZX81 keyboard to connect to a PS/2 keyboard interface, as on the back of the Spectrum Next, so that you can experience the true pain of a classic ZX81 keyboard in ZX81 emulaton mode.

This code was targeted at a 5v Sparkfun Arduino Pro Micro clone, but with a small amount of juggling will easily work on any other Arduino.

The module is wired as follows:

|Right Ribbon Cable||Left Ribbon Cable|
|-|-|-|   
| A3  A2  A1  A0  15 |  | 14  16  10  5  6  7  8  9 |

on the PS/2 side the script is using ps2dev library and the ps2 plug is wired to

|Clock|Data|
|-|-|
|3|2|
 
Also, 5v and GND are taken from the PS2 port to power the device (don't use a 3v arduino for this project)
