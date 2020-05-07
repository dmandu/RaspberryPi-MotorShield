robotCar: main.c MotorShield.c SpeedEncoder.c DistanceSensor.c
	gcc -o robotCar main.c MotorShield.c SpeedEncoder.c DistanceSensor.c -I. -lwiringPi -lpthread
