//
// Created by noahb on 22.09.2022.
//
#include "Arduino.h"

#ifndef ROBALL_ASYNCMOTOR_H
#define ROBALL_ASYNCMOTOR_H


class AsyncMotor {
private:
    uint8_t enable;
    uint8_t control1;
    uint8_t control2;
    uint8_t channel;
public:
    AsyncMotor() {
        enable = -1;
        control1 = -1;
        control2 = -1;
        channel = -1;
    }
    AsyncMotor(uint8_t pinEnable, uint8_t pinControl1, uint8_t pinControl2, uint8_t chanNum) {
        pinMode(pinControl1, OUTPUT);
        control1 = pinControl1;

        pinMode(pinControl2, OUTPUT);
        control2 = pinControl2;

        enable = pinEnable;
        channel = chanNum;
        ledcSetup(channel, 1000, 8);
        ledcAttachPin(enable, channel);
    };
    void setSpeed(uint8_t speed);
    void setDirection(boolean dir);
};


#endif //ROBALL_ASYNCMOTOR_H
