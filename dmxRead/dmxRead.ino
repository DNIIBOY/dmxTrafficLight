#include <DMXSerial.h>  // https://github.com/mathertel/DMXSerial

#define RED 22
#define YELLOW 23
#define GREEN 24

int startAddress = 1;

void setup() {
  DMXSerial.init(DMXReceiver);
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  unsigned long lastPacketTime = DMXSerial.noDataSince();
  int redVal = DMXSerial.read(startAddress);
  int yellowVal = DMXSerial.read(startAddress + 1);
  int greenVal = DMXSerial.read(startAddress + 2);
  
  digitalWrite(RED, redVal > 128);
  digitalWrite(YELLOW, yellowVal > 128);
  digitalWrite(GREEN, greenVal > 128);
}
