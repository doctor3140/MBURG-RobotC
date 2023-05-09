#pragma config(Sensor, S1,     leftS,          sensorEV3_Color, modeEV3Color_RGB_Raw)
#pragma config(Sensor, S2,     rightS,         sensorEV3_Color, modeEV3Color_RGB_Raw)
#pragma config(Sensor, S3,     ,               sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S4,     sonarSensor,    sensorEV3_Ultrasonic)
#pragma config(Motor,  motorA,          armMotor,      tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, driveRight, encoder)

#include "lib/teamTools.h"

task main(){
	motor[motorB] = 20;
	repeat(forever){
		displayCenteredTextLine(2, "Left RPM is: %d", getMotorRPM(leftMotor);
		sleep(10);
	}
}

