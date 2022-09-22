//
// Created by noahb on 16.09.2022.
//
#include "Arduino.h"
#include "WiFi.h"
#include "WebSocketsServer.h"
#include "AsyncMotor.h"

WebSocketsServer webSocketsServer = WebSocketsServer(81);
AsyncMotor motor1 = AsyncMotor(12, 14, 15);
AsyncMotor motor2 = AsyncMotor(16, 7, 8);

void setup() {
    Serial.begin(9600);

    WiFi.mode(WIFI_MODE_AP);
    WiFi.begin("Roball");

    Serial.println("Opened Acces-Point \"Roball\"");

}

void loop() {
    asm("nop");
}