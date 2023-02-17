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
bool checkGreen = false; //to enable/disable lilCheck function
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
	while (time1[T1] < getSearchTime()) //need to find better timing method/boot-out. Consult WindSprints for better bootout
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
}


void findLineRight()
{
	playSound(soundBlip);
	clearTimer(T1);
	while (time1[T1] < getSearchTime()) //need to find better timing method/boot-out. Consult WindSprints for better bootout
	{
		if ((getColorName(leftS)==colorWhite)) //was left
		{
			motorSearchRight();
			//startTask(display);
		}
		else if (getColorName(leftS)==colorBlack)
		{
			//playSound(soundLowBuzzShort);
			STP();
			sleep(200);
		}
	}
	while ((getColorName(rightS)!=colorBlack)) //change to ==white if no work (most likely redundent remove cmt after testing)
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
	encoderFoward(getTapeThreasholdCM());
	if (getColorName(leftS)==colorBlack) //was leftS, but since leftS is Right then it should be rightS nvm???
	{
		encoderFoward(8);
		encoderPointLeft();
		if(checkTurnFurther && (getColorName(leftS)==colorWhite)){
		findLineLeft();
		}
		encoderFoward();
		sleep(20);
	}
	else{
		encoderFoward(getTapeThreasholdCM());
	}
}

void rightTurn()
{
	STP();
	sleep(200);
	//playSound(soundBeepBeep);
	encoderFoward(getTapeThreasholdCM()); //Turn off if momentum is too much
	if (getColorName(rightS)==colorBlack) //was rightS, but since rightS is Left then it should be leftS nvm???
	{
		playSound(soundBeepBeep);
		encoderFoward(8);
		encoderPointRight();
		if(checkTurnFurther && (getColorName(rightS)==colorWhite)){
		findLineRight();
		}
		encoderFoward();
		sleep(20);
	}
	else{
		encoderFoward(getTapeThreasholdCM());
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
		//playSound(soundBlip);
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
			playTone();
		}
	}
if ((getColorName(rightS)==colorBlack)&&(getColorName(leftS)==colorBlack))//Zig and Intersection //Adddition
		{
			playTone();
			encoderFoward(5);//OG 70
			findLineRight();
		}
	else if (getColorName(rightS)==colorBlack) // lean left
	{
		motorLeanLeft();

		if ((getColorName(rightS)==colorBlack)&&(getColorName(leftS)==colorBlack))//Zig and Intersection
		{
			encoderFoward(5);//OG 70
			findLineRight();
		}
	}

	else if (getColorName(leftS)==colorBlack) // lean right
	{
		motorLeanLeft();

		if ((getColorName(rightS)==colorBlack)&&(getColorName(leftS)==colorBlack))//Zig and Intersection for LT
		{
			encoderFoward(5);
			findLineLeft();
		}
	}

	else if ((getColorName(rightS)==colorWhite)&&(getColorName(leftS)==colorWhite)) //both white -> move in straight line
	{
		motorFoward();
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
		setSpeed(10);
		setLeanSpeed(6);
		setSearchSpeed(3);
		setDist(2.5);
		setTapeThreasholdCM(5);
		setSearchSpeed(3);
		setSearchTime(4000);
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
