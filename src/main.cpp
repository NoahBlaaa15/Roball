//
// Created by noahb on 16.09.2022.
//
#include "Arduino.h"
#include "WiFi.h"
#include "WebSocketsServer.h"
#include "AsyncMotor.h"
#include "ArduinoOTA.h"

WebSocketsServer webSocketsServer = WebSocketsServer(81);
AsyncMotor motorL;
AsyncMotor motorR;

const u_int8_t speedR = 102;
const u_int8_t speedL = 110;

void webSocketCallback(uint8_t num, WStype_t type, uint8_t * payload, size_t length);

void setup() {
    Serial.begin(9600);

    WiFi.softAP("Roball", NULL);

    ArduinoOTA.onStart([]() {
        Serial.println("Start");
    });
    ArduinoOTA.onEnd([]() {
        Serial.println("\nEnd");
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    });
    ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
        else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
        else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
        else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
        else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });
    ArduinoOTA.begin();

    Serial.println("Opened Access-Point \"Roball\"");


    //delay(30000);
    motorL = AsyncMotor(14, 13, 12, 0);
    motorR = AsyncMotor(15, 16, 17, 1);

    motorL.setSpeed(60);
    motorL.setDirection(true);
    motorR.setSpeed(60);
    motorR.setDirection(true);

    Serial.println("Motor Test started");
    delay(1000);
    motorL.setSpeed(0);
    motorR.setSpeed(0);
    Serial.println("Motor Test finished");

    webSocketsServer.begin();
    webSocketsServer.onEvent(webSocketCallback);
    Serial.println("WebServer open at Gateway:81");


}

void loop() {
    //asm("nop");
    webSocketsServer.loop();
    ArduinoOTA.handle();
}

void webSocketCallback(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
    String text;
    IPAddress ip;
    String mlsT;
    String mrsT;
    int64_t dirType;
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
            Serial.printf("[%u] get Text: %s\n", num, text.c_str());

            dirType = text.toInt();
            switch (dirType) {
                case 0: //Break
                    motorL.setSpeed(0);
                    motorR.setSpeed(0);
                    break;
                case 1: //UP
                    motorL.setSpeed(speedL);
                    motorR.setSpeed(speedR);
                    motorR.setDirection(1);
                    motorL.setDirection(1);
                    break;
                case 2: //DOWN
                    motorL.setSpeed(speedL);
                    motorR.setSpeed(speedR);
                    motorR.setDirection(0);
                    motorL.setDirection(0);
                    break;
                case 3: //RIGHT
                    motorL.setSpeed(speedL);
                    motorR.setSpeed(speedR);
                    motorR.setDirection(0);
                    motorL.setDirection(1);
                    break;
                case 4: //LEFT
                    motorL.setSpeed(speedL);
                    motorR.setSpeed(speedR);
                    motorR.setDirection(1);
                    motorL.setDirection(0);
                    break;

            }
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
        case WStype_PING:
        case WStype_PONG:
        default:
            break;
    }

}