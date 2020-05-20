#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>
#include <pthread.h>
#include <stdbool.h>
#include "SpeedEncoder.h"

#define PI 3.14

int pin;

void SpeedEncoderInit(int pinNum) {
	pin = pinNum;

	wiringPiSetup();
	pinMode(pinNum, INPUT);
}

void * SpeedEncoderRotations(void * args) {
	struct MeasureDataArgs * argptr = (struct MeasureDataArgs *) args;
	int pulses = 0;
	int rotations = 0;
	int dataHigh = 1;
	int data;
	int * speed =argptr->speedptr;
	_Bool * moving = argptr->movingptr;
	while(rotations != 10) {
	    data = digitalRead(pin);
	    if(data == dataHigh) {
            while (data != dataHigh) {
                data = digitalRead(pin);
            }
            ++pulses;
            rotations = pulses / 20;
        }
	}
	return NULL;
}
