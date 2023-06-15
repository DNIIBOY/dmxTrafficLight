#include <DMXSerial.h>  // https://github.com/mathertel/DMXSerial

void setup() {
  DMXSerial.init(DMXReceiver);
}

void loop() {
  int dmxVal = DMXSerial.read(1);
  if (dmxVal > 128){
    digitalWrite(4, HIGH);
  }
  else{
    digitalWrite(4, LOW);
  }
}
