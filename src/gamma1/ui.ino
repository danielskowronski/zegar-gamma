int thm1_history[60], thm2_history[60];

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

int incmod(int x, int mod){
  x++;
  if (x>=mod) x=0;
  return x;
}

int currIdx=0;
int trend(int* array, int start=currIdx, int count=60){
  int i=start;
  int balance=0;
  do {
         if (array[i]<array[incmod(i,count)]) balance++;
    else if (array[i]>array[incmod(i,count)]) balance--;
    i=incmod(i, count);
  } while (i!=start); 
  
  return balance;
  if (balance>0) return 1; else if (balance<0) return -1; else return 0;
}
int thmVals[2] = {0,0};
void readThm(int count=60){
  int thm=0;
  for (int i=0; i<100; i++){
    thm += (analogRead(thm_int_pin)/1024.0)*5000;
  }
  thm /= 100;
  thm /= 2; thm *= 2;
  thmVals[0]=thm;
  thm1_history[currIdx]=thm/5;
  
  sensors.requestTemperatures(); 
  thm = sensors.getTempCByIndex(0)*10;
  thmVals[1] = thm;
  thm2_history[currIdx]=thm/2;
  
  
  currIdx=incmod(currIdx, count);
}

int currentMode = 1;
int secondsInCurrentMode = -1;
const int modeCound=2;
void displaySecondLine(){
  if (secondsInCurrentMode<0){
   if (now.second()%10 != 9) return; //align thm zone changes to x0 and x5 secs
  }
  secondsInCurrentMode++;
  secondsInCurrentMode%=5;
  if (secondsInCurrentMode!=0) {
   return; 
  }
  else {
    currentMode++;
    currentMode%=2;
  }
  
  readThm();
  
  int thm = thmVals[currentMode];
  
  lcd.setCursor(0,1); 
  
  if (currentMode==0) lcd.write(byte(3)); else lcd.write(byte(4));
  int curr_trend;
  if (currentMode==0) curr_trend=trend(thm1_history); else curr_trend=trend(thm2_history);
  if (curr_trend>0){
    lcd.write(byte(0));
  }
  else if (curr_trend<0){
    lcd.write(byte(1));
  }
  else {
    lcd.print("=");
  }
  lcd.print(" ");
  if (thm<10) lcd.print("0"); 
  lcd.print(thm/10);lcd.print(".");lcd.print(thm%10);
  lcd.write(byte(2));lcd.print("                        ");
  
}
