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
	while(1) {
		int data = digitalRead(pin);
		printf("Measured Data: %d\n", data);
		sleep(1);
		pthread_testcancel();
	}
}
