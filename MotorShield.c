//
// Created by d22ma on 4/9/2020.
//

#include <stdio.h>
#include <wiringPi.h>
#include <stdbool.h>

struct Motors {
    int enablePin;
    int forwardPin;
    int reversePin;
};

void Init(struct Motors motor, int enable, int forward, int reverse) {
    wiringPiSetup();
    motor.enablePin = enable;
    motor.forwardPin = forward;
    motor.reversePin = reverse;

    pinMode(motor.enablePin, OUTPUT);
    pinMode(motor.forwardPin, OUTPUT);
    pinMode(motor.reversePin, OUTPUT);

    digitalWrite(motor.enablePin, HIGH);
    digitalWrite(motor.forwardPin, LOW);
    digitalWrite(motor.reversePin, LOW);
}

void Move(struct Motors motor, char direction) {
    if(direction == 'R') {
        digitalWrite(motor.forwardPin, LOW);
        digitalWrite(motor.reversePin, HIGH);
    }
    else {
        digitalWrite(motor.forwardPin, HIGH);
        digitalWrite(motor.reversePin, LOW);
    }
}