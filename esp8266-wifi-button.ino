/**
 * Autor: Matthias Lohr <matthias@lohr.me>
 */
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include "settings.h"

ESP8266WiFiMulti WiFiMulti;

const int  buttonPin = 2;

int lastButtonState = 0;
int currentButtonState = 0;

void sendRequest() {
  HTTPClient http;
  http.begin(WIFI_BUTTON_URL);
  http.GET();
  http.end();
}

void setup() {
  Serial.begin(115200);
  Serial.print("Starting...\n");
  pinMode(buttonPin, INPUT_PULLUP);
  WiFiMulti.addAP(WIFI_BUTTON_SSID, WIFI_BUTTON_KEY);
  Serial.print("Waiting for AP connection\n");
}

void loop() {
  if((WiFiMulti.run() == WL_CONNECTED)) {
    currentButtonState = digitalRead(buttonPin);
    if (currentButtonState == LOW && lastButtonState == HIGH) {
      sendRequest();
    }
    lastButtonState = currentButtonState;
    yield();
    delay(10);
  }
  else {
    delay(250);
  }
}


