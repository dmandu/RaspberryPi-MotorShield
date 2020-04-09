//
// Created by d22ma on 4/9/2020.
//

#include <stdio.h>
#include <wiringPi.h>
#include <stdbool.h>

#ifndef ASSIGNMENT3_MOTORSHIELD_H
#define ASSIGNMENT3_MOTORSHIELD_H

struct Motors {
    int enablePin;
    int forwardPin;
    int reversePin;
};


void Init(struct Motors, int, int, int);

void Move(struct Motors, char);

void Stop(bool Yes);
#endif //ASSIGNMENT3_MOTORSHIELD_H
