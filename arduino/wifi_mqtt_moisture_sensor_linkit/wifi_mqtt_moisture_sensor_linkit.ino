#include <string>
#include <sstream>
#include <LTask.h>
#include <LWiFi.h>
#include <LWiFiClient.h>
#include <PubSubClient.h> // http://pubsubclient.knolleary.net/api.html
#include <Wire.h>
#include <Adafruit_BMP085.h>

#define WIFI_AP "PetersonData"
#define WIFI_PASSWORD "gonorthorwest!!"
#define WIFI_AUTH LWIFI_WPA  // choose from LWIFI_OPEN, LWIFI_WPA, or LWIFI_WEP.

int moisturePin = A0;
int moistureValue = 0;
int lightPin = A1;
int lightValue = 0;
char message_buff[100];
Adafruit_BMP085 bmp;
LWiFiClient c;
PubSubClient client("192.168.0.101", 1883, callback, c);

void setup() {
  pinMode(13, OUTPUT);
  pinMode(3, OUTPUT);
  LWiFi.begin();
  Serial.begin(115200);

  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP085 sensor, check wiring!");
    while (1) {}
  }

  // keep retrying until connected to Network
  Serial.println("Connecting to Network");
  while (0 == LWiFi.connect(WIFI_AP, LWiFiLoginInfo(WIFI_AUTH, WIFI_PASSWORD))) {
    Serial.println("Still trying to connect...");
    delay(5000);
  }

  // if (client.connect("openwest-remote-farm-controller", "arduino", "b2cfa4183267af678ea06c7407d4d6d8")) {
  if (client.connect("openwest-remote-farm-controller")) {
    client.publish("openwest/arduinos/1/status", "Hello OpenWest (from LinkitONE)!");
    client.subscribe("remote_farm/controllers/1/commands");
    digitalWrite(13, LOW);
    delay(100);
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(100);
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(100);
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(100);
    digitalWrite(13, HIGH);
    delay(100);
  }
}

void loop() {
//  Serial.print("MQTT Client State");
//  Serial.println(client.state());

  // Reconnect if not connected
  if (0 == client.connected()) {
    
    Serial.println("Trying to connect again");
    client.connect("openwest-remote-farm-controller");
    client.subscribe("remote_farm/controllers/1/commands");
    delay(1000);
    
  } else {
    
    moistureValue = analogRead(moisturePin);
    lightValue = analogRead(lightPin);
    float temp = bmp.readTemperature();
    
    std::stringstream ss;
    ss << "readings,loc=remote_farm,device_id=1 ";
    ss << "moist=" << moistureValue;
    ss << ",temp=" << (temp * 9.0 / 5.0 + 32.0);
    ss << ",light=" << lightValue;
    ss << ",status=" << 1;
    // ss << ",pressure(Pa)=" << bmp.readPressure();
    //  ss << ",altitude(M)=" << bmp.readAltitude();
    //  ss << ",pressureSeaLevel(Pa)=" << bmp.readSealevelPressure();
  
    if (client.publish("remote_farm/controllers/1/measurements", ss.str().c_str())) {
      Serial.println(ss.str().c_str());
    } else {
      Serial.println("Failed to publish.");
    }
    
    delay(1000);
  
    client.loop();
  }
}

// Callback function
void callback(char* topic, byte* payload, unsigned int length) {
  int p = 0;
  // create character buffer with ending null terminator (string)
  for (p = 0; p < length; p++) {
    message_buff[p] = payload[p];
  }
  message_buff[p] = '\0';
  String msgString = String(message_buff);

  Serial.println("Message arrived:  topic: " + String(topic));
  Serial.println("Length: " + String(length, DEC));
  Serial.println("Message: " + msgString);

  char ledTopic[100];
  strcpy(ledTopic, topic);

  if (String(ledTopic) == "remote_farm/controllers/1/commands/power") {
    if (msgString == "ON") {
      digitalWrite(13, HIGH);
      digitalWrite(3, HIGH);
      client.publish("remote_farm/controllers/1/messages", "Turning ON Power");
    } else if (msgString == "OFF") {
      digitalWrite(13, LOW);
      digitalWrite(3, LOW);
      client.publish("remote_farm/controllers/1/messages", "Turning OFF Power");
    } else {
      Serial.println("msgString not matching");
      delay(1000);
    }
  } else {
    Serial.print("No Match|");
    Serial.print(topic);
    Serial.print("|\n");
  }
}
