#include <DMXSerial.h>  // https://github.com/mathertel/DMXSerial

void setup() {
  DMXSerial.init(DMXReceiver);
  Serial.begin(9600);
}

void loop() {
  int dmxVal = DMXSerial.read(startAddress);
  Serial.println(dmxVal);
}
