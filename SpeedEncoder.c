#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>
#include <pthread.h>

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
	while(1) {
		data = digitalRead(pin);
		printf("\nMeasured Data: %d\n", data);
		if(data != prevData) {
			prevData = data;
			++pulses;
			rotations = pulses/18;
			printf("\nPulses: %d  Rotations: %d\n", pulses, rotations);
		}
		pthread_testcancel();
	}
}
