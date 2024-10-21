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

const int LED_BUILTIN = 2;

void setup()
{
  Serial.begin(9600);
  delay(500);
  e220ttl.begin();

  pinMode(LED_BUILTIN, OUTPUT);

  configureLoRa(e220ttl, printParameters);
  // e220ttl.setMode(MODE_0_NORMAL);

  Serial.println("Hi, I'm going to send message!");
}
bool state = false;

void loop()
{
  state = !state;
  digitalWrite(LED_BUILTIN, state);
  // while (Serial.available() == 0)
  // {
  //   // Stop while you write message
  // }

  // String userInput = Serial.readStringUntil('\n');
  // Serial.println(userInput);
  ResponseStatus rs = e220ttl.sendMessage("Hello");
  Serial.println(rs.getResponseDescription());
  delay(500);
}
