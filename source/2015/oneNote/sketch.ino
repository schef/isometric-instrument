
#define MIDI_CHANNEL 1
// For this sketch, we only can play one note
#define MIDI_NOTE 60 // Middle C (C4)
// The threshold level for sending a note on event. If the
// sensor is producing a level above this, we are in note on
// state, otherwise note off
#define NOTE_ON_THRESHOLD 100

// We keep track of whether a note is sounding or not,
// so we know whether to send a note on or off event.
boolean noteSounding = false;
// The value read from the sensor
int sensorValue;

void setup() {
  // Nothing to initialize for this sketch
}

void loop() {
  // read the input on analog pin 0
  sensorValue = analogRead(A7);
  // Send the appropriate MIDI note on or off message
  if (sensorValue > NOTE_ON_THRESHOLD) {
    if (noteSounding) {
      // Nothing to do - note is already on
    } else {
      // Value has risen above threshold - turn the note on
      usbMIDI.sendNoteOn(MIDI_NOTE, 100, MIDI_CHANNEL);
      noteSounding = true;
    }
  } else {
    if (noteSounding) {
      // Value has fallen below threshold - turn the note off
      usbMIDI.sendNoteOff(MIDI_NOTE, 100, MIDI_CHANNEL);
      noteSounding = false;
    } else {
      // Nothing to do - note is already off
    }
  }
  // Delay a bit to avoid glitches (very short notes that
  // sound because the breath falls below the threshold
  // value, then goes back above it). Adding 20
  // milleseconds of delay reduces the responsiveness
  // of the instrument, and we'll discuss better ways
  // of handling this in later posts. For now, this is
  // good enough.
  delay(20);
}
