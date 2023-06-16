#include <DMXSerial.h>  // https://github.com/mathertel/DMXSerial
#include <TM1637Display.h>

#define RED 22
#define YELLOW 23
#define GREEN 24

#define STATUSPIN 4

#define CLK 8
#define DIO 9

#define BTN_UP 11
#define BTN_DOWN 12

int startAddress = 1;
TM1637Display display(CLK, DIO);

void setup() {
  DMXSerial.init(DMXReceiver);
  display.setBrightness(5);

  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);

  pinMode(BTN_UP, INPUT_PULLUP);
  pinMode(BTN_DOWN, INPUT_PULLUP);

  Serial.begin(9600);
  display.clear();
  display.showNumberDec(startAddress, false, 3, 0);

  //Bollocks
  digitalWrite(STATUSPIN, HIGH);
}

void loop() {

  int it = 0;
if(digitalRead(BTN_UP) == LOW && digitalRead(BTN_DOWN) == HIGH) {
  for (int i = startAddress + 1; i <= 255 && digitalRead(BTN_UP) == LOW; i++) {

    display.showNumberDec(i, false, 3, 0);

    if(it < 18) {
    delay(400 - (it * it));
    } else {
      delay(70);
    }

    startAddress = i;
    it++;
  }
} else if(digitalRead(BTN_DOWN) == LOW && digitalRead(BTN_UP) == HIGH){
  for (int i = startAddress - 1; i >= 1 && digitalRead(BTN_DOWN) == LOW; i--) {
  display.showNumberDec(i, false, 3, 0);
  if(it < 18) {
  delay(400 - (it * it));
  // Serial.println(400 - (it * it));
  // Serial.println(it);

  } else {
    delay(70);
  }
  startAddress = i;
  it++;
 }
} else if(digitalRead(BTN_DOWN) == LOW && digitalRead(BTN_UP) == LOW){
  //Serial.println("BOTH BUTTONS PRESSED!");
}

  unsigned long lastPacketTime = DMXSerial.noDataSince();
  int redVal = DMXSerial.read(startAddress);
  int yellowVal = DMXSerial.read(startAddress + 1);
  int greenVal = DMXSerial.read(startAddress + 2);

  Serial.println(startAddress);
  
  digitalWrite(RED, redVal > 128);
  digitalWrite(YELLOW, yellowVal > 128);
  digitalWrite(GREEN, greenVal > 128);
}
