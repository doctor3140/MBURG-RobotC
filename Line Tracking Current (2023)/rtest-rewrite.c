#pragma config(Sensor, S1,     rightS,         sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S2,     leftS,          sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S3,     reflect,        sensorEV3_Color)
#pragma config(Sensor, S4,     sonarSensor,    sensorEV3_Ultrasonic)
#pragma config(Motor,  armMotor,          armMotor,      tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  leftMotor,          leftMotor,     tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  rightMotor,          rightMotor,    tmotorEV3_Large, PIDControl, driveRight, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

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

CHANGELOG!! 2/9/23

Changed LTRight and LTRLeft to use opposite color sensors

Changed tapeThreashold from 80 to 120


*/

int m = -1; // for motor vector

float speed = 4.5; //10 old //7.5 OG
float leanSpeed = 6;
float ltSpeed = 3;

int searchTime = 1000*4; //Time for SLT & SRT (was 1k)Ft
int tapeThreashold = 120; //Width of Green tape (how far it needs to move forward to detect the black line in lilup //OG is 40 //60
int uTurnValue = 680; //for uturns when two greens are detected //OG 185 //newscrap 155

int face = 320; // for faceLeft & faceRight //OG is m*190 (-320 total for big) //newscrap 160
int point = 700; // for leftPointTurn & rightPointTurn //OG is m*320 (-760 for big)

//variables for obstacle
bool hasObstacle = false;

//features
bool checkGreen = true; //to enable/disable lilcheck function
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
	sleep(20);
	}
}

void leanLeft(){
		motor[leftMotor]=(-speed*m);
		motor[rightMotor]=(speed*m);
}
void leanRight(){
		motor[leftMotor]=(speed*m);
		motor[rightMotor]=(-speed*m);
}


void leftMotorMove(){
		motor[leftMotor]=(-ltSpeed*m);
		motor[rightMotor]=(ltSpeed*m);
}
void rightMotorMove(){
		motor[leftMotor]=(ltSpeed*m);
		motor[rightMotor]=(-ltSpeed*m);
}

//Arm Down//
void armDown()
{
	resetMotorEncoder(armMotor);
	setMotorTarget(armMotor, -70, 25);
	waitUntilMotorStop(armMotor);
	sleep(500);
}
//Arm Up//
void armUp()
{
	resetMotorEncoder(armMotor);
	setMotorTarget(armMotor, 70, 25);
	waitUntilMotorStop(armMotor);
	sleep(500);
}


void STP()
{
	motor[leftMotor]=0;
	motor[rightMotor]=0;
}

void lilUp()
{
	resetMotorEncoder(leftMotor);
	resetMotorEncoder(rightMotor);
	setMotorTarget(leftMotor, m*40, speed);
	setMotorTarget(rightMotor, m*40, speed);
	waitUntilMotorStop(rightMotor);
	sleep(1000);
}


void lilUp(int d)
{
	resetMotorEncoder(leftMotor);
	resetMotorEncoder(rightMotor);
	setMotorTarget(leftMotor, m*d, speed);
	setMotorTarget(rightMotor, m*d, speed);
	waitUntilMotorStop(rightMotor);
	sleep(1000);
}


void lilBack(int d)
{
	resetMotorEncoder(leftMotor);
	resetMotorEncoder(rightMotor);
	setMotorTarget(leftMotor, m*-d, speed);
	setMotorTarget(rightMotor, m*-d, speed);
	waitUntilMotorStop(rightMotor);
	sleep(1000);
}


// 230 is for new robot; 198/ 184 is for old robot; 375 is for point turn
void faceLeft()
{
	resetMotorEncoder(leftMotor);
	resetMotorEncoder(rightMotor);
	setMotorTarget(leftMotor, face, 25);
	setMotorTarget(rightMotor, -face, 25);
	waitUntilMotorStop(rightMotor);
	sleep(1000);
}
void faceRight()
{
	resetMotorEncoder(leftMotor);
	resetMotorEncoder(rightMotor);
	setMotorTarget(leftMotor, -face, 25);
	setMotorTarget(rightMotor, face, 25);
	waitUntilMotorStop(rightMotor);
	sleep(1000);
}


void uTurn()
{
	STP();
	sleep(500);

	resetMotorEncoder(leftMotor);
	resetMotorEncoder(rightMotor);
	setMotorTarget(leftMotor, -uTurnValue, 30);
	setMotorTarget(rightMotor, uTurnValue, 30);
	waitUntilMotorStop(rightMotor);
	sleep(1000);

}

void LTLeft()
{
	clearTimer(T1);
	while (time1[T1] < searchTime) //need to find better timing method/boot-out. Consult WindSprints for better bootout
	{
		if ((getColorName(rightS)==colorWhite)) //was right
		{
			leftMotorMove();
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
		rightMotorMove();
	}
}


void LTRight()
{
	playSound(soundBlip);
	clearTimer(T1);
	while (time1[T1] < searchTime) //need to find better timing method/boot-out. Consult WindSprints for better bootout
	{
		if ((getColorName(leftS)==colorWhite)) //was left
		{
			rightMotorTurn();
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
		leftMotorTurn();
		//startTask(display);
		//playSound(soundBlip);
	}
}

	//this is awful, please fix


void leftTurn()
{
	STP();
	sleep(200); //was 500
	lilUp(tapeThreashold);
	if (getColorName(leftS)==colorBlack) //was leftS, but since leftS is Right then it should be rightS nvm???
	{
		lilUp(40);
		faceLeft();
		if(checkTurnFurther && (getColorName(leftS)==colorWhite)){
		LTLeft();
		}
		lilUp(20);
		sleep(20);
	}
	else{
		lilUp(tapeThreashold);
	}
}

void rightTurn()
{
	STP();
	sleep(200);
	lilUp(tapeThreashold); //Turn off if momentum is too much
	if (getColorName(rightS)==colorBlack) //was rightS, but since rightS is Left then it should be leftS nvm???
	{
		lilUp(40);
		faceRight();
		if(checkTurnFurther && (getColorName(rightS)==colorWhite)){
		LTRight();
		}
		lilUp(20);
		sleep(20);
	}
	else{
		lilUp(tapeThreashold);
	}
}


//Turns left until sensor sees black or timer runs out and doubles back right
//made for double black and as fail safe when leanDetect fails


void lilcheck(bool leftIsTrue)
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
			lilcheck(true);
			if (!checkGreen)
			{
				leftTurn();
			}
		}
		else if ((getColorName(leftS)!=colorGreen) && (getColorName(rightS)==colorGreen)) //right green -> turnRight
		{
			lilcheck(false);
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
			lilUp(130);//OG 70
			LTRight();
		}
	else if (getColorName(rightS)==colorBlack) // lean left
	{
		leanLeft();

		if ((getColorName(rightS)==colorBlack)&&(getColorName(leftS)==colorBlack))//Zig and Intersection
		{
			lilUp(130);//OG 70
			LTRight();
		}
	}

	else if (getColorName(leftS)==colorBlack) // lean right
	{
		leanRight();

		if ((getColorName(rightS)==colorBlack)&&(getColorName(leftS)==colorBlack))//Zig and Intersection for LT
		{
			lilUp(70);
			LTLeft();
		}
	}

	else if ((getColorName(rightS)==colorWhite)&&(getColorName(leftS)==colorWhite)) //both white -> move in straight line
	{
		motor[leftMotor]= speed;
		motor[rightMotor]= speed;
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


//TASK MAIN//
task main()
{
	//armUp();
	clearSounds();
	clearTimer(T1);
	startTask(display);
	repeat(forever)
	{
		lineTracking();//basically the entire program
		//avoidObstacle();
		//sweepRoom();
	}

}
