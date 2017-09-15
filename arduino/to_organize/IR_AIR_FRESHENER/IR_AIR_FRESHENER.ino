#include <SharpIR.h>

#define ir A0
#define model 20150

boolean done = false;

SharpIR sharp(ir, 25, 93, model);

// ir: the pin where your sensor is attached
// 25: the number of readings the library will make before calculating a mean distance
// 93: the difference between two consecutive measurements to be taken as valid
// model: an int that determines your sensor:  1080 for GP2Y0A21Y
//                                            20150 for GP2Y0A02Y
//                                            (working distance range according to the datasheets)

void setup() {
  Serial.begin(9600);
  pinMode(ir, INPUT);
  digitalWrite(2, LOW);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
}

void loop() {
  unsigned long pepe1=millis();  // takes the time before the loop on the library begins
  int dis=sharp.distance();      // this returns the distance to the object you're measuring

  Serial.print("Distance: ");    // returns it to the serial monitor
  Serial.println(dis);

  if (dis < 200) {
    // nothing
    Serial.println("Too Close");
  } else if (dis < 270) {
    Serial.println("Target found...");
    Serial.println("Fire!!!");
    digitalWrite(2, HIGH);
    Serial.println("Wait a second...");
    delay(1000);
    Serial.println("Turning Fire off.");
    digitalWrite(2, LOW);
    Serial.print("Waiting 10 seconds...");
    delay(10000);
  } else {
   // nothing
   Serial.println("Nothing in range...");
  }
  delay(500);
}


