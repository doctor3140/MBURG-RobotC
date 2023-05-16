#pragma config(Sensor, S1,     rightS,         sensorEV3_Color, modeEV3Color_RGB_Raw)
#pragma config(Sensor, S2,     leftS,          sensorEV3_Color, modeEV3Color_RGB_Raw)
#pragma config(Sensor, S3,     reflect,        sensorEV3_Color)
#pragma config(Sensor, S4,     sonarSensor,    sensorEV3_Ultrasonic)
#pragma config(Motor,  motorA,          armMotor,      tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, driveRight, encoder)
#pragma config(Motor,  motorD,           ,             tmotorEV3_Large, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "lib\teamTools.h"
#include "lib\RawColorTools.h"
/*
the width and the height: 120 cm & 90 cm
you have to execute the code to check if there is a silver line before executing this file
*/
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define LENGTH 1
#define WIDTH 2

float boxWidth;
float boxLength;
float boxMargin;

float robotFront;
float robotBack;
float robotSides;

float robotWidth = 13.6;
float robotLength = 17;

int currentDirection = 0;
int turnNumberInRoom = (int)((boxLength/robotWidth));

bool rightStart = true;
bool errorRescue = false;

float currentXY[2] = {
	{0, 0}
};

string direction[4] = {
	{"Up", "Down", "Left", "Right"}
};

float boxSize[2] = {
	{120, 90}
};
int CornerLocationForLeft[3] = {
	{0, 1, 2} //from left to right and up to down, so upper left is 0, upper right is 1, lower right is 2
};
void setBoxDimensions(float w, float l, float m){
	boxWidth = w;
	boxLength = l;
	boxMargin = m;
}

task displayPos(){
		repeat(forever){
		displayBigTextLine(2, "SS: %d", SensorValue[S4]);
		displayBigTextLine(4, "X: %d", currentXY[0]);
		displayBigTextLine(6, "Y: %d", currentXY[1]);
		displayBigTextLine(6, "D: %d", direction[currentDirection]);
		sleep(10); //refreshrate in ms
	}
}

void oneSweep(){ //this is one sweep from left to right
	encoderForward(boxWidth-robotWidth);
}

void sweepRoomFromLeft(){
	encoderPointLeft();
	sleep(500);
	if(SensorValue[S4] <=10) {
		 encoderPointRight();
		 encoderPointRight();
		 //for(int i=0; i<turnturnNumberInRoom; i++){
		 	  oneSweep();
		 //}
	}
}

void executeRescueRoom(){
	setBoxDimensions(120, 90, 5); //I don't know about the bocMargin (in this case, it's 5) means
	resetMotorEncoder(motorB);
	resetMotorEncoder(motorC);
	encoderBackward(robotLength);
	sweepRoomFromLeft();
}

task main()
{
	executeRescueRoom();


}
