# Monterey-MK-9500-MIDI
🎹 -> 🎼 Arduino program to convert inputs from the Monterey-MK-9500 piano to a MIDI standard output

## Materials
- Monterey-MK-9500 Keyboard
- Arduino Uno[^1] or Mega
- 5-din female jack/cable

[^1]: Note on Arduino Uno clones: The original Atmega8U2 or 16U2 chips might not be present and instead use a cheap knockoff which has insufficient capacity to store this firmware.

## Instructions

### Using your Arduino into a MIDI device
How to compile the firmware
https://github.com/TheKikGen/USBMidiKliK
You must have the WINAVR or gcc-avr installed on your computer.
sudo apt-get install gcc-avr binutils-avr avr-libc gdb-avr avrdude

Clone the USBMidiKlik source code and its submodules lufa and midiXparser :
git clone --recurse-submodules https://github.com/TheKikGen/USBMidiKliK

To build for uno, use 'make uno'.
To get help, use 'make mdkhelp'.

## TODO
- Include custom firmware flashing instructions
- Implement key velocity 
- Implement octave changes
