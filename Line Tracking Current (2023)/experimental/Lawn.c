#pragma config(Sensor, S1,     rightS,         sensorEV3_Color, modeEV3Color_RGB_Raw)
#pragma config(Sensor, S2,     leftS,          sensorEV3_Color, modeEV3Color_RGB_Raw)
#pragma config(Sensor, S3,     reflect,        sensorEV3_Color)
#pragma config(Sensor, S4,     sonarSensor,    sensorEV3_Ultrasonic)
#pragma config(Motor,  motorA,          armMotor,      tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, reversed, driveLeft, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, reversed, driveRight, encoder)
#pragma config(Motor,  motorD,           ,             tmotorEV3_Large, openLoop)

#include "lib\teamTools.h"
#include "lib\RawColorTools.h"

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

bool errorRescue = false;

float currentXY[2] = {
	{0, 0}
	};
string direction[4] = {
	{"Up", "Down", "Left", "Right"}
};

int currentDirection = 0; //0 to start forward
//float


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

/*
bool equals(string str1, string str2){
	return (stringFind(str1, str2)>=0);
}
//don't know why I can't use equals() :(
*/
void directionOverFlow(int d){
	if(d==RIGHT){
		if(currentDirection>4){
			currentDirection-=4;
		}
		else{
			currentDirection++;
		}
	}
	else if(d==LEFT){
		if(currentDirection<0){
			currentDirection+=4;
		}
		else{
			currentDirection--;
		}
	}
	else{
		errorRescue=true;
		}
}

void lawnRightTurn(){
	encoderPointRight();
	directionOverFlow(RIGHT);
}

void lawnLeftTurn(){
	encoderPointLeft();
	directionOverFlow(LEFT);
}

void lawnForward(int dist){
	encoderForward(dist);
	if(currentDirection==UP){
		currentXY[1]+=dist;
	}
	else if(currentDirection==DOWN){
		currentXY[1]-=dist;
	}
	else if(currentDirection==RIGHT){
		currentXY[0]+=dist;
	}
	else if(currentDirection==LEFT){
		currentXY[0]-=dist;
	}
	else{
		errorRescue=true;
	}
}

void lawnBackward(int dist){
	encoderBackward(dist);
	if(currentDirection==UP){
		currentXY[1]-=dist;
	}
	else if(currentDirection==DOWN){
		currentXY[1]+=dist;
	}
	else if(currentDirection==RIGHT){
		currentXY[0]-=dist;
	}
	else if(currentDirection==LEFT){
		currentXY[0]+=dist;
	}
	else{
		errorRescue=true;
	}
}



void mowRoom(){
//commented out until needed
//if(rightEqualsReflect()&&leftEqualsReflect){
//ignoring exits, and triangles for zones
STP();
// IDENTIFY WALL //
int firstSide = 0; //to identify if real length has been taken
if((SensorValue(sonarSensor)>=(boxLength-boxLength*boxMargin))&&(SensorValue(sonarSensor)<=(boxLength+boxLength*boxMargin))){
	boxLength=SensorValue(sonarSensor);
	firstSide = LENGTH;
}
else if((SensorValue(sonarSensor)>=(boxWidth-boxWidth*boxMargin))&&(SensorValue(sonarSensor)<=(boxWidth+boxWidth*boxMargin))){
	boxWidth=SensorValue(sonarSensor);
	firstSide = WIDTH;
}
else{
	errorRescue=true;
	//will replace later for case of exit and other stuff
}
lawnForward(robotSides);
lawnRightTurn(); //could also be left?

if(firstSide==LENGTH){
	boxLength=SensorValue(sonarSensor)+robotBack;
}
else if(firstSide==WIDTH){
	boxWidth=SensorValue(sonarSensor)+robotBack;
}
else{
	errorRescue=true;
	//will replace later for case of exit and other stuff
}

//NONE OF THIS WILL WORK PRIOR TO FIGURING OUT WHETHER ITS LEFT OR RIGHT
if(firstSide==LENGTH){
	while(sensorvalue(sonarsensor)<boxLength-robotside){
		lawnforward(1);	
	}
	lawnRight();
	while(SensorValue(sonarSensor)<boxWidth-robotSide){
		lawnForward(1);
	}	
	lawnRight();
}

else if(firstSide==WIDTH){
	while(SensorValue(sonarSensor)<boxWidth-robotSide){
		lawnForward(1);
	}
	lawnRight();
while(sensorvalue(sonarsensor)<boxlength-robotside){
		lawnforward(1);	
	}
	lawnRight();
}

else{
	errorRescue=true;
}
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
	setBoxDimensions(90, 120, .1);
	mowRoom();
}