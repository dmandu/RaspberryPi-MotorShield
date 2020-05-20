#include <stdio.h>
#include<stdlib.h>

#ifndef SPEEDENCODER_H
#define SPEEDENCODER_H

struct MeasureDataArgs {
	int * speedptr;
	_Bool * movingptr;
};

void InitSpeedEncoder(int);

void * SpeedEncoderRotations(void *);

#endif //SPEEDENCODER_H
