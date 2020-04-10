#include <stdio.h>
#include "MotorShield.h"

int main() {
	struct Motors motor1;
	/*
	motor1.enablePin = 0;
	motor1.forwardPin = 3;
	motor1.reversePin = 2;
	*/
   	Init(&motor1, 0, 3, 2);
   	Move(&motor1, 'R');

   	return 0;
}
