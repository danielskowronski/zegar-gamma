#include <RTClib.h>
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

#define I2C_ADDR          0x27 
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

#define thm_in_pin 7

LiquidCrystal_I2C	lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

RTC_DS1307 rtc;
char monthsNames[12][4] = { "jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec" };

void setup() {  
  lcd.begin (16,2);
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);
  
  lcd.home ();
  lcd.print("Zegar Gamma [ds]");  
  lcd.setCursor(0,1);
  lcd.print("build 0004");
  
  for (int i=5; i>=0; i--){
    lcd.setCursor(15,1);lcd.print(i);
    delay(350);
  }
  lcd.clear();
  
  Serial.begin(57600);
  if (! rtc.begin()) {
    lcd.setCursor(0,0);lcd.println("No RTC found");
    while (1);
  }

  if (! rtc.isrunning()) {
    lcd.setCursor(0,0);lcd.println("No date set");
    lcd.setCursor(0,1);lcd.println("Date from code");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    delay(2000);
  }
  
  lcd.clear();
}

DateTime now;
void loop(){  
  now= rtc.now();
  
  if (secondChanged()){
    displayStandardTimeDateLine();
    displaySecondLine(); 
  }
  
  
  
  
  delay(100);
}
