#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

// WIFI
  const char* ssid = "XXXXXXXXXX";                             // paste SSID
  const char* password = "XXXXXXXXXXXX";                       // paste password

// telegram bot
#define BOTtoken "XXXXXXXXXXX:XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" // your token
#define CHAT_ID "XXXXXXX"                                      // telegram chat ID

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

const int gasSensor = A0;                                       // gas sensor
bool gasDetected = false;
int count = 3;                                                  // message
const int drop = 150;                                           // drop

void setup() {
  Serial.begin(115200);
  client.setInsecure();
  
  pinMode(gasSensor, INPUT_PULLUP);                             

  Serial.print("Connecting with Wifi: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  bot.sendMessage(CHAT_ID, "Bot <GAS> started", "");
}

void loop() {
  int sensorValue = analogRead(gasSensor);                                                // Read A0   
  if(gasDetected && count){
    bot.sendMessage(CHAT_ID, "GAS Leak Detected!!!", "");
    Serial.println("GAS Leak Detected");
    count -= 1;                                                                             // Уменьшаем счётчик на 1  
    delay(10000);                                                                           // pause 10s  
     
  }
     
  if (sensorValue > drop) {
    gasDetected = true;                                                                   // sensor 
  }
  else {
    gasDetected = false;                                                                  // sensor status
    count = 3;                                                                              // Number of messages again 3
  }
}