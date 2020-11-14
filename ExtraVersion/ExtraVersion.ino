#include <LCDBitmap.h>
#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
LCDBitmap bitmap(&lcd, 0, 0);  // Set the bitmap to the &lcd display at character position 0,0.

byte graph[20];
byte bars[] = { 1, 2, 4, 5, 10, 20 };

char inData[30];
char inChar;
int charIndex;
long starttime = 0;
int first = 0;

int timedisplayed = 3000;

int led = 7; 
bool ledOn = false;

const int buzzer = 9; //buzzer to arduino pin 9

struct KUND {
  int id;
  String namn;
  int betalat;
};

KUND kundlist[6];
KUND firstkund;

long day = 86400000; 
long hour = 3600000; 
long minute = 60000;
int startHour = 15;
int startMinute = 40;

int chooseAd = NULL;

//ADS

//Hederlige Harrys Bilar
String HHB1 = "Kop bil hos Harry";
String HHB2 = "En god bilaffar for harry!";
String HHB3 = "Hederlige Harrys bilar";

//Farmor ankas pajer AB
String FAP1 = "Kop paj hos Farmar Anka";
String FAP2 = "Skynda! Innan Marten atit alla pajer";

//Svarte Petters Svartbyggen
String SPS1 = "Lat Petter bygga at dig";
String SPS2 = "Bygga svart? Ring Petter";

//Långbens Detektivbyrå
String LD1 = "Mysterier? Ring Langben";
String LD2 = "Langben fixar biffen";

//Yrrol AB
String Y1 = "T-Rod - for dig som tankt klart";
String Y2 = "Claes Mansson - om flickan sjalv far valja";
int adLength = 3000; //in milliseconds

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  createKundlist();
  firstkund.namn="test";
  firstkund.betalat = 0;
  firstkund.id = 0;
  pinMode(led, OUTPUT); 
pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
}

void createKundlist(){
   KUND harry;
   harry.id=1;
  harry.namn = "Hederlige Harrys Bilar";
    harry.betalat = 5000; // 0-5000

  KUND anka;
  anka.id=2;
  anka.namn = "Farmor Ankas Pajer AB";
  anka.betalat = 3000;  // 5001-8001

  KUND peter;
  peter.id=3;
  peter.namn = "Svarte Petters Svartbyggen";
  peter.betalat = 1500; // 8002-9502

  KUND ben;
  ben.id=4;
  ben.namn = "Langbens detektivbyra";
  ben.betalat = 4000;  // 9503-13503

  KUND iot;
  iot.id=5;
  iot.namn = "iot";
  iot.betalat = 1000;  // 13504-14504

  KUND yrrol;
  yrrol.id=6;
  yrrol.namn = "Yrrol AB";
  yrrol.betalat = 6000;

  kundlist[0] = harry;
  kundlist[1] = anka;
  kundlist[2] = peter;
  kundlist[3] = ben;
  kundlist[4] = iot;
  kundlist[5] = yrrol;
}

KUND checkoutKund(int lotter){
    int i,min=0;
  for (i=0;i<sizeof(kundlist)/sizeof(KUND);i++){
    if ((min<=lotter) && lotter<(min+kundlist[i].betalat))
      return kundlist[i];
    else
      min+=kundlist[i].betalat+1;
  }
}

void playAdHHB(int num)
{
  Serial.print(num);
  chooseAd = randomize(num);
  
  if(chooseAd == 1) adFX(HHB1,"scroll",false);
  else if (chooseAd == 2) adFX(HHB2,"print",false);
  else if (chooseAd == 3) adFX(HHB3,"blink",true);
}

void playAdFAP()
{
  chooseAd = randomize(2);
  if(chooseAd == 1) adFX(FAP1,"scroll",false);
  else if (chooseAd == 2) adFX(FAP2,"print",false);
}

void playAdSPS()
{
  long currentMinute = currentMinuteApproximation();
  if (currentMinute % 2 == 0) adFX(SPS1,"scroll",false);
  else adFX(SPS2,"scroll",false);
}

void playAdLD()
{
   long currentHour = currentHourApproximation();
  if(currentHour >=6 && currentHour < 17) adFX(LD2,"print",false);
  else adFX(LD1,"print",false);
}

void playAdY() //the new ad.
{
  chooseAd = randomize(2);
  if(chooseAd == 1) adFX(Y1,"blink",true);
  else if (chooseAd == 2) adFX(Y2,"scroll",true);
}

void adFX(String message,String textEffect,bool ledEffect)
{
  digitalWrite(led, LOW);
  ledOn = false;
  bool messagePrinted = false;
  bool messageDisplayed = false;
  long adTimer = millis();
  long ledEffectTimer = adTimer;
  long blinkMessageTimer = adTimer;
  long scrollMessageTimer = adTimer;
  int ledBlinkFrequency = 500;
  int scrollindex = 0;
  int scrollLength = message.length()+16;

  while(millis() - adTimer < adLength)
  {
    //blinkLed
    if (ledEffect == true) //blinkLed();
    {
      if (millis() > ledEffectTimer + ledBlinkFrequency) 
      {
        if (ledOn == false)
        {
          digitalWrite(led, HIGH);
          ledOn = !ledOn;
        }
        if(ledOn == true)
        {
          digitalWrite(led, LOW);
          ledOn = !ledOn;
        }
        ledEffectTimer = millis();
      }
    }

    //printMessage
    if (textEffect == "print" && messagePrinted == false)
    {
      displayMessage(message);
      messagePrinted = true;
    }

    //blinkMessage
    else if (textEffect == "blink")
    {
      if(millis() > blinkMessageTimer + 1000 && messageDisplayed == true)
      {
        lcd.clear();
        messageDisplayed = false;
        blinkMessageTimer=millis();
      }
      else if(millis() > blinkMessageTimer + 500 && messageDisplayed == false)
      {
        displayMessage(message);
        messageDisplayed = true;
        blinkMessageTimer=millis();
      }
    }
//scrollMessage

    else if (textEffect == "scroll")
    {
      if(messageDisplayed==false)
      {
        lcd.setCursor(16,0);
        lcd.print(message);
        messageDisplayed=true;
      }
      if(scrollindex == scrollLength)
      {
        scrollindex = 0;
        lcd.clear();
        lcd.setCursor(16,0);
        lcd.print(message);
      }
      
      if(millis() > scrollMessageTimer + 300)
      {
        lcd.scrollDisplayLeft();
        scrollMessageTimer = millis();
        scrollindex++;
      }
    }


//  else if (textEffect == "scroll"){
//      if (messageDisplayed == false ){
//        message=message+" *** ";
//      }
//      if (millis() > scrollMessageTimer + 300 || messageDisplayed == false)
//      {
//        lcd.clear();
//        lcd.setCursor(0,0); 
//        if (message.length()-scrollindex<15){
//          lcd.print(message.substring(scrollindex,message.length()));
//          if (message.length()-scrollindex+1>0){
//            lcd.setCursor(message.length()-scrollindex,0);
//            lcd.print(message.substring(0,16-(message.length()-scrollindex)));
//          }
//          else break;
//        }
//        else
//          lcd.print(message.substring(scrollindex,scrollindex+16));
//        scrollindex++;
//        if (scrollindex==message.length()) scrollindex=0;
//        scrollMessageTimer=millis();
//        messageDisplayed =true;
//      }
//  }



//  else if (textEffect == "scroll"){
//      if (messageDisplayed == false ){
//        message="               "+message;
//      }
//      if (millis() > scrollMessageTimer + 300 || messageDisplayed == false)
//      {
//            lcd.clear();
//            lcd.setCursor(0,0);
//            //lcd.print(message.substring(scrollindex));
//            if (scrollindex+16>message.length())    lcd.print(message.substring(scrollindex,message.length()));
//            else    lcd.print(message.substring(scrollindex,scrollindex+16));
//            scrollindex++;
//            if (scrollindex==message.length()) scrollindex=0;
//            scrollMessageTimer=millis();
//            messageDisplayed =true;
//      }
//    }

  }
}

long currentHourApproximation()
{
  long millisecondsElapsedToday = startHour * hour + startMinute * minute + millis();
  long hours = millisecondsElapsedToday  / hour;
  return hours;
}

long currentMinuteApproximation()
{
  long millisecondsElapsedToday = startHour * hour + startMinute * minute + millis();
  long minutes = ((millisecondsElapsedToday % day) % hour) / minute;
  return minutes;
}

int randomize(int range)
{
  int r = rand() % range;
  return r+1;
}

void playIOT(){
    lcd.setCursor(5, 0);

  lcd.print("IOT 20");
  bitmap.begin();  // Then initialize the LCD bitmap.
  long displaystarttime=millis();
  while (millis()<displaystarttime+timedisplayed){
   byte curr_bars = bars[(millis()/3000)%6];
    for (byte x=0; x<curr_bars; x++) {
    graph[x] = random(0, BITMAP_H+1);
    }
  
    bitmap.barGraph(curr_bars, graph, ON, UPDATE);  // Display the bar graph.
    delay(50);
  }
}

void athinaBlinkMessage(String message){
  long displaystarttime=millis();
  while (millis()<displaystarttime+timedisplayed){
    lcd.clear();
    displayMessage(message);
    delay(750);
    lcd.clear();
    delay(500);
  }
}

void displayMessage (String message){
  if(message.length()<17)
    lcd.print(message);
  else if (message.length()<32 && message.substring(16)==" "){
    lcd.print(message);
    lcd.setCursor(0,1);
    lcd.print(message.substring(16));
  }
  else if (message.length()<32 && message.substring(16)!=" "){
    int index=message.lastIndexOf(" ", 16);
    lcd.print(message.substring(0,index));
    lcd.setCursor(0, 1);
    lcd.print(message.substring(index+1));
  }
  else{
    int index=message.indexOf(" ");
    lcd.print(message.substring(0,index));
    delay(2000);
    lcd.clear(); 
    int breakIndex=message.lastIndexOf(" ", 16+index);
    lcd.print(message.substring(index+1,breakIndex));
    lcd.setCursor(0, 1);
    lcd.print(message.substring(breakIndex+1));
    delay(2000);
    lcd.clear();
  }
}

void athinaPrintMessage(String message){
  lcd.clear();
  long displaystarttime=millis();
  while (millis()<displaystarttime+timedisplayed){
    lcd.setCursor(0,0);
    displayMessage(message);
  }
}

void athinaScrollMessage(String message){
  lcd.clear();
  long displaystarttime=millis();
  while (millis()<displaystarttime+timedisplayed){
    lcd.setCursor(15,0);
    lcd.print(message);
    lcd.scrollDisplayLeft();
    delay(300);
  }
}

void changeKundBetal(char* id, char* betala){
    for (int i=0;i<sizeof(kundlist)/sizeof(KUND);i++){
    if (kundlist[i].id == atoi(id)){
      kundlist[i].betalat = atoi(betala);
      return;
    }
  }
}

void loop() {
//digitalWrite(bluePin, HIGH);
//  athinaBlinkMessage("hello world 1, IOT 20");
//  delay(3000);
//  athinaPrintMessage("hello world 2");
//  delay(3000);
//  athinaScrollMessage("hello world 3");
//  delay(3000);

  char inChar;
  char inData[30];
  int charIndex=0;
  while (Serial.available()) {
      if(charIndex < 29)
    {
      delay(2);  //delay to allow byte to arrive in input buffer
      inChar = Serial.read();
      inData[charIndex] = inChar;
      charIndex++;
      inData[charIndex] = '\0';
    } 
    lcd.clear();  
  }

    if (inData[0]=='s') {  //sänk -> s:1:1500:
      char* ptr = NULL;
      byte index = 0;
      char* kundid;
      char* betal;
      ptr = strtok(inData, ":");
      while (ptr != NULL)
      {
        if(index==1)
        {
          kundid=ptr;
        }
        if(index==2)
        {
          betal=ptr;
        }
        index++;
        ptr = strtok(NULL, ":");
      }

      changeKundBetal(kundid, betal);
      inData[0]='\0';
    }

    if (inData[0]=='a') {  //add reklam -> a:
        int summaAntalLotter = 0;
        for(int i = 0; i < sizeof(kundlist)/sizeof(KUND); i++){
          summaAntalLotter += kundlist[i].betalat;
        }
      if(millis()-starttime > timedisplayed){
      lcd.clear();
      starttime = millis();
      KUND found;
      while(true){
        int r = rand() % summaAntalLotter;
        found = checkoutKund(r);
        if(firstkund.id != found.id) break;     
      }
    
    int id = found.id;
    int msgNum = 1;
    int betalning = found.betalat;
    
    if(betalning >= 5000){
      msgNum = 3;
    }
    else{
      msgNum = 2;
    }
       
    switch(id){
      case 1:
        playAdHHB(msgNum);
        break;
      case 2:
        playAdFAP();
        break;
      case 3:
        playAdSPS();
        break;
      case 4:
        playAdLD();
        break;
      case 5:
        playIOT();
        break;
      case 6:
        playAdY();
        break;
    }
    firstkund = found;
    }  
      
      inData[0]='a';
  }
  if (inData[0]=='b'){ //b -> brand
    lcd.clear();
    String message= "BRANDLARM UTRYM SNARAST";
    displayMessage(message);    
    delay(300);
     tone(buzzer, 1000); // Send 1KHz sound signal...
    delay(1000);        // ...for 1 sec
    noTone(buzzer);     // Stop sound...
    delay(1000);        // ...for 1sec
  }
  
}
