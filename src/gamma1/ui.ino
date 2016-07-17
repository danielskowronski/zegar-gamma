int lastSecond = -1;
boolean secondChanged(){
  if (lastSecond != now.second()){
    lastSecond = now.second();
    return true;
  }
  else {
    return false;
  }
}

void displayStandardTimeDateLine(){
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
}

int currentMode = 0;
void displaySecondLine(){
  lcd.setCursor(0,1);
  int thm = 0;
  for (int i=0; i<100; i++){
    thm += (analogRead(thm_in_pin)/1024.0)*5000;
  }
  thm /= 100;
  if (thm<10) lcd.print("0"); 
  lcd.print(thm/10);lcd.print(".");lcd.print(thm%10);
  lcd.print(char(223));lcd.print("C");
}
