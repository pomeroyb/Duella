=============================
Duella: Uncia DLP 3D Printer Firmware
=============================

In <a href="http://en.wikipedia.org/wiki/Ancient_Roman_units_of_measurement#Weight">ancient Roman units of weight, a Duella is equal to 1/3 of an Uncia.</a>

This is my fork of the Uncia DLP 3D Printer firmware that was initially shipped with my Uncia 3D Printer.

The original Uncia firmware was clearly a huge rip off of the Sedgwick firmware (Even using the strange "pseudo-gcode"), so please check out <a href="http://sedgwick3d.com/">his site too</a>!

This firmware improves upon the original, allowing Uncia users to update their printers without going through the hassle of replacing electronics.
(This doesn't exclude adding electronics like an extra stepper driver or a servo -- but is more commenting on the practice of replacing the Teensy 2.0 with RAMPs 1.4)

For Use With Creation Workshop Software:
========================================
CWS is an excellent slicer and printer interface that already works with the Uncia, thanks to a custom driver from Steve Hernandez.
This firmware will play nicely with his eUNCIA driver, but limits the user to the stock Uncia. If a user wants to upgrade their printer (in any way), they will need my fork of Creation Workshop.
(This has to do with my eUNCIA driver pinging the firmware, and using that to discover what upgrades the user has.

Check out Steve's <a href="https://github.com/Pacmanfan/UVDLPSlicerController">Git repo</a>, and his <a href="http://www.buildyourownsla.com/forum/">forums</a> too!

I hope to eventually improve upon this firmware, 
Currently Supported Hardware/Electronics:
===============================
*   Stock Uncia 3D Printer
*	Teensy 2.0
*	A498 Stepper Driver

Future Support Planned For:
===========================
*	Endstop(s)
*	Servo Aperture
*	Wiper mechanism (Stepper Powered)

