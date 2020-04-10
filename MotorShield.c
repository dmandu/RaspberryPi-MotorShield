//
// Created by d22ma on 4/9/2020.
//

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <wiringPi.h>
#include "MotorShield.h"


void Init(struct Motors *motor, int enable, int forward, int reverse) {
	if(wiringPiSetup() < 0) {
		printf("setup failed\n");
		exit(1);
    	}
	motor->enablePin = enable;
	motor->forwardPin = forward;
	motor->reversePin = reverse;

    	pinMode(motor->enablePin, OUTPUT);
    	pinMode(motor->forwardPin, OUTPUT);
    	pinMode(motor->reversePin, OUTPUT);

    	digitalWrite(motor->enablePin, HIGH);
    	digitalWrite(motor->forwardPin, LOW);
    	digitalWrite(motor->reversePin, LOW);

	printf("\nEnablePin: %d", motor->enablePin);
	printf("\nForwardPin: %d", motor->forwardPin);
	printf("\nReversePin: %d\n", motor->reversePin);
}

void Move(struct Motors *motor, char direction) {
	if(direction == 'R') {
        	digitalWrite(motor->forwardPin, LOW);
        	digitalWrite(motor->reversePin, HIGH);
    	}
    	else {
        	digitalWrite(motor->forwardPin, HIGH);
        	digitalWrite(motor->reversePin, LOW);
    	}

	printf("Move()\n");
	printf("EnablePin: %d\n", motor->enablePin);
	printf("ForwardPin: %d\n", motor->forwardPin);
	printf("ReversePin: %d\n", motor->reversePin);
}
