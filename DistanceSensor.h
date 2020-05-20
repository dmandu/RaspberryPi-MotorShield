#include <stdio.h>

#ifndef DISTANCESENSOR_H
#define DISTANCESENSOR_H


void InitDistanceSensor(int, int);

double MeasureDistance();

void avoidObstacle(int * action);

void maneuverObstacle(int * action);
#endif //DISTANCESENSOR_H
