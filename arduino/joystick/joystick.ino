#define joyX A0 // Joystick X pin connected to A0 on the UNO
#define joyY A1 // Joystick Y pin connected to A1 on the UNO
#define joySwitch 4 // Joystick switch connected to Pin 4 on UNO

void setup() {
  pinMode(joySwitch, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {

  if (!digitalRead(joySwitch)) { // If Joystick switch is clicked re-center all Servos
    delay(1000); // delay for debouncing the joystick switch
    Serial.println("Switch pushed");
  }

  if (

  Serial.print("X - ");
  Serial.println(analogRead(joyX));
  Serial.print("Y - ");
  Serial.println(analogRead(joyY));
  delay(1000);

}
