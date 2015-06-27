const int selectPin[] = { 15, 16, 17, 18, 19, 20 };
const int dataPin[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14 };

int keyNote[6][12];
int keyNoteOld[6][12];

long lastDebounceTime[6][12];
long debounceDelay = 5;

void initPins(){

    for (int i = 0; i < 6; i++){
      pinMode(selectPin[i], OUTPUT);
    }
    for (int i = 0; i < 12; i++){
      pinMode(dataPin[i], INPUT);
    }
    
    //for (int s = 0; s < 6; s++) {
    //  for (int d = 0; d < 12; d++) {
    //    lastDebounceTime[s][d] = 0;
    //  }
    //}
    
}

void readNote(){
    //select
    for (int s = 0; s < 6; s++) {
        digitalWrite(selectPin[s], HIGH);

        //data
        for (int d = 0; d < 12; d++) {
            keyNote[s][d] = digitalRead(dataPin[d]);
            //if (keyNote[s][d] != keyNoteOld[s][d]){
            //  lastDebounceTime[s][d] = millis();
            //}
        }
        digitalWrite(selectPin[s], LOW);
    }
}

void setup()   {                
  Serial.begin(38400);
  initPins();
}

void loop() {
  readNote();
  
  for (int s = 0; s < 6; s++){
    for (int d = 0; d < 12; d++){
     // if ((millis() - lastDebounceTime[s][d]) > debounceDelay) {
      if (keyNote[s][d] == 1 && keyNote[s][d] != keyNoteOld[s][d]){
        
        if ((millis() - lastDebounceTime[s][d]) > debounceDelay) {
        //Serial.print(s);
        //Serial.print(":");
        //Serial.print(d);
        //Serial.println("=1");
        usbMIDI.sendNoteOn(35+s*5+d, 100, s+1);
        //delay(100);
        keyNoteOld[s][d] = keyNote[s][d];
        lastDebounceTime[s][d] = millis();
        }
      }
        else if (keyNote[s][d] == 0 && keyNote[s][d] != keyNoteOld[s][d]){
          if ((millis() - lastDebounceTime[s][d]) > debounceDelay) {
        //Serial.print(s);
        //Serial.print(":");
        //Serial.print(d);
        //Serial.println("=0");
        usbMIDI.sendNoteOff(35+s*5+d, 100, s+1);
        //delay(100);
        keyNoteOld[s][d] = keyNote[s][d];
        lastDebounceTime[s][d] = millis();
        }
      }
    }
  }
}
