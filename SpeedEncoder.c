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

void * SpeedEncoderMeasureData(void * args) {
	printf("This is the SpeedEncoderThread. Now reading data\n");
	struct MeasureDataArgs * argptr = (struct MeasureDataArgs *) args;
	int pulses = 0;
	int rotations = 0;
	int prevData = 0;
	int data;
	int * speed =argptr->speedptr;
	_Bool * moving = argptr->movingptr;
	*speed = 2*PI*pulses/(3*18);
	printf("THREAD: Speed: %d\n", *speed);
	while(*moving) {
//		printf("\nTHREAD: isMoving: %d\n", *moving);
		data = digitalRead(pin);
//		printf("THREAD: Measured Data: %d\n", data);
		if(data != prevData) {
			prevData = data;
			++pulses;
			rotations = pulses/18;
			printf("\nTHREAD: Pulses: %d  Rotations: %d\n", pulses, rotations);
		}
        	*speed = 2*PI*pulses/(3*18);
//		printf("THREAD: Speed: %d\n", *speed);
	}
	printf("THREAD: Wheels no longer moving, returning to main\n");
	return 0;
}
