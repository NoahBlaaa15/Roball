//
// Created by noahb on 22.09.2022.
//
#include "Arduino.h"
#include "AsyncMotor.h"

/**
 * Sets the speed of the motor
 * @param speed Number between 0 and 255
 */
void AsyncMotor::setSpeed(uint8_t speed) {
    ledcWrite(0, speed);
}

/**
 * Sets the direction of the motor
 * @param dir true for forward; false for backwards
 */
void AsyncMotor::setDirection(boolean dir) {
    digitalWrite(control1, dir ? HIGH : LOW);
    digitalWrite(control2, dir ? LOW : HIGH);
}
