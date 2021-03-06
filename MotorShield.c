/**************************************************************
* Class: CSC-615-01 Spring 2020
* Name: David Mandujano
* Student ID: 911901177
* Project: Assignment3 - Motors
*
* File: MotorShield.c
*
* Description: This file contains the instructions of each method to
*		initialize and run the motos on the Raspberry Pi
**************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <wiringPi.h>
#include <softPwm.h>
#include "MotorShield.h"


//******************************************
//Method to initialize the motor struct
//setting the pins that are used by each motor
//******************************************
void Init(struct Motors * motor, int enable, int forward, int reverse) {
	//*****************************************
	//Set the variables of the motor struct
	//The enable pin and 2 control pins
	//I believe the 2 control pins are for
	//forward and reverse, but not too sure
	//******************************************
	motor->enablePin = enable;
	motor->forwardPin = forward;
	motor->reversePin = reverse;


	//****************************************
	//Set the pins to all be outputs
	//***************************************
        softPwmCreate(motor->enablePin, 0, 100);

    	pinMode(motor->enablePin, OUTPUT);
    	pinMode(motor->forwardPin, OUTPUT);
    	pinMode(motor->reversePin, OUTPUT);

	//**************************************
	//Turn on enable pin and turn off the
	//2 control pins
	//**************************************
	    digitalWrite(motor->enablePin,HIGH);
    	digitalWrite(motor->forwardPin, LOW);
    	digitalWrite(motor->reversePin, LOW);


}


void Move(struct Motors motor [], char direction,  int speed, _Bool * moving) {
    if(*moving != TRUE) {
        *moving = TRUE;
    }
    for(int i = 0; i < 4; ++i) {
        softPwmWrite(motor[i].enablePin, speed);
    }

	if(direction == 'F') {
		for(int i = 0; i < 4; ++i) {
            //digitalWrite(motor[i].enablePin, HIGH);

            digitalWrite(motor[i].reversePin, LOW);
			digitalWrite(motor[i].forwardPin, HIGH);
		}
	}
	else if(direction == 'B') {
		for(int i = 0; i < 4; ++i) {
            //digitalWrite(motor[i].enablePin, HIGH);

            digitalWrite(motor[i].forwardPin, LOW);
			digitalWrite(motor[i].reversePin, HIGH);
		}
	}
	else if(direction == 'R') {
		for(int i = 0; i < 4; ++i) {
		    //digitalWrite(motor[i].enablePin, HIGH);
			if(i == 0 || i == 2) {
				digitalWrite(motor[i].reversePin, LOW);
				digitalWrite(motor[i].forwardPin, HIGH);
			}
			else {
				digitalWrite(motor[i].forwardPin, LOW);
				digitalWrite(motor[i].reversePin, HIGH);
			}
		}
	}
	else if(direction == 'L') {
		for(int i = 0; i < 4; ++i) {
			if(i == 0 || i == 2) {
				digitalWrite(motor[i].forwardPin, LOW);
				digitalWrite(motor[i].reversePin, HIGH);
			}
			else {
				digitalWrite(motor[i].reversePin, LOW);
				digitalWrite(motor[i].forwardPin, HIGH);
			}
		}
	}
}

//*************************************
//Method to test that that motors are
//moving either forward or reverse
//speed is the PWM range 0-100
//*************************************
void Forward(struct Motors * motor, int speed) {

	softPwmWrite(motor->enablePin, speed);
	//******************************************
	//If reverse direction, turn reverse pin on
	//and turn off forward pin, else move foward
	//******************************************

	digitalWrite(motor->reversePin, LOW);
	digitalWrite(motor->forwardPin, HIGH);
}

void Reverse(struct Motors * motor, int speed) {

	softPwmWrite(motor->enablePin, speed);

	digitalWrite(motor->forwardPin, LOW);
	digitalWrite(motor->reversePin, HIGH);
}

void Left(struct Motors * motor1, struct Motors * motor2, struct Motors * motor3, struct Motors * motor4, int speed) {

	Reverse(motor1, speed);
	Reverse(motor3, speed);
	Forward(motor2, speed);
	Forward(motor4, speed);
}

void Right(struct Motors * motor1, struct Motors * motor2, struct Motors * motor3, struct Motors * motor4, int speed) {

	Reverse(motor2, speed);
	Reverse(motor4, speed);
	Forward(motor1, speed);
	Forward(motor3, speed);
}


void SmoothRight(struct Motors motors [], int speed, _Bool * moving) {
    for(int i = 0; i < 4; ++i) {
        if(i == 0 || i == 2) {
            softPwmWrite(motors[i].enablePin, speed);
        }
    }
}

void SmoothLeft(struct Motors motors [], int speed, _Bool * moving) {
    for(int i = 2; i < 4; ++i) {
        if(i == 1 || i == 3) {
            softPwmWrite(motors[i].enablePin, speed);
        }
    }
}


void Stop(_Bool Yes, struct Motors motors[], _Bool * moving) {
	if(Yes) {
		for(int i = 0; i < 4; ++i) {
			digitalWrite(motors[i].forwardPin, LOW);
			digitalWrite(motors[i].reversePin, LOW);
		}
	}
	*moving = FALSE;
}
