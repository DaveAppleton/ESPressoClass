/* 
 * EPresso 1.0 LED_BUILTIN = 16;
 * EPresso 2.0 LED_BUILTIN = 2;
 */
#include <ESPert.h>

ESPert espert;

void setup() {
  Serial.begin(115200);
   espert.init();
   espert.oled.init();
  Serial.println("ADC init");
}

void loop() {
  espert.oled.clear();
  espert.oled.setCursor(6, 32);
  int out = 0;
  for (int i = 0; i < 100; i++) {
    out += analogRead(A0);
  }
  Serial.println("ADC: " + String(out));
  if (out < 50) espert.oled.println("DARK");
  else if (out > 200) espert.oled.println("VERY BRIGHT");
  else espert.oled.println("BRIGHT");
  espert.oled.update();
  delay(1000);
}
