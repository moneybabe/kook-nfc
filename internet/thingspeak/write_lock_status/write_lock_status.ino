#include <ESP8266WiFi.h>;
#include <WiFiClient.h>;
#include <ThingSpeak.h>;

const char* ssid = "test";   // Your Network SSID
const char* password = "abcd1234";       // Your Network Password

int lockstatus = D1;

WiFiClient client;

unsigned long myChannelNumber = 1615491; //Your Channel Number (Without Brackets)
const char * myWriteAPIKey = "EGNJOD979Y60A92S"; //Your Write API Key

void setup() {
  Serial.begin(9600);
  delay(10);
  pinMode(lockstatus, INPUT_PULLUP);
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  // Waiting for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  // WiFi connected
  Serial.println("");
  Serial.println("WiFi connected");
  ThingSpeak.begin(client);
}

// Push lock status to ThingSpeak
int value = 1;
void loop() {
  if (value != digitalRead(lockstatus)) {
    value = digitalRead(lockstatus);
    ThingSpeak.writeField(myChannelNumber, 2, digitalRead(lockstatus), myWriteAPIKey); //Update in ThingSpeak
  }
  delay(10);
}
