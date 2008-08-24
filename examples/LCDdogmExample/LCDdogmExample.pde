#include <LCDdogmSPI.h>

#define CSB_PIN 10
#define RS_PIN 9
#define LCD_LINES 3

// This initializes for a 3 LINES display

LCDdogmSPI lcd = LCDdogmSPI(LCD_LINES, CSB_PIN, RS_PIN);

void setup() {
  lcd.init();
  lcd.cursorTo(2,7);
  lcd.println("theqtisch");
}

void loop() {
  delay(10); 
}
