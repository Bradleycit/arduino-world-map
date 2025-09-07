#include <Adafruit_NeoPixel.h>
#include <smooth.h>
#include <Wire.h>
#include <RTClib.h>

const byte StripPin = 6;
const byte ButtonPin = 0; // Digital Pin 2
const byte PhotoPin = A1;
const byte PotPin = A0;
const byte LEDPin = 13;
const byte NumModes = 2;
const byte NumLED = 150;
const float Pi = 3.14159;
const byte x[NumLED] = {3, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 8,
9, 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 14, 15, 
17, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 19, 20, 21, 22, 
24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 25, 26, 27, 29, 30, 30, 
30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 31, 32, 33, 34, 36, 36, 36, 
36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 38, 39, 40, 42, 42, 42, 42, 
42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 43, 44, 45, 46, 46};
byte Intensity, Brightness;
volatile byte Selection = 0;
volatile unsigned long LastInterrupt = 0;
RTC_DS1307 rtc;
runningAverage value (30);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NumLED, StripPin, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  rtc.begin();
  strip.begin();
  attachInterrupt(ButtonPin, swap, RISING);
  pinMode(PotPin, INPUT);
  pinMode(PhotoPin, INPUT);
  pinMode(LEDPin, OUTPUT);
  for (int i = 0; i<NumLED; i++){
    strip.setPixelColor(i,0,0,0); 
  }
  strip.show();
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); uncomment if you need to set the time on your RTC
}

void loop() {
  
  if (Selection == 0){
    setBrightness();
    timeMode();
  }

  else if (Selection == 1){
    rainbowCycle(20);
  }

  else if (Selection == 2){
    off();
  }
}

void rainbowCycle(uint8_t wait) {
  uint16_t j;
  uint8_t i;

  for(j=0; j<256*5; j++) {
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    if(Selection != 1) break;
    setBrightness();
    goodDelay(wait);
  }
}

uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

void timeMode(){
  DateTime now = rtc.now();
  for (byte i = 0; i<NumLED; i++){
    Intensity = (pow(sin(Pi*(float)x[i]/48.0+Pi*((1.0/24.0)*(float)now.hour()+(1.0/1440.0)*(float)now.minute()+(1.0/86400.0)*(float)now.second())-Pi/4), 4))*255.0;
    strip.setPixelColor(i, Intensity, Intensity, Intensity*0.8);
  }
  strip.show();
}

void off(){
  for (int i = 0; i<NumLED; i++){
    strip.setPixelColor(i, 0, 0, 0);
  }
  strip.show();
}

void setBrightness(){
  strip.setBrightness(value.smooth(map((float)analogRead(PotPin)*constrain(map(analogRead(PhotoPin), 400, 900, 0, 1000)/1000.0, 0.2, 1.0),0,1023,0,255)));
}

void swap(){
  if (millis() - LastInterrupt > 200){
    if (Selection == NumModes) Selection = 0;
    else Selection++;
  }
  LastInterrupt = millis();
}