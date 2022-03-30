#include <MIDIUSB.h>

const int midiChannel = 0;
const int CC = 1;
const int fromMIN = 100;
const int fromMAX = 185;
const int toMIN = 0;
const int toMAX = 127;

int pressureVal8;
int ccVal;
int serialVal;

void setup() {

  pressureVal = analogRead(A0);

  Serial.begin(9600);

  while (!Serial1);
}

void reading(){

  pressureVal = analogRead(A0);
  
  Serial.println(pressureVal);
  
  ccVal = map(pressureVal, fromMIN, fromMAX, toMIN, toMAX);

  Serial.println(ccVal);
  
}

void controlChange(byte channel, byte control, byte value) {
  
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  
  MidiUSB.sendMIDI(event);

}

void sendMidiData() {

  if(ccVal >= 127)
    ccVal = 127;
  
  controlChange(midiChannel, CC, ccVal);

}

void serialRead(){

  if(Serial.available() > 0)
    serialVal = Serial.read();
  
}

void loop() {

  reading();

  sendMidiData();

  serialRead();
  
}
