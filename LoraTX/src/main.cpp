#include "Arduino.h"
#include "LoRa_E220.h"
#include "E220_My_Settings.h"

#include <WiFi.h>
#include <WebServer.h>
#include <FS.h>
#include <SPIFFS.h>

WebServer server(80);

const char *ssid = "ESP32-Access-Point";
const char *password = "12345678";

void handleRoot()
{
  File file = SPIFFS.open("/index.html", "r");
  if (!file)
  {
    Serial.println("Failed to open file");
    server.send(500, "text/plain", "Failed to load the page.");
    return;
  }
  server.streamFile(file, "text/html");
  file.close();
}

// Обробка запитів для CSS
void handleCSS()
{
  File file = SPIFFS.open("/style.css", "r");
  if (!file)
  {
    Serial.println("Failed to open CSS file");
    server.send(500, "text/plain", "Failed to load the CSS file.");
    return;
  }
  server.streamFile(file, "text/css");
  file.close();
}

// Обробка запитів для JS
void handleJS()
{
  File file = SPIFFS.open("/script.js", "r");
  if (!file)
  {
    Serial.println("Failed to open JS file");
    server.send(500, "text/plain", "Failed to load the JS file.");
    return;
  }
  server.streamFile(file, "application/javascript");
  file.close();
}

void handleFormSubmission()
{
  String inputData1 = server.arg("inputData1");
  String inputData2 = server.arg("inputData2");

  Serial.println("Data 1 received: " + inputData1);
  Serial.println("Data 2 received: " + inputData2);

  String response = "Data received:\n";
  response += "Input 1: " + inputData1 + "\n";
  response += "Input 2: " + inputData2 + "\n";

  server.send(200, "text/plain", response);
}

void initSPIFFS()
{
  if (!SPIFFS.begin(true))
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  Serial.println("SPIFFS mounted successfully");
}

//
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

  initSPIFFS();

  WiFi.softAP(ssid, password);

  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/style.css", handleCSS);
  server.on("/script.js", handleJS);
  server.on("/submit", HTTP_POST, handleFormSubmission);

  server.begin();
  Serial.println("HTTP server started");
}
bool state = false;

void loop()
{
  server.handleClient();
  // state = !state;
  // digitalWrite(LED_BUILTIN, state);
  // ResponseStatus rs = e220ttl.sendMessage("Hello");
  // Serial.println(rs.getResponseDescription());
  // delay(500);
}
