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

void setup() {
  lcd.begin (16,2); //  <<----- My LCD was 16x2
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);
  
  lcd.home ();
  lcd.print("Zegar Gamma [ds]");  
  lcd.setCursor(0,1);
  lcd.print("build 0001");
  
  for (int i=5; i>=0; i--){
    lcd.setCursor(15,1);lcd.print(i);
    delay(500);
  }
}

int n=0;
void loop(){
  lcd.clear();
  lcd.setCursor(0,0); lcd.print("znak #");
  lcd.setCursor(6,0); lcd.print(n);
  lcd.setCursor(0,1); lcd.print(char(n));
  
  delay(500);
  n++;
  if (n>256) n=0;
}

