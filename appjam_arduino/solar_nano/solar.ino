#include <PS2Keyboard.h>
#include <Adafruit_NeoPixel.h>
#define NEO_PIN 7

const int DataPin = 2;
const int IRQpin =  3;
const int piezo = 6;
int tones[] = {200, 294, 330, 349, 392, 440, 494, 523};

Adafruit_NeoPixel strip = Adafruit_NeoPixel(10, NEO_PIN, NEO_GRB + NEO_KHZ800);
PS2Keyboard keyboard;

void setup() {
  delay(1000);
  keyboard.begin(DataPin, IRQpin);
  pinMode(piezo, OUTPUT);
  Serial.begin(9600);
  Serial.println("Keyboard Test:");
  strip.begin(); //네오픽셀을 초기화하기 위해 모든LED를 off시킨다
  strip.show();
}

void loop() {
  String barcode = "";
  if (keyboard.available()) {
    while (keyboard.available()) {
      char c = keyboard.read();
      barcode += c;
    }
    Serial.println(barcode.toInt());
  }
  else {
    while (Serial.available()) {
      String ho = "";
      char color = Serial.read();
      ho += color;
      if (ho.toInt() == 1) {
        tone(piezo,tones[0]); delay(300);
        colorWipe(strip.Color(255, 0, 0), 20); //빨간색 출력
        colorWipe(strip.Color(0, 0, 0), 10); //빨간색 출력
        noTone(piezo);
        delay(100);
        tone(piezo,tones[0]); delay(300);
        colorWipe(strip.Color(255, 0, 0), 20); //빨간색 출력
        colorWipe(strip.Color(0, 0, 0), 10); //빨간색 출력
        noTone(piezo);
        delay(100);
        tone(piezo,tones[0]); delay(300);
        noTone(piezo);        
        colorWipe(strip.Color(255, 0, 0), 20); //빨간색 출력
        colorWipe(strip.Color(0, 0, 0), 10); //빨간색 출력
        colorWipe(strip.Color(255, 0, 0), 20); //빨간색 출력
        colorWipe(strip.Color(0, 0, 0), 10); //빨간색 출력
        colorWipe(strip.Color(255, 0, 0), 20); //빨간색 출력
      }
      else if (ho.toInt() == 2) {
        colorWipe(strip.Color(0, 0, 255), 20); //파란색 출력
        colorWipe(strip.Color(0, 0, 0), 10); //빨간색 출력
        colorWipe(strip.Color(0, 0, 255), 20); //파란색 출력
        colorWipe(strip.Color(0, 0, 0), 10); //빨간색 출력
        colorWipe(strip.Color(0, 0, 255), 20); //파란색 출력
        colorWipe(strip.Color(0, 0, 0), 10); //빨간색 출력
        colorWipe(strip.Color(0, 0, 255), 20); //파란색 출력
        colorWipe(strip.Color(0, 0, 0), 10); //빨간색 출력
        colorWipe(strip.Color(0, 0, 255), 20); //파란색 출력
        colorWipe(strip.Color(0, 0, 0), 10); //빨간색 출력
      }
    }
    rainbow(20);
  }
  delay(100);
}

int rainbow(uint8_t wait) {
  uint16_t i, j;
  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
      if (keyboard.available()) return 1;
      if(Serial.available()) return 1;
    }
    strip.show();
    delay(wait);
  }
}

uint32_t Wheel(byte WheelPos) {
  if (WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}
