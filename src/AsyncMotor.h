//
// Created by noahb on 22.09.2022.
//
#include "Arduino.h"

#ifndef ROBALL_ASYNCMOTOR_H
#define ROBALL_ASYNCMOTOR_H


class AsyncMotor {
private:
    unsigned char enable;
    unsigned char control1;
    unsigned char control2;
public:
    AsyncMotor(unsigned char pinEnable, unsigned char pinControl1, unsigned char pinControl2){

    };
    void setSpeed(unsigned char speed);
    void setDirection(bool dir);
};


#endif //ROBALL_ASYNCMOTOR_H
