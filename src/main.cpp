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

    WiFi.softAP("Roball", NULL);

    Serial.println("Opened Access-Point \"Roball\"");


    //delay(30000);
    motor1 = AsyncMotor(14, 13, 12, 0);
    motor2 = AsyncMotor(15, 16, 17, 1);

    motor1.setSpeed(130);
    motor1.setDirection(true);
    motor2.setSpeed(130);
    motor2.setDirection(true);

    Serial.println("Motor Test started");
    delay(1000);
    motor1.setSpeed(0);
    motor2.setSpeed(0);
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
    int32_t speed;
    boolean dir;
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

            speed = atoi(text);
            dir = speed > 0;
            speed = abs(speed);

            motor1.setSpeed(map(speed, 0, 100, 0, 130));
            motor2.setSpeed(map(speed, 0, 100, 0, 130));

            motor1.setDirection(dir);
            motor2.setDirection(dir);
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