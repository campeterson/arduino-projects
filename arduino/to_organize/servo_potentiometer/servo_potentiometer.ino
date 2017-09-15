#include <Servo.h>

Servo myservo; //create servo object to control a servo

int potpin = 0; // analog pin used to connect the potentiometer
int val;        // variable to read the value from the analog pin

void setup() {
  myservo.attach(9);
}

void loop() {
  val = analogRead(potpin);         // reads tge vakye if the potentiometer (values between 0 and 1023)
  val = map(val, 0, 1023, 0, 179);  // scale it to use it with the servo (values between 0 and 180)

  myservo.write(val);         // sets the servo position according to the scaled value
  delay(15);                  // waits for the servo to get there
}
