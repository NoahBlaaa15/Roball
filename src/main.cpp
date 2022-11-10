//
// Created by noahb on 16.09.2022.
//
#include "Arduino.h"
#include "WiFi.h"
#include "WebSocketsServer.h"
#include "AsyncMotor.h"

WebSocketsServer webSocketsServer = WebSocketsServer(81);
AsyncMotor motor1;
AsyncMotor motor2;

void webSocketCallback(uint8_t num, WStype_t type, uint8_t * payload, size_t length);

void setup() {
    Serial.begin(9600);

    WiFi.mode(WIFI_MODE_STA);
    WiFi.begin("Roball");

    Serial.println("Opened Access-Point \"Roball\"");

    motor1.setupMotor(12, 14, 15);
    motor2.setupMotor(16, 7, 8);

    motor1.setSpeed(120);
    motor1.setDirection(true);
    motor2.setSpeed(120);
    motor2.setDirection(true);

    pinMode(OUTPUT, 12);
    pinMode(OUTPUT, 14);
    pinMode(OUTPUT, 15);
    pinMode(OUTPUT, 16);
    pinMode(OUTPUT, 7);
    pinMode(OUTPUT, 8);

    Serial.println("Motor Test started");
    delay(1250);
    Serial.println("Motor Test finished");

    webSocketsServer.begin();
    webSocketsServer.onEvent(webSocketCallback);
    Serial.println("WebServer open at Gateway:81");


}

void loop() {
    //asm("nop");
    webSocketsServer.loop();
}

void webSocketCallback(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
    char* text;
    IPAddress ip;
    switch(type) {
        case WStype_DISCONNECTED:
            Serial.printf("[%u] Disconnected!\n", num);
            break;
        case WStype_CONNECTED:
            ip = webSocketsServer.remoteIP(num);
            Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);

            // send message to client
            webSocketsServer.sendTXT(num, "Connected");
            break;
        case WStype_TEXT:
            text = reinterpret_cast<char *>(payload);
            Serial.printf("[%u] get Text: %s\n", num, text);
            // send message to client
            // webSocket.sendTXT(num, "message here");

            // send data to all connected clients
            // webSocket.broadcastTXT("message here");
            break;
        case WStype_BIN:
            Serial.printf("[%u] get binary length: %u\n", num, length);
            //hexdump(payload, length);

            // send message to client
            // webSocket.sendBIN(num, payload, length);
            break;
        case WStype_ERROR:
            Serial.println("Error!");
        case WStype_FRAGMENT_TEXT_START:
        case WStype_FRAGMENT_BIN_START:
        case WStype_FRAGMENT:
        case WStype_FRAGMENT_FIN:
            break;
    }

}