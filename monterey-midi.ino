#include <PS2Keyboard.h>

#define DEFAULT_OCTAVE 5    // set the default octave when switching on your Arduino. 5 = note C5, 4 = note C4, etc.

#define NOTE_ON 0x90
#define NOTE_OFF 0x80
#define NOTE_START 53

PS2Keyboard keyboard;
const int DataPin = 3;
const int IRQpin =  2;

const char keyNoteMap[37] = {
    'a', 'b', 'c', 'd', 'e', 
    'f', 'g', 'h', 'i', 'j', 
    'k', 'l', 'm', 'n', 'o', 
    'p', 'q', 'r', 's', 't', 
    'u', 'v', 'w', 'x',  'y',  
    'z', '8',  '9', '-', '=',  
    '\\',  '[', ']', ';',  '\'', 
    ',', '.'
}; 

boolean midiMode = true;    // if midiMode = false, the Arduino will send on and off messages via the serial monitor.
                            // if midiMode = true, the Arduino will act as a native MIDI device.

byte octaveValue = DEFAULT_OCTAVE;

char noteQueue[2];

enum NoteStatus { NONE, NOTE_PRESSED, VELOCITY_PRESSED };
int noteStatus = NoteStatus::NONE;

// Plays a MIDI note. Doesn't check to see that cmd is greater than 127, or that data values are less than 127:
void noteCmd(int cmd, int pitch, int velocity) {
    Serial.write(cmd);
    Serial.write(pitch);
    Serial.write(velocity);
}

int calcMIDINote(char notePressed) {
    // Search array position for the note pressed
    const char *ptr = strchr(keyNoteMap, notePressed);
    int index = ptr - keyNoteMap;
    return NOTE_START + index; 
}

// Default velocity of all MIDI notes, the range is from 0 to 127 (fastest)
// Monterey produces a range from 7 to 1 (fastest)
int calcMIDINoteVelocity(char velocityPressed) {
    String velocity(velocityPressed);
    return (-7.833 * velocity.toInt()) + 134.83;
}

//________________________________________________________________________________________________________________________________________
void setup() {
    keyboard.begin(DataPin, IRQpin);
    
    if (midiMode) {
        Serial.begin(31250); // this is the standard communication baudrate for MIDI devices, do not change this!
    }
    else {
        Serial.begin(9600);
    }
}

//________________________________________________________________________________________________________________________________________
void loop() {
    if (keyboard.available()) {
        char keyValue = keyboard.read();

        switch (noteStatus) {
            case NoteStatus::NONE:
                noteQueue[0] = keyValue;
                noteStatus = NoteStatus::NOTE_PRESSED;
                break;

            case NoteStatus::NOTE_PRESSED:
                noteQueue[1] = keyValue;
                noteStatus = NoteStatus::VELOCITY_PRESSED;

                int MIDINote = calcMIDINote(noteQueue[0]);
                int MIDIVelocity = 100;//calcMIDINoteVelocity(noteQueue[1]);

                // Note Off
                if (noteQueue[1] == '0') {
                    noteCmd(NOTE_OFF, MIDINote, MIDIVelocity);

                    if (!midiMode)
                        Serial.println("Note OFF. Key: " + String(noteQueue[0]) + " Speed: " + String(noteQueue[1]));
                }

                // Note On
                else {
                    noteCmd(NOTE_ON, MIDINote, MIDIVelocity);

                    if (!midiMode)
                        Serial.println("Note ON. Key: " + String(noteQueue[0]) + " MIDI Note: " + String(MIDINote) + " Speed: " + String(noteQueue[1]));
                }

                noteStatus = NoteStatus::NONE;
                break;

            
        }
    }
}

void demo() {
    for (int note = 60; note < 72; note++) {
        //Note on channel 1 (0x90), some note value (note), middle velocity (0x45):
        noteCmd(NOTE_ON, note, 100);

        delay(100);
        //Note on channel 1 (0x90), some note value (note), silent velocity (0x00):
        noteCmd(NOTE_OFF, note, 0x00);
        delay(100);
    }
}