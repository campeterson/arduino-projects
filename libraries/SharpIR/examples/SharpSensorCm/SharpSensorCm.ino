#include <SharpIR.h>

#define ir A0
#define model 20150

boolean done=false;

SharpIR sharp(ir, 25, 93, model);

// ir: the pin where your sensor is attached
// 25: the number of readings the library will make before calculating a mean distance
// 93: the difference between two consecutive measurements to be taken as valid
// model: an int that determines your sensor:  1080 for GP2Y0A21Y
//                                            20150 for GP2Y0A02Y
//                                            (working distance range according to the datasheets)

int redPin = 11;
int greenPin = 10;
int bluePin = 9;

void setup() {
  Serial.begin(9600);
  pinMode (ir, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  unsigned long pepe1=millis();  // takes the time before the loop on the library begins
  int dis=sharp.distance();  // this returns the distance to the object you're measuring

  Serial.print("Distance: ");  // returns it to the serial monitor
  Serial.println(dis);

  if (dis < 49) {
    setColor(255, 0, 0);  // red  
  } else if (dis < 100) {
    setColor(0, 0, 255);  // blue  
  } else {
    setColor(0, 255, 0);  // green  
  }
  delay(50);
}

void setColor(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}
  

