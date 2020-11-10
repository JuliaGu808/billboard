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

int timedisplayed = 6000;

struct KUND {
  int id;
  String namn;
  int betalat;
};

KUND kundlist[5];
KUND firstkund;

long day = 86400000; 
long hour = 3600000; 
long minute = 60000;
int startHour = 15;
int startMinute = 40;

int chooseAd = NULL;

//ADS

//Hederlige Harrys Bilar
//String HHB11 = "Kop bil";
//String HHB12 = "hos Harry";
String HHB1 = "Kop bil hos Harry";
String HHB2 = "En god bilaffar for harry!";
String HHB3 = "Hederlige Harrys bilar";

//Farmor ankas pajer AB
String FAP1 = "Kop paj hos Farmor Anka";
String FAP2 = "Skynda! Innan Marten atit alla pajer";

//Svarte Petters Svartbyggen
String SPS1 = "Lat Petter bygga at dig";
String SPS2 = "Bygga svart? Ring Petter";

//Långbens Detektivbyrå
String LD1 = "Mysterier? Ring Langben";
String LD2 = "Langben fixar biffen";

void setup() {
  lcd.begin(16, 2);
  createKundlist();
  firstkund.namn="test";
  firstkund.betalat = 0;
  firstkund.id = 0;
  
  
  

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

  kundlist[0] = harry;
  kundlist[1] = anka;
  kundlist[2] = peter;
  kundlist[3] = ben;
  kundlist[4] = iot;
}

KUND checkoutKund(int lotter){
  if(lotter >= 0 && lotter <= 5000){
    return kundlist[0];
  }
  else if(lotter >= 5001 && lotter <= 8001){
    return kundlist[1];
  }
  else if(lotter >= 8002 && lotter <= 9502){
    return kundlist[2];
  }
  else if(lotter >= 9503 && lotter <= 13503){
    return kundlist[3];
  }
  else{
    return kundlist[4];
  }
}

void playAdHHB()
{
  //lcd.print("hhb");
  chooseAd = randomize(3);
  if(chooseAd == 1) scrollMessage(HHB1);
  else if (chooseAd == 2) printMessage(HHB2);
  else if (chooseAd == 3) blinkMessage(HHB3);
}

void playAdFAP()
{
 
  //lcd.print("fap");
chooseAd = randomize(2);
if(chooseAd = 1) scrollMessage(FAP1);
else if (chooseAd = 2) printMessage(FAP2);
}

void playAdSPS()
{
  //lcd.print("sps");
  long currentMinute = currentMinuteApproximation();
  if (currentMinute % 2 == 0) scrollMessage(SPS1);
  else scrollMessage(SPS2);
}
void printMessage(String message){
   if (message.length()<17)
  lcd.print(message);
  else {
    if (message.substring(16)==" "){
    lcd.print(message);
    lcd.setCursor(0,1);
    lcd.print(message.substring(16));}
    else {
      int index=message.lastIndexOf(" ", 16);
      lcd.print(message.substring(0,index));
      lcd.setCursor(0, 1);
      lcd.print(message.substring(index+1));
    }
  }
}


void playAdLD()
{
 // lcd.print("dld");
  long currentHour = currentHourApproximation();
  if(currentHour >=6 && currentHour < 17) printMessage(LD2);
  else printMessage(LD1);
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

void scrollMessage(String msg)
 {

  lcd.setCursor(17, 0);
 lcd.print(msg);
 long displaystarttime=millis();
  for (int i = 0; i < 40; i++)
    {
      if(millis()>displaystarttime+timedisplayed){
       break; 
      }
      lcd.scrollDisplayLeft();
      delay(200);
    }
    lcd.clear(); 
 }
 

 void blinkMessage(String message){
  long displaystarttime=millis();
  while (millis()<displaystarttime+timedisplayed){
     printMessage(message);
  delay(750);
  lcd.clear();
  delay(500);
  
  }
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


void loop() {

//  athinaBlinkMessage("hello world 1, IOT 20");
//  delay(3000);
//  athinaPrintMessage("hello world 2");
//  delay(3000);
//  athinaScrollMessage("hello world 3");
//  delay(3000);
  
 int summaAntalLotter = 0;
  for(int i = 0; i < 5; i++){
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
    switch(id){
      case 1:
        playAdHHB();
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
    }
    firstkund = found;
    
  }
  
}
