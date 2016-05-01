//
//    FILE: main.ino
//  AUTHOR: Mo Team
// VERSION: 0.9.00 
// PURPOSE: Automatic Bartender Machine
//    DATE: 2016-04-30
//     URL: https://github.com/iH8uAll/M-Machine.git
//
// Released to the public domain
//

// TODO list
// - robustness
// - add libraries and headers
// - add functions
// - add screen and buttons for offline use

static char temp = 0; // temp char for serial comunication.
int i = 0,
    num = 0;            
long gotTime = 0;
const int mPINS[] = {13,12,11,10,9,8,7,6,5}; // available pumps pin
const char version[] = "0.9.00";

class initMotor // class for initialize a pump
{
  int motorPin;

public:
initMotor(int Mpin)
{
  motorPin = Mpin;
}
};
  
initMotor M1(mPINS[1]);
initMotor M2(mPINS[2]);
initMotor M3(mPINS[3]);
initMotor M4(mPINS[4]);

void initialDisplay(void); // display initial information
void Motor(long interval, int num, int gotTime); // enable the number of the motor for given interval
void Cocktail(int M1_sec, int M2_sec, int M3_sec, int M4_sec); // make a coctail giving the quantities in [ml] for any pump
int createQuantity(int quantity_ml); // conversion from [ml] to sec knowing [ml]/[sec] work time of a pump

void setup() {
  Serial.begin(9600); // start comunication
}

void loop() {
  if(Serial.available() > 0)
  {
    temp = Serial.read();
    if(temp == '1'){
    Cocktail(80,20,100,0); // make cocktail with given [ml]
    }
    else if (temp == '2'){
    Cocktail(80,80,40,0);
    }
    else if (temp == '3'){
    Cocktail(80,20,100,0); 
    }
    else if (temp == '4'){
    Cocktail(80,20,100,0);
    }
  }
}

void initialDisplay(void){
    Serial.print(F("\nMo Machine -  "));
    Serial.println(version);
}

void Motor(long interval, int num, int gotTime){
 
  unsigned long getTime = millis();
  
  if(getTime - gotTime > interval){
       digitalWrite(mPINS[num], HIGH);
       gotTime = getTime;
  }
  else {
        digitalWrite(mPINS[num], LOW);
       }
}

int createQuantity(int quantity_ml)
{
  int quantity = 60/100; //[sec]/[ml]
  quantity_ml *= quantity; //[ml] *= [sec]/[ml] = [sec]
  return quantity_ml;
} 

void Cocktail(int M1_ml, int M2_ml, int M3_ml, int M4_ml){
    Motor(createQuantity(M1_ml), 1, 0);
    Motor(createQuantity(M2_ml), 2, 0);
    Motor(createQuantity(M3_ml), 3, 0);
    Motor(createQuantity(M4_ml), 4, 0);
}
