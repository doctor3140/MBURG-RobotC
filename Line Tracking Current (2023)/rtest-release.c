#pragma config(Sensor, S1,     rightS,         sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S2,     leftS,          sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S3,     reflect,        sensorEV3_Color)
#pragma config(Sensor, S4,     sonarSensor,    sensorEV3_Ultrasonic)
#pragma config(Motor,  motorA,          armMotor,      tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, driveRight, encoder)
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

float m = -1; // for motor vector

int spd = 2;

float fSpeed = m*4.5*spd; //10 old //7.5 OG

float speed1 = m*6; //for leaning (Ussually 20 for Bot1) //20 old
float speed2 = m*-6; //for leaning (Ussually -10 for Bot1) //-10 old
float speed3 = m*-3*spd; //for SLT & SRT foward moving wheel (ussually 20) //10 old
float speed4 = m*3*spd; //for SLT & SRT backward moving wheel (ussually 0) //-10 old
float searchTime = 1000*4; //Time for SLT & SRT (was 1k)Ft
int error = 0; //For the amount of errors?
int Message[6]; //Array made for displaying errors or messages
int dumbError = 0; //dumb way of displaying errors
int tapeThreashold = 120; //Width of Green tape (how far it needs to move forward to detect the line in lilup //OG is 40 //60
int uTurnValue = m*680; //for uturns when two greens are detected //OG 185 //newscrap 155

int face = m*-320; // for faceLeft & faceRight //OG is m*190 (-320 total for big) //newscrap 160
int point = m*-700; // for leftPointTurn & rightPointTurn //OG is m*320 (-760 for big)
int obstacleDistance = 5; // for the value that the robot distinguishes if there is an obstacle in front of it
//variables for obstacle
bool hasObstacle = false;
bool leftBlack = false;
bool rightBlack = false;

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
/*
task display() //Display for Error Log
{
	displayBigTextLine(2, "1st Error: %d", Message[0]);
	displayBigTextLine(4, "2nd Error: %d", Message[1]);
	displayBigTextLine(6, "3rd Error: %d", Message[2]);
	displayBigTextLine(8, "Time: %d", time1[T1]);
	displayBigTextLine(10, "Direction: %d", direction);
	displayBigTextLine(12, "Last Error: %d", Message[5]);
}
*/
task display() //Display for Error Log
{
	displayBigTextLine(2, "LCS: %d", getColorName(leftS));
	displayBigTextLine(4, "RCS: %d", getColorName(rightS));
	displayBigTextLine(6, "SS: %d", SensorValue[S4]);
	displayBigTextLine(8, "MotorB: %d", getMotorEncoder(motorB));
	displayBigTextLine(10, "MotorC: %d", getMotorEncoder(motorC));
	displayBigTextLine(12, "Last Error: %d", Message[5]);
}


void messagelogic(int x) //input errormessage number -> Fills in Array for Error message Display
{
	if (error == 1)
	{
		Message[0] = x;
	}
	else if (error == 2)
	{
		Message[1] = x;
	}
	else if (error == 3)
	{
		Message[2] = x;
	}
	else if (error == 4)
	{
		Message[3] = x;
	}
	/*
	else if (error == 5)
	{
	Message[4] = x;
	}
	*/
	else if (error >= 5) //was else if (error == 5) before timer
	{
		Message[5] = x;
	}
	else
	{
		return; //use break instead of return
	}
}

void leftMotorMove(){
		motor[motorB]=speed3;
		motor[motorC]=speed4;
}
void rightMotorMove(){
		motor[motorB]=speed4;
		motor[motorC]=speed3;
}

//Arm Down//
void armDown()
{
	resetMotorEncoder(motorA);
	setMotorTarget(motorA, -70, 25);
	waitUntilMotorStop(motorA);
	sleep(500);
}
//Arm Up//
void armUp()
{
	resetMotorEncoder(motorA);
	setMotorTarget(motorA, 70, 25);
	waitUntilMotorStop(motorA);
	sleep(500);
}

void errormessage(int x)
{
	setLEDColor(ledRedFlash);
	//playTone();
	if (x >= 1)
	{
		error++;
		messagelogic(x);
		startTask(display);
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
{
	resetMotorEncoder(motorB);
	resetMotorEncoder(motorC);
	setMotorTarget(motorB, m*d, 30);
	setMotorTarget(motorC, m*d, 30);
	waitUntilMotorStop(motorC);
	sleep(1000);
}


void lilBack(int d)
{
	resetMotorEncoder(motorB);
	resetMotorEncoder(motorC);
	setMotorTarget(motorB, m*-d, 10);
	setMotorTarget(motorC, m*-d, 10);
	waitUntilMotorStop(motorC);
	sleep(1000);
}


// 230 is for new robot; 198/ 184 is for old robot; 375 is for point turn
void faceLeft()
{
	resetMotorEncoder(motorB);
	resetMotorEncoder(motorC);
	setMotorTarget(motorB, face, 25);
	setMotorTarget(motorC, -face, 25);
	waitUntilMotorStop(motorC);
	sleep(1000);
}
void faceRight()
{
	resetMotorEncoder(motorB);
	resetMotorEncoder(motorC);
	setMotorTarget(motorB, -face, 25);
	setMotorTarget(motorC, face, 25);
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

		while (getMotorEncoder(motorB) >= -1300) //RS confused at "do" Statement
		{
			do
			{
				motor[motorB]=-15;
				motor[motorC]=-15;
			}	while ((getColorName(rightS)!=colorBlack)&&(getColorName(rightS)!=colorBlack));
			break;
		}

		while ((getColorName(rightS)!=colorBlack)&&(getColorName(rightS)!=colorBlack))

		STP();
		sleep(500);
		if ((getColorName(rightS) == colorBlack && getColorName(rightS) == colorBlack))
		{
			lilUp(100);
			faceLeft();
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
			}	while ((getColorName(rightS)!=colorBlack)&&(getColorName(leftS)!=colorBlack));
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
			}	while ((getColorName(rightS)!=colorBlack)&&(getColorName(leftS)!=colorBlack));
		}

			STP();
			sleep(500);
			lilUp(100);
			sleep(500);
			faceLeft();
			lilUp();
	}
}


void uTurn()
{
	STP();
	sleep(500);

	resetMotorEncoder(motorB);
	resetMotorEncoder(motorC);
	setMotorTarget(motorB, m*-uTurnValue, 30);
	setMotorTarget(motorC, m*uTurnValue, 30);
	waitUntilMotorStop(motorC);
	sleep(1000);

}

void LTLeft()
{
	clearTimer(T1);
	while (time1[T1] < searchTime) //need to find better timing method/boot-out. Consult WindSprints for better bootout
	{
		if ((getColorName(rightS)==colorWhite)) //was right
		{
			motor[motorB]=speed3;
			motor[motorC]=speed4;
			startTask(display);
			//playSound(soundBlip);
		}
		else if(getColorName(rightS)==colorBlack)
		{
			//playSound(soundLowBuzzShort);
			STP();
			sleep(200);

		}
	}

	while ((getColorName(leftS)!=colorBlack)) //change to ==white if no work (most likely redundent remove cmt after testing)
	{
		motor[motorB]=speed4;
		motor[motorC]=speed3;
		startTask(display);
		//playSound(soundBlip);
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
			motor[motorB]=speed4;
			motor[motorC]=speed3;
			startTask(display);
			//playSound(soundBlip);
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
		motor[motorB]=speed3;
		motor[motorC]=speed4;
		startTask(display);
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
		resetMotorEncoder(motorB);
		resetMotorEncoder(motorC);
		setMotorTarget(motorC, m*20, 10);
		waitUntilMotorStop(motorC);
		if (getColorName(rightS)==colorGreen)
		{
			setMotorTarget(motorC, 0, 10); //Was motorC, but seemed to be moving wrong direction
			waitUntilMotorStop(motorC);
			STP();
			uTurn();
		}
		else
		{
			setMotorTarget(motorC, 0, 10);  //Was motorC, but seemed to be moving wrong direction (what is this do)
			waitUntilMotorStop(motorC);
			leftTurn();
		}
	}
	else
	{
		resetMotorEncoder(motorB);
		resetMotorEncoder(motorC);
		setMotorTarget(motorB, m*20, 10);
		waitUntilMotorStop(motorB);

		if (getColorName(leftS)==colorGreen)
		{
			setMotorTarget(motorB, 0, 10); //Was motorB, but seemed to be moving wrong direction
			waitUntilMotorStop(motorC);
			STP();
			uTurn();
		}
		else
		{
			setMotorTarget(motorB, 0, 10);
			waitUntilMotorStop(motorC);
			rightTurn();
		}
	}
}
}






void lineTracking()
{
	startTask(display); //to aid in refresh rate of display

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
		if ((getColorName(leftS)==colorGreen)&&(getColorName(rightS)==colorGreen)) //both green -> Uturn
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
			dumbError = 1;
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
		motor[motorB]=speed1;
		motor[motorC]=speed2;

		if ((getColorName(rightS)==colorBlack)&&(getColorName(leftS)==colorBlack))//Zig and Intersection
		{
			lilUp(130);//OG 70
			LTRight();
		}
	}

	else if (getColorName(leftS)==colorBlack) // lean right
	{
		motor[motorB]=speed2;
		motor[motorC]=speed1;

		if ((getColorName(rightS)==colorBlack)&&(getColorName(leftS)==colorBlack))//Zig and Intersection for LT
		{
			lilUp(70);
			LTLeft(); //leanDetect is useful for on the fly changes?
		}
	}

	else if ((getColorName(rightS)==colorWhite)&&(getColorName(leftS)==colorWhite)) //both white -> move in straight line
	{
		motor[motorB]= fSpeed;
		motor[motorC]= fSpeed;
	}

	else // problem/unkown -> error sign
	{
		//errormessage(1);
		dumbError = 1;
		//Unknown Color
	}
	checkObstacle(5);
}




void findLine()
{
	clearTimer(T2);
	while (time1[T2] < 3000)
	{
		do
		{
			motor[motorB]= 10;
			motor[motorC]= -10;
		} while (getColorName(leftS) != colorBlack && getColorName(leftS) != colorBlack );
		return;
	}
	clearTimer(T2);
	while (time1[T2] < 3000)
	{
		do
		{
			motor[motorB]= -10;
			motor[motorC]= 10;
		} while (getColorName(leftS) != colorBlack && getColorName(leftS) != colorBlack );
		return;
	}
}

// this is the method for robot to find the black line when going out from the room. If turn left and right to check for black. If there's black, return to lineTracking.


int direction1[4];

int direction2[4];

// we store the room situation in those two arrays
//  0     1      2    3
// posX, posY, negX, negY
// the number in array stands for four direction.


void getRoom1()
{
	for (int i= 0; i < 4; i++)
	{
		sleep(300);
		if (getUSDistance(S4) > 100) // find the way without exit
		{
			direction1[i] = 5; // exit
		}
		else if (getUSDistance(S4) < 95 &&  getUSDistance(S4) > 90)
		{
			direction1[i] = 4;
		}
		else if (getUSDistance(S4) < 75 &&  getUSDistance(S4) > 70) // find the way without exit
		{
			direction1[i] = 3;
		}
		else if (getUSDistance(S4) < 70 &&  getUSDistance(S4) > 65) // find the way without exit
		{
			direction1[i] = 2;
		}
		else if (getUSDistance(S4) < 45 &&  getUSDistance(S4) > 40) // find the way without exit
		{
			direction1[i] = 1;
		}
		else
		{
			direction1[i] = 0;
		}
		faceRight();
		lilBack(40);
		sleep(500);
		lilUp(30);
	}
}

void getRoom2()
{
	for (int i= 0; i < 4; i++)
	{
		sleep(300); //why return??
		if (getUSDistance(S4) > 100) // find the way without exit
		{
			direction2[i] = 5; // exit
		}
		else if (getUSDistance(S4) < 95 &&  getUSDistance(S4) > 90)
		{
			direction2[i] = 4;
		}
		else if (getUSDistance(S4) < 75 &&  getUSDistance(S4) > 70) // find the way without exit
		{
			direction2[i] = 3;
		}
		else if (getUSDistance(S4) < 70 &&  getUSDistance(S4) > 65) // find the way without exit
		{
			direction2[i] = 2;
		}
		else if (getUSDistance(S4) < 45 &&  getUSDistance(S4) > 40) // find the way without exit
		{
			direction2[i] = 1;
		}
		else
		{
			direction2[i] = 0;
		}
		faceRight();
		lilBack(40);
		sleep(500);
		lilUp(30);
	}
}



void sweepRoom()
{

	if (getColorReflected(S3)>=50) // enter rescue room
	{

		STP();
		sleep(300);
		lilUp(175);
		armDown();
		clearTimer(T2);

		// < 10 wall 0
		// 40-45 short edge with box 1
		// 65-70 short edge without box 2
		// 70 - 75 long edge with box 3
		// 90 - 95 long edge without box 4
		// > 100 exit 5

		// those number are for level 2. For level one, only 5 are useful.

		hasObstacle = false;


		getRoom1(); // look around the room, store the situation.

		for (int i = 0; i < 4; i++)
		{
			if (direction1[i] == 5 && i != 2) // !=2 means not going back the entrance.
			{
				repeat(i)
				{
					faceRight();
					lilBack(70);
					sleep(500);
					lilUp();
				}
				do{
					motor[motorB]= -30;
					motor[motorC]= -30;
				} while (!(getColorName(rightS) == colorGreen && getColorName(leftS) == colorGreen));
				STP();
				lilUp(100);
				findLine();
				return; //why return??
			}
		}

		// if there's an exit, turn to that side, and go out.

		do{
			motor[motorB]= -30;
			motor[motorC]= -30;
		} while (getUSDistance(S4) > 15);

		STP();
		sleep(500);

		// go straight

		getRoom2(); // check room again at this location.

		// two checks can guarantee the location of exit.


		for (int i = 0; i < 4; i++)
		{
			if (direction2[i] == 5 && i != 2)
			{
				repeat(i)
				{
					faceRight();
					lilBack(70);
					sleep(500);
					lilUp(40);
				}
				do{
					motor[motorB]= -30;
					motor[motorC]= -30;
				} while (!(getColorName(rightS) == colorGreen && getColorName(leftS) == colorGreen));
				STP();
				lilUp(100);
				findLine();
				return;
			}
		}

		// turn to the exit direction, and go out.


		faceRight();
		lilBack(50);
		sleep(500);
		lilUp();
		if (getUSDistance(S4) > 15)
		{
			do{
				motor[motorB]= -30;
				motor[motorC]= -30;
			} while (getUSDistance(S4) > 15);
			faceRight();
			lilBack(70);
			sleep(500);
			lilUp(50);
			do{
				motor[motorB]= -30;
				motor[motorC]= -30;
			} while (!(getColorName(rightS) == colorGreen && getColorName(leftS) == colorGreen));
			STP();
			lilUp(100);
			findLine();
			return;
		}
		else
		{
			uTurn();
			lilBack(70);
			sleep(500);
			lilUp(40);
			do{
				motor[motorB]= -30;
				motor[motorC]= -30;
			} while (getUSDistance(S4) > 15);
			faceLeft();
			lilBack(70);
			sleep(500);
			lilUp(40);
			do{
				motor[motorB]= -30;
				motor[motorC]= -30;
			} while (!(getColorName(rightS) == colorGreen && getColorName(leftS) == colorGreen));
			STP();
			lilUp(100);
			findLine();
			return;
		}

		// if two check didn't see exit, that means the exit is on the same side as the entrance, so move to that direction, and go out.


		repeatUntil(getUSDistance(S4) > 100)
		{
			do{
				motor[motorB]= -30;
				motor[motorC]= -30;
			} while (getUSDistance(S4) > 15);
			clearTimer(T2);
			while (time1[T2] < 3000)
			{
				do
				{
					motor[motorB]= -15;
					motor[motorC]= 15;
				} while (getUSDistance(S4) > 100);

				do{
					motor[motorB]= -30;
					motor[motorC]= -30;
				} while (!(getColorName(rightS) == colorGreen && getColorName(leftS) == colorGreen));
				STP();
				lilUp(100);
				findLine();
				return;
			}
		}

		// back up code, go straight to the wall, turn around and see if there's an exit, if find exit go out, if not loop again.
	}
}





//TASK MAIN//
task main()
{
	//armUp();
	clearSounds();
	clearTimer(T1);
	repeat(forever)
	{
		while(SensorValue[S4] < obstacleDistance){

			lineTracking();//basically the entire program <-- no this is false
			//sweepRoom();
		}
		checkObstacle(obstacleDistance);
		avoidOBstacle();
	}

}
