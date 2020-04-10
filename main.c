#include <stdio.h>
#include "MotorShield.h"

int main() {
	struct Motors motor1;

	//***************************************************
	//These ints are the number of the wiringPi library pins
	//they correspond to pins 11, 15, and 13 on the actual Pi
	//I chose these because in the motor shield pdf on iLearn
	//in the pin description section it has these pins for Motor1
	//****************************************************
   	Init(&motor1, 0, 3, 2);
   	Move(&motor1, 'R');

   	return 0;
}
