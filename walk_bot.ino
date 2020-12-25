#include<Servo.h>
#include<Wire.h>
#include<LiquidCrystal_I2C.h>
#include <IRremote.h>

//Define hex numbers
#define B1 0x9716BE3F
#define B2 0x3D9AE3F7
#define B3 0x6182021B
#define B4 0x8C22657B
#define B5 0x488F3CBB

//custom bytes
byte heart[] = {
  B00000,
  B00000,
  B00000,
  B01010,
  B11111,
  B11111,
  B01110,
  B00100
};
const int ir = 13;
bool walk = false;
bool dance = false;
int x;
int y;

Servo servo1; //servo 1 is left close to conector servo 2 is right close to conector and servo 3 is opp of conector 
Servo servo2;
Servo servo3;
Servo servo4;

IRrecv irrecv(ir);
decode_results results;
uint32_t Previous;

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  lcd.clear();
  lcd.print("Hello");

  irrecv.enableIRIn();
    
  servo1.attach(9);
  servo2.attach(10);
  servo3.attach(11);
  servo4.attach(12);
  
  servo1.write(0);
  servo2.write(180);
  servo3.write(180);
  servo4.write(0);
  delay(2000);
  servo1.write(90);
  servo2.write(90);
  delay(20);
  servo3.write(90);
  servo4.write(90);
  delay(2000);
}

void loop() {
  //walk move
  //servo4.write(50);
  //servo2.write(90);
  //servo3.write(90);
  //servo1.write(130);
  //delay(500);
  //servo1.write(90);
  //servo3.write(130);
  //servo2.write(50);
  //servo4.write(90);
  //delay(500);
  //leap move
  //servo1.write(30);
  //servo2.write(150);
  //servo3.write(120);
  //servo4.write(50);
  //delay(500);
  //servo1.write(120);
  //servo2.write(70);
  //servo3.write(90);
  //servo4.write(80);
  //delay(500);

  if(irrecv.decode(&results))
  {Serial.println(results.value,HEX);
  irrecv.resume();
   if(results.value == 0xFFFFFFFF)
    {
      results.value=Previous;
    }
    if(results.value == B1)
    {
      lcd.clear();
      lcd.print("Hello My Name Is ");
      lcd.setCursor(0,1);
      lcd.print("Checo");
      servo1.write(30);
      servo2.write(150);
      servo3.write(90);
      servo4.write(90);
    }
    if(results.value == B2)
    {
      lcd.clear();
      lcd.print("     *    *     ");
      servo1.write(90);
      servo2.write(90);
      delay(20);
      servo3.write(90);
      servo4.write(90);
      walk = !walk;
      x=0;
    }
   if(results.value == B3)
    {
      lcd.clear();
      lcd.print("Heres A Little ");
      lcd.setCursor(0,1);
      lcd.print("Dance For You");
      servo1.write(90);
      servo2.write(90);
      delay(20);
      servo3.write(90);
      servo4.write(90);
      y=0;
      dance = !dance;
      delay(2000);
    }
    if(results.value == B4)
    {
      lcd.clear();
      lcd.print("Want To Shake");
      lcd.setCursor(0,1);
      lcd.print("Hands With Me?");
      servo1.write(90);
      servo2.write(140);
      delay(20);
      servo3.write(90);
      servo4.write(90);
    }
    if(results.value == B5)
    {
      lcd.clear();
      lcd.createChar(1,heart);
      lcd.print("     *    *     ");
      lcd.setCursor(0,1);
      lcd.print("   I ");
      lcd.write(1);
      lcd.print(" You!!!");
    }
    while(dance == true && y < 20)
      {
        servo2.write(150);
        delay(20);
        servo1.write(30);
        servo3.write(150);
        servo4.write(30);
        delay(100);
        servo2.write(70);
        delay(20);
        servo1.write(110);
        servo3.write(90);
        servo4.write(90);
        delay(100);
        y += 1;
      }
    while(walk == true && x < 10)
      {
        servo2.write(150);
        delay(20);
        servo1.write(30);
        servo3.write(150);
        servo4.write(30);
        delay(500);
        servo2.write(70);
        delay(20);
        servo1.write(110);
        servo3.write(90);
        servo4.write(90);
        delay(500);
        x += 1;
      }
  }
}
