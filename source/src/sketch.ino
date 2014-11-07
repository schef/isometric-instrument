// Pin Definitions
//These are pin definitions for isometric-instrument on mega2560

//const int dataPin[] = { 23, 25, 27, 29, 31, 33, 35, 37 };
const int dataPin[] = { 37, 35, 33, 31, 29, 27, 25, 23 };

//const int selectPin[] = { 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44 };
const int selectPin[] = { 44, 42, 40, 38, 36, 34, 32, 30, 28, 26, 24, 22 };

//const int sustainPin = 12;
//int sustainStatus;
//int sustainStatusOld;

int keyNote[8][12];
int keyNoteOld[8][12];

boolean keyStatus[8][127];
boolean keyStatusOld[8][127];

int octave = 0;
int base = 35;

int formula = 0;

const int octaveUp = 85;
const int octaveDown = 84;
const int fn = 11;

//long lastDebounceTime[80];  // the last time the output pin was toggled
//long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup()
{
    pinMode(selectPin[0], OUTPUT);
    pinMode(selectPin[1], OUTPUT);
    pinMode(selectPin[2], OUTPUT);
    pinMode(selectPin[3], OUTPUT);
    pinMode(selectPin[4], OUTPUT);
    pinMode(selectPin[5], OUTPUT);
    pinMode(selectPin[6], OUTPUT);
    pinMode(selectPin[7], OUTPUT);
    pinMode(selectPin[8], OUTPUT);
    pinMode(selectPin[9], OUTPUT);
    pinMode(selectPin[10], OUTPUT);
    pinMode(selectPin[11], OUTPUT);

    pinMode(dataPin[0], INPUT);
    pinMode(dataPin[1], INPUT);
    pinMode(dataPin[2], INPUT);
    pinMode(dataPin[3], INPUT);
    pinMode(dataPin[4], INPUT);
    pinMode(dataPin[5], INPUT);
    pinMode(dataPin[6], INPUT);
    pinMode(dataPin[7], INPUT);

    //    pinMode(sustainPin, INPUT);

    Serial.begin(31250);
    //Serial.begin(9600);
    //Serial.print("ready:");
    //Serial.println("");
}

void loop()
{
    //read pins
    readNote();

    //checkOctaves 
    //    if (keyNote[octaveUp] != keyNoteOld[octaveUp] && octave < 4){
    //        if(keyNote[octaveUp]){
    //            octave++;
    //            keyNoteOld[octaveUp] = 1;
    //            changeOctave(1, formula);
    //        }
    //        else
    //            keyNoteOld[octaveUp] = 0;
    //    }
    //    if (keyNote[octaveDown] != keyNoteOld[octaveDown] && octave > 0){
    //        if(keyNote[octaveDown]){
    //            octave--;
    //            keyNoteOld[octaveDown] = 1;
    //            changeOctave(-1, formula);
    //        }
    //        else
    //            keyNoteOld[octaveDown] = 0;
    //    }

    //basMode
    //formula = 0;
    //banjoMode
    //formula = 1;
    //kvintMode
    //formula = 2;
    //majorThirdMode
    //formula = 3;

    //checkNotes
    for (int s = 0; s < 12; s++){
        for (int d = 0; d < 8; d++){
            if ( d == 0 && s == 11){
                if (keyNote[0][0])
                    formula = 0;
                else if (keyNote[0][1])
                    formula = 1;
                else if (keyNote[0][2])
                    formula = 2;
                else if (keyNote[0][3])
                    formula = 3;
            }
            else{
            if (keyNote[d][s] && keyNote[0][11] == 0){
                //noteOn(d, instrument(formula, s, d, base, octave), 100);
                keyStatus[d][instrument(formula, s, d, base, octave)] = true;
            }
            else{
                //noteOn(d, instrument(formula, s, d, base, octave), 0);
                keyStatus[d][instrument(formula, s, d, base, octave)] = false;
            }
            }
        }
    }

    //noteOn and noteOff
    for (int c = 0; c < 8; c++){
        for (int n = 0; n < 127; n++){
            if(keyStatus[c][n] != keyStatusOld[c][n]){
                if(keyStatus[c][n]){
                    noteOn(c, n, 100); 
                    keyStatusOld[c][n] = true;
                }
                else{
                    noteOn(c, n, 0);
                    keyStatusOld[c][n] = false;
                }
            }
        }
    }
    // output out the state of the pedal:
    //    sustainStatus = digitalRead(sustainPin);
    //    if(sustainStatus != sustainStatusOld){
    //        if(sustainStatus){
    //            //MIDI.sendControlChange(64,127,1);
    //            command(176, 64, 127);
    //        }
    //        else{
    //            //MIDI.sendControlChange(64,0,1);
    //            command(176, 64, 0);
    //        }
    //        sustainStatusOld = sustainStatus;
    //    }
}

int instrument(int formula, int select, int data, int base, int octave){
    if (formula == 0){
        return select + data * 5 + base + octave * 12;
    }
    else if (formula == 1){
        if(data == 0) //zica D
            return select + data * 5 + base + octave * 12;
        else if(data == 1) // zica G
            return select + data * 5 + base + octave * 12;
        else if(data == 2) // zica H
            return select + data * 5 - 1+ base + octave * 12;
        else if(data == 3) // zica D
            return select + data * 5 - 3 + base + octave * 12;
        else if(data == 4) // ponovo zica D
            return select + data * 5 + base + octave * 12;
        else if(data == 5) // zica G
            return select + data * 5 + base + octave * 12;
        else if(data == 6) // zica H
            return select + data * 5 - 1+ base + octave * 12;
        else if(data == 7) // zica D
            return select + data * 5 - 3 + base + octave * 12;
    }
    else if (formula == 2){
        if(data == 0)
            return select + data * 5 + base + octave * 12;
        else if(data == 1)
            return select + data * 5 + 2 + base + octave * 12;
        else if(data == 2)
            return select + data * 5 + 4 + base + octave * 12;
        else if(data == 3)
            return select + data * 5 + 6 + base + octave * 12;
        else if(data == 4)
            return select + data * 5 + 8 + base + octave * 12;
        else if(data == 5)
            return select + data * 5 + 10 + base + octave * 12;
        else if(data == 6)
            return select + data * 5 + 12 + base + octave * 12;
        else if(data == 7)
            return select + data * 5 + 14 + base + octave * 12;
    }
    else if (formula == 3){
        if(data == 0)
            return select + data * 5 + base + octave * 12;
        else if(data == 1)
            return select + data * 5 - 1 + base + octave * 12;
        else if(data == 2)
            return select + data * 5 - 2 + base + octave * 12;
        else if(data == 3)
            return select + data * 5 - 3 + base + octave * 12;
        else if(data == 4)
            return select + data * 5 - 4 + base + octave * 12;
        else if(data == 5)
            return select + data * 5 - 5 + base + octave * 12;
        else if(data == 6)
            return select + data * 5 - 6 + base + octave * 12;
        else if(data == 7)
            return select + data * 5 - 7 + base + octave * 12;
    }
}

//void changeOctave(int i, int formula){
//    //octaveUp
//    if(i == 1)
//    for(int i=0; i<96; i++){
//      if(keyNote[i])
//          keyShift[i] = 1;
//          noteOff[i];
//    }
//    for(int i=0; i<96; i++){
//          noteOn[i+12];
//    }
//    //octaveDown
//    else if(i == -1)
//
//}

void readNote(){
    //select
    for (int s = 0; s < 12; s++) {
        digitalWrite(selectPin[s], HIGH);

        //data
        for (int d = 0; d < 8; d++) {
            keyNote[d][s] = digitalRead(dataPin[d]);
        }
        digitalWrite(selectPin[s], LOW);
    }
}

void serialPrint(int channel, int i, int stanje, int nota){ 
    Serial.print("c");
    Serial.print(channel);
    Serial.print("-");
    Serial.print(i);
    Serial.print(":");
    Serial.print(stanje);
    Serial.print("-nota-");
    Serial.print(nota);
    Serial.println(""); 
}

void noteOn(int channel, int pitch, int velocity) {
    command(0x90 + channel, pitch, velocity);
}


void midiChannelExpression(int channel, int value) {
    // Modulation wheel effect
    command(0xB0 + channel, 0x01, value);
}

void command(int cmd, int value1, int value2) {
    Serial.write(cmd);
    Serial.write(value1);
    Serial.write(value2);
}
