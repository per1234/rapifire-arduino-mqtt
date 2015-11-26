#include <YunClient.h>
#include <PubSubClient.h>
#include <RapifireMqtt.h>

#define THING_ID "YOUR_THING_ID"
#define THING_KEY "YOUR_THING_KEY"
#define DATA_TOPIC "YOUR_DATA_TOPIC"
#define COMMANDS_TOPIC "YOUR_COMMANDS_TOPIC"

YunClient client;

void callback(char* topic, uint8_t* bytes, unsigned int length)
{
  for (int i = 0; i < length; i++) {
    Serial.print((char)bytes[i]);
  }

  Serial.println();
}

RapifireMqtt rapifire(THING_ID, THING_KEY, DATA_TOPIC, COMMANDS_TOPIC, callback, client);

void setup() {
  Serial.begin(9600);

  Serial.println(F("Starting bridge..."));
  Bridge.begin();

  Serial.println(F("Bridge ready."));
}

void loop() {
  if (!rapifire.connected()) {
    Serial.println(F("Connecting to RAPIFIRE.."));

    if (rapifire.connect()) {
      Serial.println(F("Connected."));
    }
  }

  rapifire.loop();
}
