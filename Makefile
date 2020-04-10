motorTest: main.c MotorShield.c
	gcc -o motorTest main.c MotorShield.c -I. -lwiringPi
