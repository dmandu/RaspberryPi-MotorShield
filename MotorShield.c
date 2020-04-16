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
void Init(struct Motors *motor, int enable, int forward, int reverse) {
	if(wiringPiSetup() < 0) {
		printf("setup failed\n");
		exit(1);
    	}
	//*****************************************
	//Set the variables of the motor struct
	//The enable pin and 2 control pins
	//I believe the 2 control pins are for
	//forward and reverse, but not too sure
	//******************************************
	motor->enablePin = enable;
	motor->forwardPin = forward;
	motor->reversePin = reverse;
	softPwmCreate(enable, 50, 100);


	//****************************************
	//Set the pins to all be outputs
	//***************************************
    	pinMode(motor->enablePin, OUTPUT);
    	pinMode(motor->forwardPin, OUTPUT);
    	pinMode(motor->reversePin, OUTPUT);

	//**************************************
	//Turn on enable pin and turn off the
	//2 control pins
	//**************************************
    	digitalWrite(motor->enablePin, HIGH);
    	digitalWrite(motor->forwardPin, LOW);
    	digitalWrite(motor->reversePin, LOW);

	//************************************
	//Print the pin numbers just to check
	//************************************
	printf("\nEnablePin: %d", motor->enablePin);
	printf("\nForwardPin: %d", motor->forwardPin);
	printf("\nReversePin: %d\n", motor->reversePin);
}


//*************************************
//Method to test that that motors are
//moving either forward or reverse
//speed is the PWM range 0-100
//*************************************
void Move(struct Motors *motor, char direction, int speed) {

	softPwmWrite(motor->enablePin, speed);
	//******************************************
	//If reverse direction, turn reverse pin on
	//and turn off forward pin, else move foward
	//******************************************
	if(direction == 'R') {
        	digitalWrite(motor->forwardPin, LOW);
        	digitalWrite(motor->reversePin, HIGH);
    	}
    	else {
        	digitalWrite(motor->forwardPin, HIGH);
        	digitalWrite(motor->reversePin, LOW);
    	}

	//*******************************
	//Print pins just to check they
	//are same as we initialized
	//******************************
	printf("Move()\n");
	printf("EnablePin: %d\n", motor->enablePin);
	printf("ForwardPin: %d\n", motor->forwardPin);
	printf("ReversePin: %d\n", motor->reversePin);
}

void Stop(bool Yes, struct Motors *motor) {
	if(Yes) {
		digitalWrite(motor->forwardPin, LOW);
		digitalWrite(motor->reversePin, LOW);
	}
}
