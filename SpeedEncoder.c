#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>
#include <pthread.h>

#define PI 3.14

int pin;

void SpeedEncoderInit(int pinNum) {
	pin = pinNum;

	wiringPiSetup();
	pinMode(pinNum, INPUT);
}

void * SpeedEncoderMeasureData(void * args) {
	printf("This is the SpeedEncoderThread. Now reading data\n");
	int pulses = 0;
	int rotatioins = 0;
	int prevData = 0;
	int data;
	int * speed = (int *) args[0];
	bool * movingPtr = (bool *) args[1];
	while(movingPtr) {
		data = digitalRead(pin);
		printf("\nMeasured Data: %d\n", data);
		if(data != prevData) {
			prevData = data;
			++pulses;
			rotations = pulses/18;
			printf("\nPulses: %d  Rotations: %d\n", pulses, rotations);
		}
		++pulses;
        *speed = 2*PI*pulses/3*18;
		pthread_testcancel();
	}
}
