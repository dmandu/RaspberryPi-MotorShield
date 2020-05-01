assignment4: main.c MotorShield.c SpeedEncoder.c DistanceSensor.c
	gcc -o assignment4 main.c MotorShield.c SpeedEncoder.c DistanceSensor.c -I. -lwiringPi -lpthread
