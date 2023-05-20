#pragma config(Sensor, S1,     rightS,         sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S2,     leftS,          sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S3,     reflect,        sensorEV3_Color)
#pragma config(Sensor, S4,     sonarSensor,    sensorEV3_Ultrasonic)
#pragma config(Motor,  motorA,          armMotor,      tmotorEV3_Medium, PIDControl, reversed, encoder)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, driveRight, encoder)
#pragma config(Motor,  motorD,          Other,         tmotorEV3_Medium, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "\lib\teamTools.h"
#include "\lib\avoidObstacle.h"

#define FINDDIST 0.75
#define TURNDIST 1
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


CHANGELOG!! 2/13/23

Rewrote #pragma code to syntax

*/


//features
bool checkGreen = true; //to enable/disable lilCheck function
bool checkTurnFurther = false; //to enable/disable turning further when line not found
bool checkSonar = false; //to enable/disable checkObstacle function

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

void findLineLeft(bool bothWheels)
{
	encoderForward(FINDDIST);
	clearTimer(T1);
	//playSound(soundBlip);
	if(bothWheels){
	while (time1[T1] < searchTime) //need to find better timing method/boot-out. Consult WindSprints for better bootout
	{
		if ((getColorName(rightS)==colorWhite)) //was right
		{

			motorSearchLeft();
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
	else{
if ((getColorName(rightS)==colorWhite)) //was right
		{
		motor[rightMotor] = getSearchSpeed();
		}
		else if(getColorName(rightS)==colorBlack)
		{
			STP();
			sleep(200);
		}
	}
}


void findLineRight(bool bothWheels){
	encoderForward(FINDDIST);
	clearTimer(T1);
if(bothWheels){
	while (time1[T1] < searchTime) //need to find better timing method/boot-out. Consult WindSprints for better bootout
	{
		if ((getColorName(leftS)==colorWhite)) //was right
		{

			motorSearchRight();
		}
		else if(getColorName(leftS)==colorBlack)
		{
			STP();
			sleep(200);
		}
	}
	while ((getColorName(rightS)!=colorBlack)) //change to ==white if no work (most likely redundent remove cmt after testing)
	{
		motorSearchLeft();
	}
	STP();
	}
	else{
if ((getColorName(leftS)==colorWhite)) //was right
		{
		motor[leftMotor] = getSearchSpeed();
		}
		else if(getColorName(leftS)==colorBlack)
		{
			STP();
			sleep(200);
		}
	}
}

	//this is awful, please fix


void leftTurn()
{
	STP();
	sleep(200); //was 500
	encoderForward(getTapeThreasholdCM());
	if (getColorName(leftS)==colorBlack) //was leftS, but since leftS is Right then it should be rightS nvm???
	{
		//encoderForward(TURNDIST);
		encoderPointLeft();
		if(checkTurnFurther && (getColorName(leftS)==colorWhite)){
		findLineLeft(true);
		}
		encoderForward();
		sleep(20);
	}
	else{
		findLineRight(false);
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
		//encoderForward(TURNDIST);
		encoderPointRight();
		if(checkTurnFurther && (getColorName(rightS)==colorWhite)){
		findLineRight(true);
		}
		encoderForward(false);
		sleep(20);
	}
	else{
		findLineLeft(false);
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
			setMotorTarget(rightMotor, 0, 0); //Was motorC, but seemed to be moving wrong direction
			waitUntilMotorStop(rightMotor);
			STP();
			uTurn();
		}
		else
		{
			setMotorTarget(rightMotor, 0, 0);  //Was motorC, but seemed to be moving wrong direction (what is this do)
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
			setMotorTarget(leftMotor, 0, 0); //Was motorB, but seemed to be moving wrong direction
			waitUntilMotorStop(leftMotor);
			STP();
			uTurn();
		}
		else
		{
			setMotorTarget(leftMotor, 0, 0);
			waitUntilMotorStop(leftMotor);
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
			encoderForward(getTapeThreasholdCM());
			findLineRight(true);
		}
	else if (getColorName(rightS)==colorBlack) // lean left
	{
		//playTone(soundBeepBeep);
		motorLeanRight();

		if ((getColorName(rightS)==colorBlack)&&(getColorName(leftS)==colorBlack))//Zig and Intersection
		{
			encoderForward(getTapeThreasholdCM());
			findLineRight(true);
		}
		/*
		//reduntant I think
		else if((getColorName(rightS)==colorGreen)&&(getColorName(leftS)==colorBlack)){
			encoderForward(getTapeThreasholdCM()*2);
			findLineRight();

		}
		else if((getColorName(rightS)==colorBlack)&&(getColorName(leftS)==colorGreen)){
			encoderForward(getTapeThreasholdCM()*2);
			findLineLeft();
		}
		*/
	}

	else if (getColorName(leftS)==colorBlack) // lean right
	{
		motorLeanLeft();

		if ((getColorName(rightS)==colorBlack)&&(getColorName(leftS)==colorBlack))//Zig and Intersection for LT
		{
			encoderForward(getTapeThreasholdCM());
			findLineLeft(true);
		}
		/*
		//reduntant I think
		else if((getColorName(rightS)==colorGreen)&&(getColorName(leftS)==colorBlack)){
			encoderForward(getTapeThreasholdCM()*2);
		  findLineRight();
		}
		else if((getColorName(rightS)==colorBlack)&&(getColorName(leftS)==colorGreen)){
			encoderForward(getTapeThreasholdCM()*2);
			findLineLeft();
			}
		*/
}
	else if ((getColorName(rightS)==colorWhite)&&(getColorName(leftS)==colorWhite)) //both white -> move in straight line
	{
		motorForward();
	}

	else // problem/unkown -> error sign
	{
		//errormessage(1);
		//sleep(500);
		//dumbError = 1;
		//Unknown Color
	}
	checkObstacle(5);
}

void properties(){
		//setMotorDirection('f');
		setWheelDiameterCM(9.7);
		setUTURN(308);
		setPoint(154);
		setSpeed(10);
		setLeanSpeed(8);
		setSearchSpeed(6);
		setDist(3);
		setTapeThreasholdCM(2.0);//original value=2.5
		setSearchTime(2.5); //was 500
		checkSonar = true;
		setObstacleDistance(5.5);
}

//TASK MAIN//
task main()
{
	clearSounds();
	clearTimer(T1);
	properties();
	encoderArmUp(-135);
	startTask(display);
	repeat(forever)
	{
		if(checkSonar){
		avoidObstacle();
		}
		lineTracking();//basically the entire program
		//sweepRoom();
	}
}
