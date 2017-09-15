int moisturePin = A0;
int moistureValue = 0;
int lightPin = A1;
int lightValue = 0;
int noisePin = A2;
int noiseValue = 0;
// int temperaturePin = A3;
// int temperatureValue = 0;

void setup() {
  // declare the ledPin as an OUTPUT:
   Serial.begin(9600);  
}

void loop() {
  moistureValue = analogRead(moisturePin);
  lightValue = analogRead(lightPin);
  noiseValue = analogRead(noisePin);
  // temperatureValue = analogRead(temperaturePin);

  delay(1000);
  Serial.print("moisture = " );
  Serial.println(moistureValue);
  Serial.print("light = " );
  Serial.println(lightValue);
  Serial.print("noise = " );
  Serial.println(noiseValue);
  // Serial.print("temperature = " );
  // Serial.println(temperatureValue);
}
