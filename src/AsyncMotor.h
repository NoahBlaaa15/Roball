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
    void setupMotor(uint8_t pinEnable, uint8_t pinControl1, uint8_t pinControl2) {
        ledcSetup(0, 5000, 8);
        ledcAttachPin(pinEnable, 0);
        enable = pinEnable;

        control1 = pinControl1;

        control2 = pinControl2;
    };
    AsyncMotor() {};
    void setSpeed(uint8_t speed);
    void setDirection(boolean dir);
};


#endif //ROBALL_ASYNCMOTOR_H
