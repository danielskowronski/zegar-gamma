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
  lcd.print("build 0003");
  
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

void loop(){  
  DateTime now = rtc.now();
  lcd.setCursor(0,0);
  if (now.hour()<10) lcd.print("0"); lcd.print(now.hour(), DEC);
  lcd.print(':');
  if (now.minute()<10) lcd.print("0"); lcd.print(now.minute(), DEC);
  lcd.print(':');
  if (now.second()<10) lcd.print("0"); lcd.print(now.second(), DEC);
  
  lcd.setCursor(10,0);   
  if (now.day()<10) lcd.print(" "); lcd.print(now.day(), DEC);
  lcd.print(" ");
  lcd.print(monthsNames[now.month()-1]);
  
  
  lcd.setCursor(0,1);
  lcd.print((analogRead(7)/1024.0)*500);
  lcd.print(char(223));lcd.print("C");
  
  
  delay(100);
}
