#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
char inData[30];
char inChar;
int charIndex;

struct KUND {
  String namn;
  int betalat;
};
KUND kundlist[4];

void setup() {
  lcd.begin(16, 2);
  createKundlist();
}

void createKundlist(){
   KUND harry;
  harry.namn = "Hederlige Harrys Bilar";
  harry.betalat = 5000; // 0-5000

  KUND anka;
  anka.namn = "Farmor Ankas Pajer AB";
  anka.betalat = 3000;  // 5001-8001

  KUND peter;
  peter.namn = "Svarte Petters Svartbyggen";
  peter.betalat = 1500; // 8002-9502

  KUND ben;
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

void loop() {
  int summaAntalLotter = 0;
  for(int i = 0; i < 4; i++){
    summaAntalLotter += kundlist[i].betalat;
  }
  int r = rand() % summaAntalLotter;
  KUND found = checkoutKund(r);
    lcd.print(found.namn);
    delay(3000);
    lcd.clear();
}
