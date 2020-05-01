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
#include "DistanceSensor.h"

#define SPEEDENCODER1 30
#define IRSENSORLEFT 27
#define IRSENSORRIGHT 21
#define IRSENSORMID 22
#define DISTANCESENSORTRIGGER 23
#define DISTANCESENSORECHO 7
#define OBSTACLESENSOR 25

#define CE0 1
#define MISO 24
#define MOSI 28
#define SCLK 29

void InitSPI();
void InitMotors();
void InitSensors();
void * LSICounter(void *);

struct Motors motor1;
struct Motors motor2;
struct Motors motor3;
struct Motors motor4;

int main() {
	wiringPiSetup();
	struct MeasureDataArgs threadArgs;

	_Bool Yes = TRUE;
	_Bool isMoving = FALSE;
	_Bool obstacle = FALSE;
	int speed = 0;

	pthread_t speedEncoderThread;
	pthread_t lsiThread;

	threadArgs.speedptr = &speed;
	threadArgs.movingptr = &isMoving;

   	InitSPI();
	InitMotors();
	InitSensors();
	SpeedEncoderInit(SPEEDENCODER1);

	struct Motors allMotors [] = {motor1, motor2, motor3, motor4};

	int ret1 = pthread_create(&lsiThread, NULL, &LSICounter, NULL);

	while(1) {
		Move(allMotors, 'F', 30, &isMoving);
		if(MeasureDistance() <= 100) {
			obstacle = TRUE;
			Stop(Yes, allMotors, &isMoving);
			sleep(3);
			if(MeasureDistance() <= 100) {
				while(digitalRead(OBSTACLESENSOR) == 1) {
					pthread_create(&speedEncoderThread, NULL, &SpeedEncoderRotations, &threadArgs);
					Move(allMotors, 'R', 30, &isMoving);
				}
				Stop(Yes, allMotors, &isMoving);
			}
			while(digitalRead(OBSTACLESENSOR) == 0) {
				Move(allMotors, 'F', 30, &isMoving);
			}
			Stop(Yes, allMotors, &isMoving);
			while(digitalRead(OBSTACLESENSOR) == 1) {
				Move(allMotors, 'L', 30, &isMoving);
			}
			Stop(Yes, allMotors, &isMoving);
		}

	}
	Stop(Yes, allMotors, &isMoving);
 	return 0;
}


void InitMotors() {
	Init(&motor1, 0, 3, 2);
	Init(&motor2, 6, 5, 4);
	Init(&motor3, 12, 14, 13);
	Init(&motor4, 26, 11, 10);
}

void InitSensors() {
	pinMode(IRSENSORLEFT, INPUT);
	pinMode(IRSENSORMID, INPUT);
	pinMode(IRSENSORRIGHT, INPUT);
	pinMode(OBSTACLESENSOR, INPUT);

	InitDistanceSensor(DISTANCESENSORTRIGGER, DISTANCESENSORECHO);
}










void InitSPI() {
	unsigned char buffer [] = {0x88, 0x00, 0x90};
	unsigned char *data = "10001000";
	unsigned char *data1 = "00000000";
	unsigned char *data2 = "10010000";
	pinModeAlt(29, 3);
	pinModeAlt(28, 3);
	pinModeAlt(24, 3);
	pinModeAlt(1, 3);

	wiringPiSPISetup(0, 500000);
	digitalWrite(CE0, LOW);
	wiringPiSPIDataRW(0, data, 8);
	wiringPiSPIDataRW(0, data1, 8);
	wiringPiSPIDataRW(0, data2, 8);
	wiringPiSPIDataRW(0, data1, 8);
	digitalWrite(CE0, HIGH);
}

void * LSICounter(void * args) {
	unsigned char buffer [2] = {0x60, 0};
	int speed = 0;
	int cycles = 0;
	while(1) {
		digitalWrite(CE0, LOW);
		wiringPiSPIDataRW(0, buffer, 2);
		digitalWrite(CE0, HIGH);
		printf("SPI: buffer afterRW: %d\n", buffer[1]);
		++cycles;
		speed = 2*3.14*500000/(18*cycles);
		sleep(2);
	}
}
