#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "MotorShield.h"

int main() {
	struct Motors motor1;
	struct Motors motor2;
	bool Yes = TRUE;
	//***************************************************
	//These ints are the number of the wiringPi library pins
	//they correspond to pins 11, 15, and 13 on the actual Pi
	//I chose these because in the motor shield pdf on iLearn
	//in the pin description section it has these pins for Motor1
	//****************************************************
   	Init(&motor1, 0, 3, 2);
	Init(&motor2, 6, 5, 4);
   	Move(&motor1, 'R', 50);
	Move(&motor2, 'R', 50);
	sleep(5);
	Stop(Yes, &motor1);
	Stop(Yes, &motor2);
	sleep(5);
	Move(&motor1, 'F', 25);
	Move(&motor2, 'F', 25);
	sleep(5);
	Stop(Yes, &motor1);
	Stop(Yes, &motor2);

   	return 0;
}
