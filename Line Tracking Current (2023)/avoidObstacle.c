#pragma config(Sensor, S1,     rightS,         sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S2,     leftS,          sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S3,     reflect,        sensorEV3_Color)
#pragma config(Sensor, S4,     sonarSensor,    sensorEV3_Ultrasonic)
#pragma config(Motor,  motorA,          armMotor,      tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, reversed, driveLeft, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, reversed, driveRight, encoder)
#pragma config(Motor,  motorD,           ,             tmotorEV3_Large, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int m = -1; // for motor direction
int face = m*242; // for faceLeft & faceRight
int point = m*480; // for leftPointTurn & rightPointTurn

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

void STP()
{
	motor[motorB]=0;
	motor[motorC]=0;
}

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
void faceLeft()
{
	resetMotorEncoder(motorB);
	resetMotorEncoder(motorC);
	setMotorTarget(motorB, -face, 25);
	setMotorTarget(motorC, face, 25);
	waitUntilMotorStop(motorC);
	sleep(1000);
}
void faceRight()
{
	resetMotorEncoder(motorB);
	resetMotorEncoder(motorC);
	setMotorTarget(motorB, face, 25);
	setMotorTarget(motorC, -face, 25);
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

void avoidObstacle()
{

	/*
	if (hasObstacle == true && getColorReflected(S3) <= 1)
	{
	armDDown();
	}
	*/
	if (hasObstacle == true)
	{
		motor[motorB]=0;
		motor[motorC]=0;
		sleep(1000);

		//segment 1 (left - move - right) (face forward)

		leftPointTurn();
		lilUp(450);  // distance go left (to be determined depend on how big the obstacles are)
		rightPointTurn();
		checkObstacle(3);

		while (hasObstacle == true) // double check
		{
			leftPointTurn();
			lilUp(100);  // distance go left
			rightPointTurn();
			checkObstacle(3);
		}


		// segment 2 (move - right) (face right)

	//	lilUp(650); // distance go forward (to be determined depend on how big the obstacles are)

		resetMotorEncoder(motorB);
		resetMotorEncoder(motorC);

		while (getMotorEncoder(motorB) >= -1300)
		{
			do
			{
				motor[motorB]=-15;
				motor[motorC]=-15;
			}	while ((getColorName(S1)!=colorBlack)&&(getColorName(S2)!=colorBlack));
			break;
		}

		while ((getColorName(S1)!=colorBlack)&&(getColorName(S2)!=colorBlack)){

		STP();
		sleep(500);
		if ((getColorName(S1) == colorBlack && getColorName(S2) == colorBlack))
		{
			lilUp(100);
			faceLeft();
			return;
		}
	}

// go forward, when it see doule black, turn left, and return to lineTracking; if not, go for the set distance.

		rightPointTurn();

		while (hasObstacle == true) //double check
		{
			leftPointTurn();
			lilUp(100);  // distance go left
			rightPointTurn();
			checkObstacle(20);
		}

		// segment 3 (move until black - left - lineTracking) (face forward)
		resetMotorEncoder(motorB);
		resetMotorEncoder(motorC);

		while (getMotorEncoder(motorB) >= -1200)
		{
			do
			{
				motor[motorB]=-15;
				motor[motorC]=-15;
			}	while ((getColorName(S1)!=colorBlack)&&(getColorName(S2)!=colorBlack));
			break;
		}

// go forward, if it see double black, it means its on the track, turn left and lintrack.
// if there's no double black, the line must be on the right side, so turn Right, and move until double black, then turn left to lineTrack.

		if (getMotorEncoder(motorB) >= -1000)
		{
			STP();
			sleep(500);
			faceRight();
			do
			{
				motor[motorB]=-15;
				motor[motorC]=-15;
			}	while ((getColorName(S1)!=colorBlack)&&(getColorName(S2)!=colorBlack));
		}

			STP();
			sleep(500);
			lilUp(100);
			sleep(500);
			faceLeft();
			lilUp();
	}
}

task main()
{
	repeat(forever)
	{
		lilUp();
		avoidObstacle();
	}
}
