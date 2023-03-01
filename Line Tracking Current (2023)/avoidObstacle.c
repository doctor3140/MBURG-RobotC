#pragma config(Sensor, S1,     rightS,         sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S2,     leftS,          sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S3,     reflect,        sensorEV3_Color)
#pragma config(Sensor, S4,     sonarSensor,    sensorEV3_Ultrasonic)
#pragma config(Motor,  motorA,          armMotor,      tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, reversed, driveLeft, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, reversed, driveRight, encoder)
#pragma config(Motor,  motorD,           ,             tmotorEV3_Large, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
#include "\lib\teamTools.h"

bool hasObstacle = false;

void checkObstacle(int x)
{
	if (SensorValue[S4] < x)
	{
		hasObstacle = true;
	}
	else
	{
		hasObstacle = false;
	}
}

/*
void lilUp()
{
	resetMotorEncoder(motorB);
	resetMotorEncoder(motorC);
	setMotorTarget(motorB, m*40, 10);
	setMotorTarget(motorC, m*40, 10);
	waitUntilMotorStop(motorC);
	sleep(1000);
}


void lilUp(int d)
{
	resetMotorEncoder(motorB);
	resetMotorEncoder(motorC);
	setMotorTarget(motorB, m*d, 30);
	setMotorTarget(motorC, m*d, 30);
	waitUntilMotorStop(motorC);
	sleep(1000);
}

void leftPointTurn()
{
	resetMotorEncoder(motorB);
	resetMotorEncoder(motorC);
	setMotorTarget(motorB, -point, 30);
	waitUntilMotorStop(motorB);
	sleep(1000);
}

void rightPointTurn()
{
	resetMotorEncoder(motorB);
	resetMotorEncoder(motorC);
	setMotorTarget(motorB, point, 30);
	waitUntilMotorStop(motorB);
	sleep(1000);
}
*/
void avoidObstacle()
{

	/*
	if (hasObstacle == true && getColorReflected(S3) <= 1)
	{
	armDDown();
	}
	*/
	checkObstacle(8);
	if (hasObstacle == true)
	{
		STP();
		sleep(1000);

		//segment 1 (left - move - right) (face forward)

		encoderPointLeft();
		encoderForward(9);
		//lilUp(450);  // distance go left (to be determined depend on how big the obstacles are)
		encoderPointRight();
		checkObstacle(6);

		while (hasObstacle == true) // double check
		{
			encoderPointLeft();
			encoderForward(5);
			//lilUp(100);  // distance go left
			//rightPointTurn();
			encoderPointRight();
			checkObstacle(6);
		}


		// segment 2 (move - right) (face right)

	//	lilUp(650); // distance go forward (to be determined depend on how big the obstacles are)

		resetMotorEncoder(motorB);
		resetMotorEncoder(motorC);

		while (getMotorEncoder(motorB) >= -1300)
		{
			do
			{
				encoderForward(9);
				sleep(500);
				encoderPointLeft();
				sleep(500);
				motorForward(15);
				//Should now be on the opposite side of the obstacle facing forward (Yet to be tested)
				//motor[motorB]=15;
				//motor[motorC]=15;
			}	while ((getColorName(S1)!=colorBlack)&&(getColorName(S2)!=colorBlack));
			break;
		}

		while ((getColorName(S1)!=colorBlack)&&(getColorName(S2)!=colorBlack)){

		STP();
		sleep(500);
		if ((getColorName(S1) == colorBlack && getColorName(S2) == colorBlack))
		{
			encoderForward(5); //lilUp(100);
			encoderPointLeft();
			return;
		}
	}

// go forward, when it see doule black, turn left, and return to lineTracking; if not, go for the set distance.

		encoderPointRight();
	//rightPointTurn();

		while (hasObstacle == true) //double check
		{
			encoderPointLeft();
			encoderForward(5); //lilUp(100);  // distance go left
			encoderPointRight();
			checkObstacle(20);
		}

		// segment 3 (move until black - left - lineTracking) (face forward)
		resetMotorEncoder(motorB);
		resetMotorEncoder(motorC);

		while (getMotorEncoder(motorB) >= -1200)
		{
			do
			{
				motorForward(15);
				//motor[motorB]=15;
				//motor[motorC]=15;
			}	while ((getColorName(S1)!=colorBlack)&&(getColorName(S2)!=colorBlack));
			break;
		}

// go forward, if it see double black, it means its on the track, turn left and lintrack.
// if there's no double black, the line must be on the right side, so turn Right, and move until double black, then turn left to lineTrack.

		if (getMotorEncoder(motorB) >= -1000)
		{
			STP();
			sleep(500);
			encoderPointRight();
			do
			{
				motorForward(15);
				//motor[motorB]=15;
				//motor[motorC]=15;
			}	while ((getColorName(S1)!=colorBlack)&&(getColorName(S2)!=colorBlack));
		}

			STP();
			sleep(500);
			encoderForward(5); //lilUp(100);
			sleep(500);
			encoderPointLeft();
			encoderForward(); //lilUp();
	}
}

void properties(){
		//setMotorDirection('f');
		setWheelDiameterCM(7.455);
		setUTURN(660);
		setPoint(332);
		setSpeed(10);
		setLeanSpeed(6);
		setSearchSpeed(6);
		setDist(2.5);
		setTapeThreasholdCM(5);
		setSearchSpeed(6);
		setSearchTime(10000);
}
task main()
{
	properties();
	repeat(forever)
	{
		encoderForward(); //lilUp();
		avoidObstacle();
	}
}
