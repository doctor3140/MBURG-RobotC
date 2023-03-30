#pragma config(Sensor, S1,     rightS,         sensorEV3_Color, modeEV3Color_RGB_Raw)
#pragma config(Sensor, S2,     leftS,          sensorEV3_Color, modeEV3Color_RGB_Raw)
#pragma config(Sensor, S3,     reflect,        sensorEV3_Color)
#pragma config(Sensor, S4,     sonarSensor,    sensorEV3_Ultrasonic)
#pragma config(Motor,  motorA,          armMotor,      tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, reversed, driveLeft, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, reversed, driveRight, encoder)
#pragma config(Motor,  motorD,           ,             tmotorEV3_Large, openLoop)

#include "\lib\teamTools.h"
#include "lib\RawColorTools.h"

#define UP 0;
#define DOWN 1;
#define LEFT 2;
#define RIGHT 3;

float boxWidth;
float boxLength;
float boxMargin;

float robotFront;
float robotBack;
float robotSides;

bool errorRescue = false;

float currentXY[2] = {
	{0, 0}
	};
string direction[4] = {
	{"Up", "Down", "Left", "Right"}
};

int currentDirection = 0; //0 to start forward



void setBoxDimensions(float w, float l, float m){
	boxWidth = w;
	boxLength = l;
	boxMargin = m;
}

void setRobotDimensions(float f, float b, float s){
	robotFront = f;
	robotBack = b;
	robotSides = s;
} //in CM might want to convert to MM ???

task displayPos(){
		repeat(forever){
		displayBigTextLine(2, "SS: %d", SensorValue[S4]);
		displayBigTextLine(4, "X: %d", currentXY[0]);
		displayBigTextLine(6, "Y: %d", currentXY[1]);
		displayBigTextLine(6, "D: %d", direction[currentDirection]);
		sleep(10); //refreshrate in ms
	}
	}

void directionOverFlow(string d){
	if(d.equals("Right")){
		if(currentDirection>4){
			currentDirection-4;	
		}
		else{
			currentDirection++;
		}
	}
	else{
		if(currentDirection<0){
			currentDirection+4;	
		}
		else{
			currentDirection--;
		}
	}
}

void lawnRightTurn(){
	encoderPointRight();
	directionOverFlow("Right");	
}

void lawnLeftTurn(){
	encoderPointLeft();
	directionOverFlow("Left");	
}

void mowRoom(){
//if(rightEqualsReflect()&&leftEqualsReflect){

	
}
	/*
	mapRoom()
	find wall to front
	find wall to left
	find wall to right
	
	//current goal is to make it know the position in a box and navigate
	*/



//}


void properties(){
		//setMotorDirection('f');
		setWheelDiameterCM(7.455);
		setUTURN(660);
		setPoint(332);
		setSpeed(20);
		setLeanSpeed(6);
		setSearchSpeed(3);
		setDist(2.5);
		setTapeThreasholdCM(2.5);
		setSearchSpeed(3);
		setSearchTime(4000);
}

task main(){
	startTask(displayPos);
	properties();
	setDimension(90, 120, .1);
	mowRoom();
}
