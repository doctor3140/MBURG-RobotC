#pragma config(Sensor, S1,     leftS,          sensorEV3_Color, modeEV3Color_RGB_Raw)
#pragma config(Sensor, S2,     rightS,         sensorEV3_Color, modeEV3Color_RGB_Raw)
#pragma config(Sensor, S3,     ,               sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S4,     sonarSensor,    sensorEV3_Ultrasonic)
#pragma config(Motor,  motorA,          armMotor,      tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, driveRight, encoder)
#include "typeTools.h"
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
	int white[3] = {355, 397, 196};
	int black[3] = {33, 42, 22};
	int target[3] = {(white[0]-black[0])/2, (white[1]-black[1])/2, (white[2]-black[2])/2}; //target for color sensor in order of red blue green. We assume white[i] => black[i] so we don't have to worry about negatives
	int current[3] = {1, 1, 1}; //current values of Sensors
	int diff[3];
	float baseSpeed = -20;
	float Kp = 1.2; //weight of new data //1.2
	float Ki = 0.005; //makes it follow straight line more //.005
	float Turn;
	float Kd = .01; //weight of change //.01
	//float Kd = .01; //weight of change //.01


	//Other
	float errorOld = 0;
	float errorNew;
	float derivative;
	float integral;

	//Checked values
	// white = {355, 397, 196}
	// black = {33, 42, 22}

task display(){
	displayBigTextLine(2, "C: %d %d %d", current[0], current[1], current[2]);
	displayBigTextLine(4, "T: %d %d %d", target[0], target[1], target[2]);
	displayBigTextLine(6, "NE: %d", errorNew);
}



float calculate(){
	float res;
	for(int i = 0; i<3; i++){
		res = current[i]-target[i];
	}
	return res/3;
}
//there might be a better way to do this with a vector output, however, I will try this with just a magnitude

void calulateColorDiff(int *expected, int *actual){
	for(int i = 0; i<3; i++){
		diff[i] = expected[i] - actual[i];
	}
}

//void calibrate(string sensor, int *color){
//	getRawRGB(sensor, current[0], current[1], current[2]);

//}

void calibrate(){
		repeat(forever){
		getColorRawRGB(rightS, current[0], current[1], current[2]);
		startTask(display);
	}
}

void PID(){
	Kp = 8;
repeat(forever){
		getColorRawRGB(leftS, current[0], current[1], current[2]);
		startTask(display);
		if(!equals()){
			errorNew = calculate();
			integral+=errorNew;
			derivative = errorNew - errorOld;
			Turn = (Kp*(errorNew)+Ki*(integral)+Kd*(derivative));
			motor[motorB] = (baseSpeed-Turn);
			motor[motorC] = (baseSpeed+Turn);
			errorOld = errorNew;
			}
		motor[motorB] = baseSpeed;
		motor[motorC] = baseSpeed;
	}
}

void linchP(string sensor, float Kp, int baseSpeed){
	string rightSensor = "rightS";
repeat(forever){
		getColorRawRGB(rightS, current[0], current[1], current[2]);
		startTask(display);
		if(!equals()){
			errorNew = calculate();
			Turn = (Kp*(errorNew));
			if(equals(sensor, rightSensor)){
				motor[motorB] = (baseSpeed+Turn);
				motor[motorC] = (baseSpeed-Turn);
			}
			else{
				motor[motorB] = (baseSpeed-Turn);
				motor[motorC] = (baseSpeed+Turn);
			}
			errorOld = errorNew;
			}
		motor[motorB] = baseSpeed;
		motor[motorC] = baseSpeed;
	}
}

void linchP(){
	Kp = 5;
repeat(forever){
		getColorRawRGB(rightS, current[0], current[1], current[2]);
		startTask(display);
		if(!equals()){
			errorNew = calculate();
			Turn = (Kp*(errorNew));
			motor[motorB] = (baseSpeed+Turn);
			motor[motorC] = (baseSpeed-Turn);
			errorOld = errorNew;
			}
		motor[motorB] = baseSpeed;
		motor[motorC] = baseSpeed;
	}
}

void twoSensors(){
	repeat(forever){

	}
}


task main()
{
	setArrays(current, target);
	linchP();
}
