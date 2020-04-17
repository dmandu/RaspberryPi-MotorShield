/**************************************************************
* Class: CSC-615-01 Spring 2020
* Name: David Mandujano
* Student ID: 911901177
* Project: Assignment 3 - Motors
*
* File: MotorShield.h
*
* Description: This file is the header file of the MotorShield.c
*		methods. It contains the struct and the definitions
*		of each method.
**************************************************************/

#include <stdio.h>
#include <wiringPi.h>
#include <stdbool.h>

#ifndef ASSIGNMENT3_MOTORSHIELD_H
#define ASSIGNMENT3_MOTORSHIELD_H

struct Motors {
    int enablePin;
    int forwardPin;
    int reversePin;
};

void Move(struct Motors [], char, int);

void Init(struct Motors *, int, int, int);

void Forward(struct Motors *, int);

void Reverse(struct Motors *, int);

void Left(struct Motors *, struct Motors *, struct Motors *, struct Motors *, int);

void Right(struct Motors *, struct Motors *, struct Motors *, struct Motors *, int);

void Stop(bool Yes, struct Motors []);
#endif //ASSIGNMENT3_MOTORSHIELD_H
