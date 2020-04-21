/**************************************************************
* Class: CSC-615-01 Spring 2020
* Name: David Mandujano
* Student ID: 911901177
* Project: Assignment3 - Motors
*
* File: main.c
*
* Description: This file tests our code from MotorShield.c and calls
*		the methods to run the motors on the Raspberry Pi
******************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include "MotorShield.h"
#include "SpeedEncoder.h"

#define SPEEDENCODER1 28

void InitSPI();
void * LSICounter(void *);

int main() {
	struct Motors motor1;
	struct Motors motor2;
	struct Motors motor3;
	struct Motors motor4;
	struct MeasureDataArgs threadArgs;

	_Bool Yes = TRUE;
	_Bool isMoving = FALSE;
	int speed = 0;
	pthread_t speedEncoderThread;
	pthread_t lsiThread;

	threadArgs.speedptr = &speed;
	threadArgs.movingptr = &isMoving;

   	InitSPI();
	Init(&motor1, 0, 3, 2);
	Init(&motor2, 6, 5, 4);
	Init(&motor3, 12, 14, 13);
	Init(&motor4, 26, 11, 10);
	SpeedEncoderInit(SPEEDENCODER1);

	struct Motors allMotors [] = {motor1, motor2, motor3, motor4};

	int ret = pthread_create(&speedEncoderThread, NULL, &SpeedEncoderMeasureData, &threadArgs);
	int ret1 = pthread_create(&lsiThread, NULL, &LSICounter, NULL);

	Move(allMotors, 'F', 30, &isMoving);
	sleep(3);
	Stop(Yes, allMotors, &isMoving);
 	return 0;
}

void InitSPI() {
	wiringPiSetup();
	wiringPiSPISetup(0, 500000);

	pinModeAlt(29, ALT4);
    pinModeAlt(28, ALT4);
    pinModeAlt(1, ALT4);
}

void * LSICounter(void * args) {
	unsigned char buffer [50];
	int speed = 0;
	int cycles = 0
	while(1) {
		wiringPiSPIDataRW(1, buffer, sizeof(buffer));
		printf("SPI: %s", *buffer);
		++cycles;
		speed = 2*3.14*500000/(18*cycles);
		printf("SPI: Speed: %d", speed);
	}
}
