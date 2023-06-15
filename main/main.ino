#include <DMXSerial.h>  // https://github.com/mathertel/DMXSerial

#define RED 22
#define YELLOW 23
#define GREEN 24

#define UPBTNPIN 0
#define DOWNBTNPIN 0
#define STATUSPIN 4

const int debounceDelay = 50;

int startAddress = 1;

void setup() {
  DMXSerial.init(DMXReceiver);

  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);

  pinMode(UPBTNPIN, INPUT);
  pinMode(DOWNBTNPIN, INPUT);
  pinMode(STATUSPIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  unsigned long lastPacketTime = DMXSerial.noDataSince();
  if (lastPacketTime < 2000){
    digitalWrite(STATUSPIN, HIGH);
    int redVal = DMXSerial.read(startAddress);
    int yellowVal = DMXSerial.read(startAddress + 1);
    int greenVal = DMXSerial.read(startAddress + 2);
    digitalWrite(RED, redVal > 128);
    digitalWrite(YELLOW, yellowVal > 128);
    digitalWrite(GREEN, greenVal > 128);
  }
  else{
    digitalWrite(STATUSPIN, LOW);
    digitalWrite(RED, LOW);
    digitalWrite(YELLOW, LOW);
    digitalWrite(GREEN, LOW);
  }
}
