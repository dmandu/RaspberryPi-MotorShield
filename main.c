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
#include "MotorShield.h"
#include "SpeedEncoder.h"

#define SPEEDENCODER 21

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

	threadArgs.speedptr = &speed;
	threadArgs.movingptr = &isMoving;

	printf("MAIN: threadArgs.speedptr %d, threadArgs.movingptr %d\n MAIN: &threadArgs = %d\n", *threadArgs.speedptr, *threadArgs.movingptr, threadArgs);
	/***************************************************
	//These ints are the number of the wiringPi library pins
	//they correspond to pins 11, 15, and 13 on the actual Pi
	//I chose these because in the motor shield pdf on iLearn
	//in the pin description section it has these pins for Motor1
	****************************************************/
   	Init(&motor1, 0, 3, 2);
	Init(&motor2, 6, 5, 4);
	Init(&motor3, 12, 14, 13);
	Init(&motor4, 26, 11, 10);
	SpeedEncoderInit(SPEEDENCODER);

	struct Motors allMotors [] = {motor1, motor2, motor3, motor4};

	printf("MAIN: Speed before thread: %d\n", speed);
	int ret = pthread_create(&speedEncoderThread, NULL, &SpeedEncoderMeasureData, &threadArgs);
	if(ret == 0) {
		printf("Thread created successfully\n");
	}
	else {
		printf("Error creating thread\n");
	}
	printf("Continuing main.c\n");
	Move(allMotors, 'L', 30, &isMoving);
	printf("MAIN: Speed while thread is running: %d\n", speed);
	printf("MAIN: isMoving = %d\n", *threadArgs.movingptr);
	sleep(3);
	Stop(Yes, allMotors, &isMoving);
	sleep(3);
	printf("MAIN: Speed after finished: %d\n", speed);
	printf("MAIN: isMoving = %d\n", isMoving);
 	return 0;
}
