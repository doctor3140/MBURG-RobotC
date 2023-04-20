#pragma config(Sensor, S1,     rightS,         sensorEV3_Color, modeEV3Color_RGB_Raw)
#pragma config(Sensor, S2,     leftS,          sensorEV3_Color, modeEV3Color_RGB_Raw)
#pragma config(Sensor, S3,     reflect,        sensorEV3_Color)
#pragma config(Sensor, S4,     sonarSensor,    sensorEV3_Ultrasonic)
#pragma config(Motor,  motorA,          armMotor,      tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, reversed, driveLeft, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, reversed, driveRight, encoder)
#pragma config(Motor,  motorD,           ,             tmotorEV3_Large, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "\lib\teamTools.h"
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


//variables for obstacle
bool hasObstacle = false;

//features
bool checkGreen = true; //to enable/disable lilCheck function
bool checkTurnFurther = false; //to enable/disable turning further when line not found
bool checkSonar = false; //to enable/disable checkObstacle function


void checkObstacle(int x)
{
	if(checkSonar){
	sleep(500); //added to prevent misreading on seesaw
		if (SensorValue[S4] < x)
		{
			hasObstacle = true;
		}
		else
		{
			hasObstacle = false;
		}
	}
}

task display() //Display for Error Log
{
	repeat(forever){
	//displayBigTextLine(2, "LCS: %d", getColorName(leftS));
	//displayBigTextLine(4, "RCS: %d", getColorName(rightS));
	displayRightS(2);
	displayLeftS(4);
	displayBigTextLine(6, "SS: %d", SensorValue[S4]);
	displayBigTextLine(8, "LeftM: %d", getMotorEncoder(leftMotor));
	displayBigTextLine(10, "RightM: %d", getMotorEncoder(rightMotor));
	sleep(20); //refreshrate in ms
	}
}

void findLineLeft()
{
	clearTimer(T1);
	while (time1[T1] < searchTime) //need to find better timing method/boot-out. Consult WindSprints for better bootout
	{
		if (rightEqualsWhite()) //was right
		{
			motorSearchLeft();
			//startTask(display);
		}
		else if(rightEqualsBlack())
		{
			STP();
			sleep(200);

		}
	}

	while (!leftEqualsBlack()) //change to ==white if no work (most likely redundent remove cmt after testing)
	{
		motorSearchRight();
	}
}


void findLineRight()
{
	//playSound(soundBlip);
	clearTimer(T1);
	while (time1[T1] < searchTime) //need to find better timing method/boot-out. Consult WindSprints for better bootout
	{
		if (leftEqualsWhite()) //was left
		{
			motorSearchRight();
			//startTask(display);
		}
		else if (leftEqualsBlack())
		{
			//playSound(soundLowBuzzShort);
			STP();
			sleep(200);
		}
	}
	while ((!rightEqualsBlack())) //change to ==white if no work (most likely redundent remove cmt after testing)
	{
		motorSearchLeft();
		//startTask(display);
		//playSound(soundBlip);
	}
}

	//this is awful, please fix


void leftTurn()
{
	STP();
	sleep(200); //was 500
	encoderForward(tapeThreasholdCM);
	if (leftEqualsBlack()) //was leftS, but since leftS is Right then it should be rightS nvm???
	{
		encoderForward(40);
		encoderPointLeft();
		if(checkTurnFurther && (leftEqualsWhite())){
		findLineLeft();
		}
		encoderForward(20);
		sleep(20);
	}
	else{
		encoderForward(tapeThreasholdCM);
	}
}

void rightTurn()
{
	STP();
	sleep(200);
	encoderForward(tapeThreasholdCM); //Turn off if momentum is too much
	if (rightEqualsBlack()) //was rightS, but since rightS is Left then it should be leftS nvm???
	{
		encoderForward(40);
		encoderPointRight();
		if(checkTurnFurther && rightEqualsWhite()){
		findLineRight();
		}
		encoderForward(20);
		sleep(20);
	}
	else{
		encoderForward(tapeThreasholdCM);
	}
}


//Turns left until sensor sees black or timer runs out and doubles back right
//made for double black and as fail safe when leanDetect fails


void lilCheck(bool leftIsTrue)
{
if(checkGreen){
	//setLEDColor(ledOrangePulse);
	STP();
	sleep(500);
	if(leftIsTrue) //true is left
	{
		resetMotorEncoder(leftMotor);
		resetMotorEncoder(rightMotor);
		setMotorTarget(rightMotor, m*20, 10);
		waitUntilMotorStop(rightMotor);
		if (rightEqualsGreen())
		{
			setMotorTarget(rightMotor, 0, 10); //Was motorC, but seemed to be moving wrong direction
			waitUntilMotorStop(rightMotor);
			STP();
			uTurn();
		}
		else
		{
			setMotorTarget(rightMotor, 0, 10);  //Was motorC, but seemed to be moving wrong direction (what is this do)
			waitUntilMotorStop(rightMotor);
			leftTurn();
		}
	}
	else
	{
		resetMotorEncoder(leftMotor);
		resetMotorEncoder(rightMotor);
		setMotorTarget(leftMotor, m*20, 10);
		waitUntilMotorStop(leftMotor);

		if (leftEqualsGreen())
		{
			setMotorTarget(leftMotor, 0, 10); //Was motorB, but seemed to be moving wrong direction
			waitUntilMotorStop(rightMotor);
			STP();
			uTurn();
		}
		else
		{
			setMotorTarget(leftMotor, 0, 10);
			waitUntilMotorStop(rightMotor);
			rightTurn();
		}
	}
}
}


void lineTracking()
{
	//startTask(display); //to aid in refresh rate of display

	if ((leftEqualsRed())&&(rightEqualsRed())) // both red -> stop at finish line
	{
		STP();
		playTone(1300, 100);
		sleep(6000);
	}

	else if((leftEqualsGreen()) || (rightEqualsGreen())) // find green -> identifyGreen -> make turn
	{
		//playSound(soundBlip);
		STP();
		if ((rightEqualsGreen())&&(leftEqualsGreen())) //both green -> Uturn
		{
			uTurn();
		}
		else if ((leftEqualsGreen()) && (!rightEqualsGreen())) //left green -> turnLeft
		{
			lilCheck(true);
			if (!checkGreen)
			{
				leftTurn();
			}
		}
		else if ((!leftEqualsGreen()) && (rightEqualsGreen())) //right green -> turnRight
		{
			lilCheck(false);
			if (!checkGreen)
			{
				rightTurn();
			}
		}
		else if ((leftEqualsSilver()) && (rightEqualsSilver())) //both silver -> rescue room
		{
			//sweepRoom();
		}
		else
		{
			//lineTracking();
			//IDK whats going on here
			playTone();
		}
	}
if ((rightEqualsBlack())&&(leftEqualsBlack()))//Zig and Intersection //Adddition
		{
			encoderForward(130);//OG 70
			findLineRight();
		}
	else if (rightEqualsBlack()) // lean left
	{
		motorLeanLeft();

		if ((rightEqualsBlack())&&(leftEqualsBlack()))//Zig and Intersection
		{
			encoderForward(130);//OG 70
			findLineRight();
		}
	}

	else if (leftEqualsBlack()) // lean right
	{
		motorLeanRight();

		if ((rightEqualsBlack())&&(leftEqualsBlack()))//Zig and Intersection for LT
		{
			encoderForward(70);
			findLineLeft();
		}
	}

	else if ((rightEqualsWhite())&&(leftEqualsWhite())) //both white -> move in straight line
	{
		motorForward();
	}

	else // problem/unkown -> error sign
	{
		//errormessage(1);
		sleep(500);
		//dumbError = 1;
		//Unknown Color
	}
	checkObstacle(5);
}

void properties(){
		//setMotorDirection('f');
		setWheelDiameterCM(10.5);
		setUTURN(660);
		setPoint(139);
		setSpeed(20);
		setLeanSpeed(6);
		setSearchSpeed(3);
		setDist(2.5);
		setTapeThreasholdCM(2.5);
		setSearchSpeed(3);
		setSearchTime(4000);
		setRawColorSensing(false);
}

//TASK MAIN//
task main()
{
	//armUp();
	clearSounds();
	clearTimer(T1);
	properties();
	startTask(display);
	repeat(forever)
	{
		lineTracking();//basically the entire program
		//avoidObstacle();
		//sweepRoom();
	}

}
=======
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


//variables for obstacle
bool hasObstacle = false;

//features
bool checkGreen = true; //to enable/disable lilCheck function
bool checkTurnFurther = false; //to enable/disable turning further when line not found
bool checkSonar = false; //to enable/disable checkObstacle function

void checkObstacle(int x)
{
if(checkSonar){
sleep(500); //added to prevent misreading on seesaw
	if (SensorValue[S4] < x)
	{
		hasObstacle = true;
	}
	else
	{
		hasObstacle = false;
	}
}
}

task display() //Display for Error Log
{
	repeat(forever){
	displayBigTextLine(2, "LCS: %d", getColorName(leftS));
	displayBigTextLine(4, "RCS: %d", getColorName(rightS));
	displayBigTextLine(6, "SS: %d", SensorValue[S4]);
	displayBigTextLine(8, "LeftM: %d", getMotorEncoder(leftMotor));
	displayBigTextLine(10, "RightM: %d", getMotorEncoder(rightMotor));
	sleep(20); //refreshrate in ms
	}
}

void findLineLeft()
{
	clearTimer(T1);
	playSound(soundBlip);
	encoderForward(2.5);
	while (time1[T1] < searchTime) //need to find better timing method/boot-out. Consult WindSprints for better bootout
	{
		if ((getColorName(rightS)==colorWhite)) //was right
		{
			motorSearchLeft();
			//startTask(display);
		}
		else if(getColorName(rightS)==colorBlack)
		{
			STP();
			sleep(200);

		}
	}

	while ((getColorName(leftS)!=colorBlack)) //change to ==white if no work (most likely redundent remove cmt after testing)
	{
		motorSearchRight();
	}
	STP();
}


void findLineRight()
{
	clearTimer(T1);
	encoderForward(2.5);
	while (time1[T1] < searchTime) //need to find better timing method/boot-out. Consult WindSprints for better bootout
	{
		if ((getColorName(leftS)==colorWhite)) //was left
		{
			motorSearchRight();
			//startTask(display);
		}
		else if (getColorName(leftS)==colorBlack)
		{
			STP();
			sleep(200);
		}
	}
	while ((getColorName(rightS)!=colorBlack)) //change to ==white if no work (most likely redundent remove cmt after testing)
	{
		motorSearchLeft();
		//startTask(display);
	}
	STP();
}

	//this is awful, please fix


void leftTurn()
{
	STP();
	sleep(200); //was 500
	encoderForward(getTapeThreasholdCM());
	if (getColorName(leftS)==colorBlack) //was leftS, but since leftS is Right then it should be rightS nvm???
	{
		encoderForward(8);
		encoderPointLeft();
		if(checkTurnFurther && (getColorName(leftS)==colorWhite)){
		findLineLeft();
		}
		encoderForward();
		sleep(20);
	}
	else{
		encoderForward(getTapeThreasholdCM());
	}
}

void rightTurn()
{
	STP();
	sleep(200);
	//playSound(soundBeepBeep);
	encoderForward(getTapeThreasholdCM()); //Turn off if momentum is too much
	if (getColorName(rightS)==colorBlack) //was rightS, but since rightS is Left then it should be leftS nvm???
	{
		playSound(soundBeepBeep);
		encoderForward(8);
		encoderPointRight();
		if(checkTurnFurther && (getColorName(rightS)==colorWhite)){
		findLineRight();
		}
		encoderForward();
		sleep(20);
	}
	else{
		encoderForward(getTapeThreasholdCM());
	}
}


//Turns left until sensor sees black or timer runs out and doubles back right
//made for double black and as fail safe when leanDetect fails


void lilCheck(bool leftIsTrue)
{
if(checkGreen){
	//setLEDColor(ledOrangePulse);
	STP();
	sleep(500);
	if(leftIsTrue) //true is left
	{
		resetMotorEncoder(leftMotor);
		resetMotorEncoder(rightMotor);
		setMotorTarget(rightMotor, m*20, 10);
		waitUntilMotorStop(rightMotor);
		if (getColorName(rightS)==colorGreen)
		{
			setMotorTarget(rightMotor, 0, 10); //Was motorC, but seemed to be moving wrong direction
			waitUntilMotorStop(rightMotor);
			STP();
			uTurn();
		}
		else
		{
			setMotorTarget(rightMotor, 0, 10);  //Was motorC, but seemed to be moving wrong direction (what is this do)
			waitUntilMotorStop(rightMotor);
			leftTurn();
		}
	}
	else
	{
		resetMotorEncoder(leftMotor);
		resetMotorEncoder(rightMotor);
		setMotorTarget(leftMotor, m*20, 10);
		waitUntilMotorStop(leftMotor);

		if (getColorName(leftS)==colorGreen)
		{
			setMotorTarget(leftMotor, 0, 10); //Was motorB, but seemed to be moving wrong direction
			waitUntilMotorStop(rightMotor);
			STP();
			uTurn();
		}
		else
		{
			setMotorTarget(leftMotor, 0, 10);
			waitUntilMotorStop(rightMotor);
			rightTurn();
		}
	}
}
}


void lineTracking()
{
	//startTask(display); //to aid in refresh rate of display

	if ((getColorName(leftS)==colorRed)&&(getColorName(rightS)==colorRed)) // both red -> stop at finish line
	{
		STP();
		playTone(1300, 100);
		sleep(6000);
	}

	else if((getColorName(leftS)==colorGreen) || (getColorName(rightS)==colorGreen)) // find green -> identifyGreen -> make turn
	{
		STP();
		if ((getColorName(rightS)==colorGreen)&&(getColorName(leftS)==colorGreen)) //both green -> Uturn
		{
			uTurn();
		}
		else if ((getColorName(leftS)==colorGreen) && (getColorName(rightS)!=colorGreen)) //left green -> turnLeft
		{
			lilCheck(true);
			if (!checkGreen)
			{
				leftTurn();
			}
		}
		else if ((getColorName(leftS)!=colorGreen) && (getColorName(rightS)==colorGreen)) //right green -> turnRight
		{
			lilCheck(false);
			if (!checkGreen)
			{
				rightTurn();
			}
		}
		else
		{
			//lineTracking();
			//IDK whats going on here
		}
	}
if ((getColorName(rightS)==colorBlack)&&(getColorName(leftS)==colorBlack))//Zig and Intersection //Adddition
		{
			//playTone(20, 5);
			encoderForward(5);//OG 70
			findLineRight();
		}
	else if (getColorName(rightS)==colorBlack) // lean left
	{
		//playTone(soundBeepBeep);
		motorLeanRight();

		if ((getColorName(rightS)==colorBlack)&&(getColorName(leftS)==colorBlack))//Zig and Intersection
		{
			encoderForward(5);//OG 70
			findLineRight();
		}
	}

	else if (getColorName(leftS)==colorBlack) // lean right
	{
		motorLeanLeft();

		if ((getColorName(rightS)==colorBlack)&&(getColorName(leftS)==colorBlack))//Zig and Intersection for LT
		{
			encoderForward(5);
		}
	}

	else if ((getColorName(rightS)==colorWhite)&&(getColorName(leftS)==colorWhite)) //both white -> move in straight line
	{
		motorForward();
	}

	else // problem/unkown -> error sign
	{
		//errormessage(1);
		sleep(500);
		//dumbError = 1;
		//Unknown Color
	}
	checkObstacle(5);
}

void properties(){
		//setMotorDirection('f');
		setWheelDiameterCM(7.455);
		setUTURN(660);
		setPoint(332);
		setSpeed(8);
		setLeanSpeed(6);
		setSearchSpeed(6);
		setDist(2.5);
		setTapeThreasholdCM(5);
		setSearchSpeed(6);
		setSearchTime(15); //was 500
}

//TASK MAIN//
task main()
{
	clearSounds();
	clearTimer(T1);
	properties();
	startTask(display);
	repeat(forever)
	{
		lineTracking();//basically the entire program
		//avoidObstacle();
		//sweepRoom();
	}
}
>>>>>>> 42a39af378ac8ae58b1af7ed0d507521add3d3ca:Line Tracking Current (2023)/rtest-rewrite.c
