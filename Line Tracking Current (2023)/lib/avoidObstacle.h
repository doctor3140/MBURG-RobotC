#pragma config(Sensor, S1,     rightS,         sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S2,     leftS,          sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S3,     reflect,        sensorEV3_Color)
#pragma config(Sensor, S4,     sonarSensor,    sensorEV3_Ultrasonic)
#pragma config(Motor,  motorA,          armMotor,      tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, driveRight, encoder)
#pragma config(Motor,  motorD,           ,             tmotorEV3_Large, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "teamTools.h"
float maxObstacleSize = 14;
bool hasObstacle = false;
float obstacleDistance = 3; //the distance when it will see the obstacle in cm (confirm this)
float turnDistance= robotWidth/2;  // 1 is margin error



void checkObstacle(int x)
{
	if (SensorValue[S4] <= x)
	{
		hasObstacle = true;
	}
	else
	{
		hasObstacle = false;
	}
}

task obstacleDisplay() //Display for Error Log
{
	repeat(forever){
	displayBigTextLine(6, "SS: %d", SensorValue[S4]);
	displayBigTextLine(8, "LeftM: %d", getMotorEncoder(leftMotor));
	displayBigTextLine(10, "RightM: %d", getMotorEncoder(rightMotor));
	sleep(10); //refreshrate in ms
	}
}


void avoidObstacle()
{
	checkObstacle(obstacleDistance);
	//checkObstacle(obstacleDistance+turnDistance);

	if (hasObstacle == true)
	{
		resetMotorEncoder(motorB);
		resetMotorEncoder(motorC);
		encoderBackward(turnDistance-obstacleDistance);

		STP();
		sleep(1000);

		//segment 1 (left - move - right) (face forward)

		encoderPointLeft();
		encoderForward(robotWidth);
		 // distance go left (to be determined depend on how big the obstacles are)
		encoderPointRight();
		checkObstacle(obstacleDistance);

		// segment 2 (move - right) (face right)

	 // distance go forward (to be determined depend on how big the obstacles are)

		resetMotorEncoder(motorB);
		resetMotorEncoder(motorC);

		encoderForward((obstacleDistance+robotLength)+(2*turnDistance));

	// go forward, when it see doule black, turn left, and return to lineTracking; if not, go for the set distance.

		encoderPointRight();

		// segment 3 (move until black - left - lineTracking) (face forward)
		resetMotorEncoder(motorB);
		resetMotorEncoder(motorC);
		while((getColorName(leftS)==colorWhite)||(getColorName(leftS)==colorWhite)){
			motorForward(5);
			}
			sleep(500);
			//if(getColorName(S1)==colorWhite)
				encoderPointLeft();

// go forward, if it see double black, it means its on the track, turn left and lintrack.
// if there's no double black, the line must be on the right side, so turn Right, and move until double black, then turn left to lineTrack.
			STP();
			sleep(500);
		}
}

void setObstacleDistance(float x){
	obstacleDistance=x;
}
