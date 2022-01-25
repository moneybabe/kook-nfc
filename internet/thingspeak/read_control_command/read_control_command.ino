#include <ESP8266WiFi.h>;
#include <WiFiClient.h>;
#include <ThingSpeak.h>;

const char* ssid = "test";
const char* password = "abcd1234";
 
int lockcommand = D1;

WiFiClient client;

unsigned long myChannelNumber = 1615491; //Your Channel Number (Without Brackets)
const char * myReadAPIKey = "43Z5H63DKQJOBH42"; //Your Write API Key

void setup() {
  Serial.begin(9600);
  delay(10);
 
  pinMode(lockcommand, OUTPUT);
  digitalWrite(lockcommand, HIGH);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Connect to ThingSpeak server
  ThingSpeak.begin(client);
 
}

// Get command from ThingSpeak
int value = 0;
void loop() {
  value = ThingSpeak.readIntField(myChannelNumber, 1, myReadAPIKey);
  // Serial.println(value);
  if (value == 1) {
    digitalWrite(lockcommand, LOW);
    delay(50);
    digitalWrite(lockcommand, HIGH); 
    while (value == 1) {
      value = ThingSpeak.readIntField(myChannelNumber, 1, myReadAPIKey);
      // Serial.println(value);
    }
  } 
  // Serial.println(ThingSpeak.readIntField(myChannelNumber, 1, myReadAPIKey));
}
