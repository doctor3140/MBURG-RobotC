#pragma config(Sensor, S1,     leftS,          sensorEV3_Color, modeEV3Color_RGB_Raw)
#pragma config(Sensor, S2,     rightS,         sensorEV3_Color, modeEV3Color_RGB_Raw)
#pragma config(Sensor, S3,     ,               sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S4,     sonarSensor,    sensorEV3_Ultrasonic)
#pragma config(Motor,  motorA,          armMotor,      tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, driveRight, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

	//#include "typeTools.h"
	string rightSen = "right";
	const string leftSen = "leftSensor";

	bool equals(string str1, string str2)
	{
	return (stringFind(str1, str2)>=0);
	}

void linchP(string sen){
repeat(forever){
			if(stringFind(sen, rightSen)>=0)){
				motor[motorB] = (-50);
				motor[motorC] = (50);
			}
			/*
			else if(equals("left", "left")){
				motor[motorB] = (50);
				motor[motorC] = (-50);
			}
			*/
	}
}
/*
task sensorLeft(){
	linchP();
}

task sensorRight(){
	linchP("rightSensor");
}
*/
task main()
{
	//startTask(sensorLeft);
	//startTask(sensorRight);
	linchP("right");
}