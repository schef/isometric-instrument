#define MOD_WHEEL_CONTROLLER 1
#define MIDI_CHANNEL 1
// Send continuous controller message no more than
// every CC_INTERVAL milliseconds
#define CC_INTERVAL 20
// Only send CC data if the pressure sensor reading
// a value larger than this.
#define BREATH_THRESHOLD 81

// The last time we sent a CC value
unsigned long ccSendTime = 0L;
// The value read from the sensor
int sensorValue;
// The CC value we will send
int ccVal;
// The last CC value we sent
int lastCcVal = 0;

button = 0;
buttonOld = 0;

void setup() {
  // Nothing to initialize for this sketch
  pinMode(15, OUTPUT);
  pinMode(2, INPUT);
  digitalWrite(15, HIGH);
}

void loop() {
  // Only read the sensor if enough time has passed
  if (millis() - ccSendTime > CC_INTERVAL) {
    // read the input on analog pin 0
    sensorValue = analogRead(A7);
    if (sensorValue > BREATH_THRESHOLD) {
      // Map the value, which may range from BREATH_THRESHOLD
      // to 1023, to a value in the range 0 to 127, which is
      // the valid range for a MIDI continuous controller
      ccVal = map(sensorValue, BREATH_THRESHOLD, 1023, 0, 127);
      if (ccVal != lastCcVal){
      // And send the value as a MIDI CC message
      usbMIDI.sendControlChange(MOD_WHEEL_CONTROLLER, ccVal, MIDI_CHANNEL);
      ccSendTime = millis();
      lastCcVal = ccVal;
      }
    } 
    else if (lastCcVal > 0) {
      // The pressure has just dropped below the threshold, so
      // send a CC value of zero
      usbMIDI.sendControlChange(MOD_WHEEL_CONTROLLER, 0, MIDI_CHANNEL);
      ccSendTime = millis();
      lastCcVal = 0;
    }
  }
 
 
  button = digitalRead(2);
  if (button == 1 && button != buttonOld){
    usbMIDI.sendNoteOn(60, 100, 1);
  }
  else (button == 0 && button != buttonOld){
    usbMIDI.sendNoteOff(60, 100, 1);
  }

}
