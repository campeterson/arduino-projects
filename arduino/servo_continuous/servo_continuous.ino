#include <Servo.h>

// From https://www.arduino.cc/en/Reference/ServoWrite
// "On a continuous rotation servo, this will set the speed of the servo
// (with 0 being full-speed in one direction, 180 being full speed in the other,
// and a value near 90 being no movement)."

// Servo - FS90R (Continuous Servo)
// Wiring:
// Connect the servo red wire to the +5v pin (or use external power)
// Connect the servo brown or black wire to the ground pin
// Connect the servo orange or yellow wire to the digital pin

Servo myservo;

void setup()
{
  myservo.attach(9);
  myservo.write(90);  // set servo to mid-point
  // myservo.write(0);  // set servo to continuous
}

void loop() {}
