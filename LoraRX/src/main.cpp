#include "Arduino.h"
#include "LoRa_E220.h"
#include "E220_My_Settings.h"

HardwareSerial mySerial(2);

const int TX_PIN = 17;
const int RX_PIN = 16;
const int AUX_PIN = 18;
const int M0_PIN = 19;
const int M1_PIN = 21;

LoRa_E220 e220ttl(&mySerial, AUX_PIN, M0_PIN, M1_PIN, UART_BPS_RATE_9600);

#define ENABLE_RSSI true
// #define DESTINATION_ADDL 2

void printParameters(struct Configuration configuration);
void printModuleInformation(struct ModuleInformation moduleInformation);

const int LED_BUILTIN = 2;

void setup()
{
  Serial.begin(9600);
  delay(500);
  e220ttl.begin();

  pinMode(LED_BUILTIN, OUTPUT);

  configureLoRa(e220ttl, printParameters);
  // e220ttl.setMode(MODE_0_NORMAL);

  Serial.println("Hi, I'm going to receive message!");
}
bool state = false;
void loop()
{
  if (e220ttl.available() > 1)
  {
    state = !state;
    digitalWrite(LED_BUILTIN, state);
    ResponseContainer rs = e220ttl.receiveMessage();
    String message = rs.data; // First ever get the data
    Serial.println("reveive message");
    // print status
    Serial.println(rs.status.getResponseDescription());
    Serial.println(message);
  }
}
