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
int trend(int* array, int start=currIdx, int count=10){
  int i=start;
  int balance=0;
  do {
         if (array[i]<array[incmod(i,count)]) balance++;
    else if (array[i]>array[incmod(i,count)]) balance--;
    i=incmod(i, count);
  } while (i!=start); 
  
  if (balance>0) return 1; else if (balance<0) return -1; else return 0;
}
int* readThm(int count=10){
  int* vals = new int[2];
  
  int thm=0;
  for (int i=0; i<100; i++){
    thm += (analogRead(thm_in_pin)/1024.0)*5000;
  }
  thm /= 100;
  vals[0]=thm;
  
  thm1_history[currIdx]=thm;
  currIdx=incmod(currIdx, count);
  
  return vals;
}

int currentMode = 0;
void displaySecondLine(){
  int thm = readThm()[0];
  
  lcd.setCursor(0,1); 
  
  lcd.write(byte(3));
  int curr_trend = trend(thm1_history);
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
  lcd.write(byte(2));lcd.print(" ");
  
}
