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

#define joystickPinX A0 // Joystick X pin connected to A0
#define joystickPinY A1 // Joystick Y pin connected to A1
#define joySwitch 4 // Joystick switch connected to Digital Pin 4

Servo leftServo;
Servo rightServo;

int leftServoPin = 7;
int rightServoPin = 8;
float conversionValue = 0.17595; // The value to convert from the analog signal

// variables will change:
int joystickX = 0;
int joystickY = 0;
float convertedX = 0;
float convertedY = 0;

void setup() {
  pinMode(joySwitch, INPUT_PULLUP);
  Serial.begin(9600);
  
  leftServo.attach(leftServoPin);
  leftServo.write(90);
  rightServo.attach(rightServoPin);
  rightServo.write(90);
}

void loop() {
  joystickX = analogRead(joystickPinX);
  joystickY = analogRead(joystickPinY);

  convertedX = convertLeft(joystickX);
  convertedY = convertRight(joystickY);
  
  if (!digitalRead(joySwitch)) { // If Joystick switch is clicked re-center all Servos
    leftServo.write(90);
    rightServo.write(90);
    Serial.println("Switch pushed");
    delay(500); // delay for debouncing the joystick switch
  }

  Serial.print("X - ");
  Serial.println(joystickX);
  Serial.print("Y - ");
  Serial.println(joystickY);

  if (joystickX < 490) {
    leftServo.write(convertedX);
  } else if (joystickX > 520) {
    leftServo.write(convertedX);
  } else {
    leftServo.write(90);
  }
  if (joystickY < 490) {
    rightServo.write(convertedY);
  } else if (joystickY > 520) {
    rightServo.write(convertedY);
  } else {
    rightServo.write(90);
  }

  delay(100);

}

int convertRight(int a) {
  return a * 0.17595;
}

int convertLeft(int a) {
  return 180 - (a * 0.17595);
}

