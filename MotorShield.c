//
// Created by d22ma on 4/9/2020.
//

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <wiringPi.h>
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
//*************************************
void Move(struct Motors *motor, char direction) {

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
