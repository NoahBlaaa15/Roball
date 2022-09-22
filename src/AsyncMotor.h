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
public:
    AsyncMotor(uint8_t pinEnable, uint8_t pinControl1, uint8_t pinControl2) {
        pinMode(pinEnable, OUTPUT);
        ledcSetup(0, 5000, 8);
        ledcAttachPin(pinEnable, 0);
        enable = pinEnable;

        pinMode(pinControl1, OUTPUT);
        control1 = pinControl1;

        pinMode(pinControl2, OUTPUT);
        control2 = pinControl2;
    };
    void setSpeed(uint8_t speed);
    void setDirection(boolean dir);
};


#endif //ROBALL_ASYNCMOTOR_H
