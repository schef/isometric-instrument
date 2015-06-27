
#define MIDI_CHANNEL 1
// For this sketch, we only can play one note
#define MIDI_NOTE 60 // Middle C (C4)
// The threshold level for sending a note on event. If the
// sensor is producing a level above this, we are in note on
// state, otherwise note off
#define NOTE_ON_THRESHOLD 200

// We keep track of whether a note is sounding or not,
// so we know whether to send a note on or off event.
boolean noteSounding = false;
// The value read from the sensor
int sensorValue;

int button;

long butRead;
long butReadOld;

int deb = 0;
int debLast = 0;

void setup() {
  // Nothing to initialize for this sketch
  pinMode(15, OUTPUT);
  pinMode(2, INPUT);
  digitalWrite(15, HIGH);
}

void loop() {
  butRead = digitalRead(2);
  if(butRead == 1 && butRead != butReadOld){
    if(millis() - deb > 5){
    button = 1;
    butReadOld = butRead;
    deb = millis();
    }
  }
  else if (butRead == 0 && butRead != butReadOld){
    if (millis() - deb > 5){
    button = 0;
    butReadOld = butRead;
    deb = millis();
    }
  }
  // read the input on analog pin 0
  sensorValue = analogRead(A7);
  // Send the appropriate MIDI note on or off message
  if (sensorValue > NOTE_ON_THRESHOLD) {
    if (noteSounding && button == 1) {
    }
    else if (noteSounding && button == 0) {
      if(millis() - debLast > 5){
      usbMIDI.sendNoteOff(MIDI_NOTE, 100, MIDI_CHANNEL);
      noteSounding = false;
      debLast = millis();
      }
    }
    else if (noteSounding == false && button == 1) {
      if(millis() - debLast > 5){
      usbMIDI.sendNoteOn(MIDI_NOTE, 100, MIDI_CHANNEL);
      noteSounding = true;
      debLast = millis();
      }
    }
    else if (noteSounding == false && button == 0) {
    }
  }
  else { 
    if (noteSounding && button == 1) {
      if(millis() - debLast > 5){
      usbMIDI.sendNoteOff(MIDI_NOTE, 100, MIDI_CHANNEL);
      noteSounding = false;
      debLast = millis();
      }
    }
    else if (noteSounding && button == 0){
      if(millis() - debLast > 5){
      usbMIDI.sendNoteOff(MIDI_NOTE, 100, MIDI_CHANNEL);
      noteSounding = false;
      debLast = millis();
      }
      // Nothing to do - note is already off
    }
    else if (noteSounding == false && button == 1) {
    }
    else if (noteSounding == false && button == 0){
    }
  }
  // Delay a bit to avoid glitches (very short notes that
  // sound because the breath falls below the threshold
  // value, then goes back above it). Adding 20
  // milleseconds of delay reduces the responsiveness
  // of the instrument, and we'll discuss better ways
  // of handling this in later posts. For now, this is
  // good enough.
}
