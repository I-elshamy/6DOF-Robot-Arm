#include <ESP32Servo.h>

#define servo1_pin 13
#define servo2_pin 12
#define servo3_pin 14
#define servo4_pin 27
#define servo5_pin 26

Servo servo1;
  Servo servo2;
  Servo servo3;
  Servo servo4;
  Servo servo5;
void setup() {
  

  servo1.attach(servo1_pin);
  servo2.attach(servo2_pin);
  servo3.attach(servo3_pin);  
  servo4.attach(servo4_pin);
  servo5.attach(servo5_pin);
  delay(1000);
  // put your setup code here, to run once:

}

void loop() {
  servo1.write(0); //130 by2fel 0 byfta7 lel a5er
  servo2.write(0); //180 bynzel le ta7t 
  servo3.write(40); //angle a2al mn 90 bylegf ymeen  
  servo4.write(140); //angle so8ayar le odam angle kbeer le wara
  servo5.write(40); //angle so8ayar le wara 

  for (int i=20;i<=160 ;i++)
    {
      servo4.write(i);
      delay(50);
    }
    servo1.write(130);
  delay(500);
   for (int i=160;i>=20 ;i--)
    {
      servo4.write(i);
      delay(50);
    }
  servo1.write(0);
}
