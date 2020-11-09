#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
char inData[30];
char inChar;
int charIndex;
long starttime = 0;
int first = 0;

int timedisplayed = 3000;

struct KUND {
  int id;
  String namn;
  int betalat;
};

KUND kundlist[4];
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

  kundlist[0] = harry;
  kundlist[1] = anka;
  kundlist[2] = peter;
  kundlist[3] = ben;
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
  else{
    return kundlist[3];
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


void loop() {
  
 int summaAntalLotter = 0;
  for(int i = 0; i < 4; i++){
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
    }
    firstkund = found;
    
  }
  
}
