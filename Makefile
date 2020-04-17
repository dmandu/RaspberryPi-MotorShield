assignment4: main.c MotorShield.c SpeedEncoder.c
	gcc -o assignment4 main.c MotorShield.c SpeedEncoder.c -I. -lwiringPi -lpthread
