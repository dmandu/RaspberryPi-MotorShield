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
#define IRSENSORLEFT 23
#define IRSENSORMID 24
#define IRSENSORRIGHT 25
#define DISTANCESENSORTRIGGER 21
#define DISTANCESENSORECHO 22
#define OBSTACLESENSOR 7
/*
#define CE0 1
#define MISO 24
#define MOSI 28
#define SCLK 29
void InitSPI();
 */
void InitMotors();
void InitSensors();
void * LSICounter(void *);

_Bool Yes = TRUE;
_Bool isMoving = FALSE;
_Bool obstacle = FALSE;
_Bool isTrail = TRUE;

int speed = 0;

struct Motors motor1;
struct Motors motor2;
struct Motors motor3;
struct Motors motor4;
struct Motors allMotors;

struct MeasureDataArgs threadArgs;

pthread_t speedEncoderThread;
//pthread_t lsiThread;

int main() {
	wiringPiSetup();
	threadArgs.speedptr = &speed;
	threadArgs.movingptr = &isMoving;

   	InitSPI();
	InitMotors();
	InitSensors();
	SpeedEncoderInit(SPEEDENCODER1);

	struct Motors allMotors [] = {motor1, motor2, motor3, motor4};

	//int ret1 = pthread_create(&lsiThread, NULL, &LSICounter, NULL);
    Move(allMotors, 'F', 30, &isMoving);

    while(isTrail) {
		CheckEchoSensor();
		CheckIRSensors();
	}
    Stop(Yes, allMotors, *isMoving);
    printf("No trail to follow");
    return 1;
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


void CheckEchoSensor() {
    if(MeasureDistance() <= 20) {
        obstacle = TRUE;
        Stop(Yes, allMotors, &isMoving);
        sleep(3);
        if(MeasureDistance() <= 20) {
            while(digitalRead(OBSTACLESENSOR) == 1) {
                pthread_create(&speedEncoderThread, NULL, &SpeedEncoderRotations, &threadArgs);
                Move(allMotors, 'R', 30, &isMoving);
                pthread_join(speedEncoderThread);
            }
            Stop(Yes, allMotors, &isMoving);
            while(digitalRead(OBSTACLESENSOR) == 0) {
                Move(allMotors, 'F', 30, &isMoving);
            }
            Stop(Yes, allMotors, &isMoving);
            while(digitalRead(OBSTACLESENSOR) == 1) {
                pthread_create(&speedEncoderThread, NULL, &SpeedEncoderRotations, &threadArgs);
                Move(allMotors, 'L', 30, &isMoving);
                pthread_join(speedEncoderThread);
            }
            Stop(Yes, allMotors, &isMoving);
            while(digitalRead(OBSTACLESENSOR) == 0) {
                Move(allMotors, 'F', 30, &isMoving);
            }
            Stop(Yes, allMotors, &isMoving);
        }
    }
}


void CheckIRSensors() {
    int high = 0;
    int low = 1;
    if(digitalRead(IRSENSORLEFT) == high && digitalRead(IRSENSORMID) == low) {
        //steer to the right
        while(digitalRead(IRSENSORLEFT) == high && digitalRead(IRSENSORMID) == low) {
            SmoothLeft(allMotors, 50, *isMoving)
        }
        Move(allMotors, 'F', 30, *isMoving);
    }
    else if(digitalRead(IRSENSORRIGHT) == high && digitalRead(IRSENSORMID) == low) {
        //steer to the left
        while(digitalRead(IRSENSORRIGHT) == high && digitalRead(IRSENSORMID) == low) {
            SmoothRight(allMotors, 50, *isMoving)
        }
        Move(allMotors, 'F', 30, *isMoving);
    }
    else if(digitalRead(IRSENSORMID) == low && digitalRead(IRSENSORLEFT) == low && digitalRead(IRSENSORRIGHT) == low){
        isTrail = FALSE;
    }
}



/*
void InitSPI() {
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
		cycles = buffer[1];
		speed = 2*3.14*500000/(18*cycles);
		printf("SPI: Speed: %d\n", speed);
		sleep(2);
	}
}
*/