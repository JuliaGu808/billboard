long day = 86400000; 
long hour = 3600000; 
long minute = 60000;
int startHour = 0;
int startMinute = 0;

int chooseAd = NULL;

//ADS

//Hederlige Harrys Bilar
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
  
}

void loop() {

}

void playAdHHB()
{
  chooseAd = randomize(3);
  if(chooseAd == 1) scrollMessage(HHB1);
  else if (chooseAd == 2) printMessage(HHB2);
  else if (chooseAd == 3) blinkMessage(HHB3);
}

void playAdFAP()
{
chooseAd = randomize(2);
if(chooseAd = 1) scrollMessage(FAP1);
else if (chooseAd = 2) printMessage(FAP2);
}

void playAdSPS()
{
  currentMinute = currentMinuteApproximation()
  if (currentminute % 2 == 0) scrollMessage(SPS1);
  else scrollMessage(SPS2);
}

void playAdLD()
{
  currentHour = currentHourApproximation()
  if(currenthour >=6 && currentHour < 17) printMessage(LD1);
  else printMessage(LD2);
}



int currentHourApproximation()
{
  int millisecondsElapsedToday = startHour * hour + startMinute * minute + millis();
  int hours = (millisecondsElapsedToday % day) / hour;
  return hours;
}

int currentMinuteApproximation()
{
  int millisecondsElapsedToday = startHour * hour + startMinute * minute + millis();
  int minutes = ((millisecondsElapsedToday % day) % hour) / minute;
  return minutes;
}

int randomize(int range)
{
  r = rand() % range;
  return r+1;
}
