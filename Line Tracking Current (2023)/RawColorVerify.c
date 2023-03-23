#pragma config(Sensor, S1,     rightS,         sensorEV3_Color, modeEV3Color_RGB_Raw)
#pragma config(Sensor, S2,     leftS,          sensorEV3_Color, modeEV3Color_RGB_Raw)
#pragma config(Sensor, S3,     reflect,        sensorEV3_Color)
#pragma config(Sensor, S4,     sonarSensor,    sensorEV3_Ultrasonic)
#pragma config(Motor,  motorA,          armMotor,      tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, reversed, driveLeft, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, reversed, driveRight, encoder)
#pragma config(Motor,  motorD,           ,             tmotorEV3_Large, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "lib\RawColorTools.h"

/*
rightS is right;
leftS is left;
S4 is Sonar;
C is right;
B is left;

Errors:
1 - Unknown color
2 - Error in leanDetect while change = 0
3 - Error in leanDetect while change does not = 0
*/

//drives backwards right now 1/23/2023



/*

CHANGELOG!! 2/13/23

Rewrote #pragma code to syntax

*/

int colorName = 1;

task display() //Display for Error Log
{
	repeat(forever){
	displayRightS(2);
	displayLeftS(4);
	displayBigTextLine(6, "Color: %d", colorName);
	}
}

task main()
{
	clearSounds();
	clearTimer(T1);
	//colorMarginBlack(15);
	//colorMarginGreen(15);
	//colorMarginRed(15);
	//colorMarginWhite(15);
	startTask(display);
	repeat(forever)
	{
		if((rightEqualsWhite())&&(leftEqualsWhite())){
		colorName = 2;
		}
		else if((rightEqualsGreen())&&(leftEqualsGreen())){
		colorName = 3;
		}
		else if((rightEqualsRed()&&leftEqualsRed())){
		colorName = 4;
		}
		else if((rightEqualsBlack())&&(leftEqualsBlack())){
		colorName = 5;
		}
		else{
			colorName = 1;
		}
		}
	}
