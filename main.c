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
#include <stdlib.h>
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
void CheckIRSensors(struct Motors []);
void CheckEchoSensor(struct Motors []);
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

struct MeasureDataArgs threadArgs;

pthread_t speedEncoderThread;
//pthread_t lsiThread;

int main() {
	wiringPiSetup();
	threadArgs.speedptr = &speed;
	threadArgs.movingptr = &isMoving;

//   	InitSPI();
	InitMotors();
	InitSensors();
	SpeedEncoderInit(SPEEDENCODER1);

	struct Motors allMotors [] = {motor1, motor2, motor3, motor4};

	//int ret1 = pthread_create(&lsiThread, NULL, &LSICounter, NULL);
    	Move(allMotors, 'F', 1, &isMoving);
   	while(isTrail) {
		CheckEchoSensor(allMotors);
		CheckIRSensors(allMotors);
	}
//	sleep(5);
	Stop(Yes, allMotors,&isMoving);
    	printf("No trail to follow");
    	return 1;
}









void InitMotors() {
	Init(&motor1, 0, 2, 3);
	Init(&motor2, 6, 4, 5);
	Init(&motor3, 12, 13, 14);
	Init(&motor4, 26, 11, 10);
}


void InitSensors() {
	pinMode(IRSENSORLEFT, INPUT);
	pinMode(IRSENSORMID, INPUT);
	pinMode(IRSENSORRIGHT, INPUT);
	pinMode(OBSTACLESENSOR, INPUT);

	InitDistanceSensor(DISTANCESENSORTRIGGER, DISTANCESENSORECHO);
}


void CheckEchoSensor(struct Motors allMotors []) {
    printf("measuring distance\n");
    if(MeasureDistance() <= 10.0) {
	printf("POTENTIAL OBSTACLE\n");
        obstacle = TRUE;
        Stop(Yes, allMotors, &isMoving);
        sleep(3);
        if(MeasureDistance() <= 10.0) {
	    printf("Obstacle still there\n");/*
            while(digitalRead(OBSTACLESENSOR) == 1) {
                pthread_create(&speedEncoderThread, NULL, &SpeedEncoderRotations, &threadArgs);
                Move(allMotors, 'R', 20, &isMoving);
                pthread_join(speedEncoderThread, NULL);
            }
            Stop(Yes, allMotors, &isMoving);
            while(digitalRead(OBSTACLESENSOR) == 0) {
                Move(allMotors, 'F', 20, &isMoving);
            }
            Stop(Yes, allMotors, &isMoving);
            while(digitalRead(OBSTACLESENSOR) == 1) {
                pthread_create(&speedEncoderThread, NULL, &SpeedEncoderRotations, &threadArgs);
                Move(allMotors, 'L', 20, &isMoving);
                pthread_join(speedEncoderThread, NULL);
            }
            Stop(Yes, allMotors, &isMoving);
            while(digitalRead(OBSTACLESENSOR) == 0) {
                Move(allMotors, 'F', 20, &isMoving);
            }
            Stop(Yes, allMotors, &isMoving);
	*/
        }
    }
}


void CheckIRSensors(struct Motors allMotors []) {
    int high = 1;
    int low = 0;
    printf("Checking IR");
    if(digitalRead(IRSENSORLEFT) == low && digitalRead(IRSENSORMID) == high && digitalRead(IRSENSORRIGHT) == low) {
	printf("Moving foward\n");
//	Move(allMotors, 'F', 20, &isMoving);
    }
    else if(digitalRead(IRSENSORLEFT) == high && digitalRead(IRSENSORMID) == low) {
        //steer to the right
	printf("SteeringLeft\n");
/*
        while(digitalRead(IRSENSORLEFT) == high && digitalRead(IRSENSORMID) == low) {
            SmoothLeft(allMotors, 30, &isMoving);
        }
        Move(allMotors, 'F', 20, &isMoving);
*/    }
    else if(digitalRead(IRSENSORRIGHT) == high && digitalRead(IRSENSORMID) == low) {
        //steer to the left
	printf("SteeringRight\n");
/*
        while(digitalRead(IRSENSORRIGHT) == high && digitalRead(IRSENSORMID) == low) {
            SmoothRight(allMotors, 30, &isMoving);
        }
        Move(allMotors, 'F', 20, &isMoving);
  */  }
    else if(digitalRead(IRSENSORLEFT) == high && digitalRead(IRSENSORMID) == high) {
        //turn left
	printf("Turn Left 90\n");
/*
        pthread_create(&speedEncoderThread, NULL, &SpeedEncoderRotations, NULL);
        Move(allMotors, 'L', 20, &isMoving);
        pthread_join(speedEncoderThread, NULL);
 */   }
    else if(digitalRead(IRSENSORRIGHT) == high && digitalRead(IRSENSORMID) == high) {
        //turn left
	printf("Turn right 90\n");
/*
        pthread_create(&speedEncoderThread, NULL, &SpeedEncoderRotations, NULL);
        Move(allMotors, 'R', 20, &isMoving);
        pthread_join(speedEncoderThread, NULL);
 */   }
    else if(digitalRead(IRSENSORMID) == low && digitalRead(IRSENSORLEFT) == low && digitalRead(IRSENSORRIGHT) == low){
        printf("No trail\n");
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
