# Monterey-MK-9500-MIDI
🎹 -> 🎼 Arduino program to convert inputs from the Monterey-MK-9500 piano to a MIDI standard output

## Materials
- Monterey-MK-9500 Keyboard
- An Arduino
    - Uno [^1] or Mega - Requires flashing [MIDI firmware](#the-midi-firmware)
    - Arduinos with an ATMEGA32U4 microcontroller (Pro Micro, Micro, Leonardo) apparently work out-of-the-box without custom firmware. **I did not test this.**
- 5-din female jack/cable
- (Optional) Breadboard/Perf board/PCB
  - This is optional but it makes it easier to connect everything between your arduino as seen in [Circuit and Connections](#circuit-and-connections)

[^1]: Note on Arduino Uno clones: The original Atmega8U2 or 16U2 chips might not be present and instead use a cheap knockoff which has insufficient capacity to store this firmware.

## Using your Arduino as a MIDI device
This process will allow you to transform your Arduino into a fully MIDI-compliant device. 

This is process is a toggle. You will retain normal Arduino features through an easy shunt to the ICSP pins.

### The MIDI firmware (USBMidiKliK)
This process requires you to flash the [USBMidiKliK](https://github.com/TheKikGen/USBMidiKliK) firmware into your Arduino - "A robust USB MIDI Arduino firmware, with a dual bootloader, based on the last version of the LUFA library"

#### Using my pre-compiled firmware
Out of convenience I provide along with this repository, pre-compiled firmware files.
https://github.com/alxcost/Monterey-MK-9500-MIDI/releases

If you find any issues, please try [compiling your own](#compiling-usbmidiklik).

#### Compiling USBMidiKliK
This section is almost a word-for-word instructions from the [official documention](https://github.com/TheKikGen/USBMidiKliK/tree/409fb99691630ee7a0cee8a2307253d8f55b18cd?tab=readme-ov-file#how-to-compile-the-firmware).
However I'm still documenting what has worked for me.

1. Clone the USBMidiKlik repository and its submodules, including lufa and midiXparser:
    1. `git clone --recurse-submodules git clone --recurse-submodules https://github.com/TheKikGen/USBMidiKliK`
2. Using gcc-avr (worked on Windows Subsystem for Linux)
    1. `sudo apt-get install gcc-avr binutils-avr avr-libc gdb-avr avrdude`
3. Build for Arduino:
    1. Arduino Uno: `make uno`
    2. Arduino Mega: `make mega`

### Flashing the Atmega16U2
Usually, there are two microcontrollers on the Arduino board: ATMEGA328P (328P) and ATMEGA16U2 (16U2). You need to update firmware of 16U2 to become a midi interface.

Install Atmel FLIP Software You will need Atmel FLIP software to update the firmware inside 16U2. https://www.microchip.com/en-us/development-tool/FLIP Install it.

Connect your Arduino board to USB. Touch briefly pins 5-6 of the ISCP1 header to reset the 16U2. image

## Circuit and Connections




## TODO
- Include custom firmware flashing instructions
- Implement key velocity 
- Implement octave changes
