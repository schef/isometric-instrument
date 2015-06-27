
#define MOD_WHEEL_CONTROLLER 11
#define MIDI_CHANNEL 1
// Send continuous controller message no more than
// every CC_INTERVAL milliseconds
#define CC_INTERVAL 20
// Only send CC data if the pressure sensor reading
// a value larger than this.
#define BREATH_THRESHOLD 81

// The last time we sent a CC value
//unsigned long ccSendTime = 0L;
// The value read from the sensor
//int sensorValue;
// The CC value we will send
//int ccVal = 0;
// The last CC value we sent
//int lastCcVal = 0;

const int selectPin[] = { 15, 16, 17, 18, 19, 20 };
const int dataPin[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14 };

int keyRead[7][13];
int keyReadOld[7][13];
boolean keyButton[7][13];
boolean keyButtonOld[7][13];
boolean noteSounding[7][13];

unsigned long debounceButton[7][13];
unsigned long buttonDel[7][13];
unsigned long debounceSound[7][13];
long debounceDelay = 7;

int baznaOktava = 35;

void initPins(){
  for (int i = 0; i < 6; i++){
    pinMode(selectPin[i], OUTPUT);
  }
  for (int i = 0; i < 12; i++){
    pinMode(dataPin[i], INPUT);
  }
}

void readNote(){
  //select
  for (int s = 0; s < 6; s++) {
    digitalWrite(selectPin[s], HIGH);

    //data
    for (int d = 0; d < 12; d++) {
      keyRead[s][d] = digitalRead(dataPin[d]);
      if (keyRead[s][d] == 1 && keyRead[s][d] != keyReadOld[s][d]){
        if (millis() - debounceButton[s][d] > debounceDelay){
          keyButton[s][d] = true;
          //Serial.print(s);
          //Serial.print(":");
          //Serial.println(d);
          keyReadOld[s][d] = keyRead[s][d];
          debounceButton[s][d] = millis();
        }
      }
      else if (keyRead[s][d] == 0 && keyRead[s][d] != keyReadOld[s][d]){
        if (millis() - debounceButton[s][d] > debounceDelay){
          keyButton[s][d] = false;
          keyReadOld[s][d] = keyRead[s][d];
          debounceButton[s][d] = millis();
        }
      }
    }
    digitalWrite(selectPin[s], LOW);
  }
}

void setup()   {
  Serial.begin(38400);
  initPins();
}

void loop() {
//    //breath
//    // Only read the sensor if enough time has passed
//    if (millis() - ccSendTime > CC_INTERVAL) {
//      // read the input on analog pin 0
//      sensorValue = analogRead(A7);
//      if (sensorValue > BREATH_THRESHOLD) {
//        // Map the value, which may range from BREATH_THRESHOLD
//        // to 1023, to a value in the range 0 to 127, which is
//        // the valid range for a MIDI continuous controller
//        ccVal = map(sensorValue, BREATH_THRESHOLD, 1023, 0, 127);
//        if (ccVal != lastCcVal){
//          // And send the value as a MIDI CC message
//          usbMIDI.sendControlChange(MOD_WHEEL_CONTROLLER, ccVal, MIDI_CHANNEL);
//          ccSendTime = millis();
//          lastCcVal = ccVal;
//        }
//      } 
//      else if (lastCcVal > 0) {
//        // The pressure has just dropped below the threshold, so
//        // send a CC value of zero
//        usbMIDI.sendControlChange(MOD_WHEEL_CONTROLLER, 0, MIDI_CHANNEL);
//        ccSendTime = millis();
//        lastCcVal = 0;
//      }
//    }

  readNote();

  for (int s = 0; s < 6; s++){
    for (int d = 0; d < 11; d++){

////note on na puhanje
//    if (ccVal > 5){
//      if (keyButton[s][d] == true && noteSounding[s][d] == true){
//        //
//      }
//      else if (keyButton[s][d] == true && noteSounding[s][d] == false) {
//        if(millis() - debounceSound[s][d] > debounceDelay){ 
//        usbMIDI.sendNoteOn(35+s*5+d, 100, 1+s);
//        noteSounding[s][d] = true;
//        debounceSound[s][d] = millis();
//        }
//        }
//      else if (keyButton[s][d] == false && noteSounding[s][d] == true){
//        if(millis() - debounceSound[s][d] > debounceDelay){ 
//        usbMIDI.sendNoteOff(35+s*5+d, 100, 1+s);
//        noteSounding[s][d] = false;
//        debounceSound[s][d] = millis();
//        }
//        }
//      else if (keyButton[s][d] == false && noteSounding[s][d] == false){
//        //
//        }
//    }
//    else {
//      if (keyButton[s][d] == true && noteSounding[s][d] == true){
//        if(millis() - debounceSound[s][d] > debounceDelay){ 
//        usbMIDI.sendNoteOff(35+s*5+d, 100, 1+s);
//        noteSounding[s][d] = false;
//        debounceSound[s][d] = millis();
//      }
//      }
//      else if (keyButton[s][d] == true && noteSounding[s][d] == false){
//        //
//      }
//      else if (keyButton[s][d] == false && noteSounding[s][d] == true){
//        if(millis() - debounceSound[s][d] > debounceDelay){ 
//        usbMIDI.sendNoteOff(35+s*5+d, 100, 1+s);
//        noteSounding[s][d] = false;
//        debounceSound[s][d] = millis();
//      }
//      }
//      else if (keyButton[s][d] == false && noteSounding[s][d] == false){
//        //
//      }
//    }

//samo gumbi
  if(keyButton[5][0] == true){
     baznaOktava = 35 + 12;
  }
  else if(keyButton[0][10] == true){
     baznaOktava = 35;
  }
  else if(keyButton[s][d] == true){
    if (keyButton[s][d] != keyButtonOld[s][d]){
    if(millis() - buttonDel[s][d] > 50){
    usbMIDI.sendNoteOn(baznaOktava+12+s*5+d, 100, 1);
    keyButtonOld[s][d] = keyButton[s][d];
    buttonDel[s][d] = millis();
    }
    }
  }

  
  
  else if (keyButton[s][d] == false){
    if (keyButton[s][d] != keyButtonOld[s][d]){
    if(millis() - buttonDel[s][d] > 50){
    usbMIDI.sendNoteOff(baznaOktava+12+s*5+d, 100, 1);
    keyButtonOld[s][d] = keyButton[s][d];
    buttonDel[s][d] = millis();
    }
    }
  }

    }
    }


  }
