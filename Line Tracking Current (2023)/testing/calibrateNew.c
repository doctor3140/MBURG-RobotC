#pragma config(Sensor, S1,     rightS,         sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S2,     leftS,          sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S3,     reflect,        sensorEV3_Color)
#pragma config(Sensor, S4,     sonarSensor,    sensorEV3_Ultrasonic)
#pragma config(Motor,  motorA,          armMotor,      tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, driveRight, encoder)
#pragma config(Motor,  motorD,           ,             tmotorEV3_Large, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
// Use this program to calibrate values for robertTools.h library

float ltSpeed = 5;
float turnDist;

task display() //Display for Error Log
{
	repeat(forever){
		displayBigTextLine(2, "LCS: %d", getColorName(leftS));
		displayBigTextLine(4, "RCS: %d", getColorName(rightS));
		displayBigTextLine(6, "SS: %d", SensorValue[S4]);
		displayBigTextLine(8, "LeftM: %d", getMotorEncoder(leftMotor));
		displayBigTextLine(10, "RightM: %d", getMotorEncoder(rightMotor));
		displayBigTextLine(12, "Enc: %d", turnDist);
		sleep(20); //refreshrate in ms
	}
}

void keyMap(){
displayBigTextLine(2, "Calibrate Modes");
displayBigTextLine(4, "Left: %s", "CAL Left");
displayBigTextLine(6, "Right: %s", "CAL Right");
displayBigTextLine(8, "Down: %s", "CAL uTurn");
}
void rsMotors(){
	resetMotorEncoder(motorB);
	resetMotorEncoder(motorC);
}
void STP(){//Stop
	motor[motorB] = 0;
	motor[motorC] = 0;
}

void leftMotorMove(){
	motor[leftMotor]=(-ltSpeed);
	motor[rightMotor]=(ltSpeed);
}
void rightMotorMove(){
	motor[leftMotor]=(ltSpeed);
	motor[rightMotor]=(-ltSpeed);
}

void leftCalibrate(){
	startTask(display);
	sleep(200);
	playSound(soundFastUpwardTones);//Start of experiment
	sleep(500);
	while(getColorName(leftS) == colorWhite){
		leftMotorMove();
	}
	STP();
	while(getColorName(rightS) == colorWhite){
		leftMotorMove();			
	}
	STP();
}


void rightCalibrate(){
	startTask(display);
	sleep(200);
	playSound(soundFastUpwardTones);//Start of experiment
	sleep(500);
	while(getColorName(rightS) == colorWhite){
		rightMotorMove();
	}
	STP();
	while(getColorName(leftS) == colorWhite){
		rightMotorMove();			
	}
	STP();
}

task main(){
	rsMotors();
	rsMotors();
	keyMap();
	repeat(forever){
		if(getButtonPress(buttonLeft)){
			//leftCalibrate();
		}
		if(getButtonPress(buttonRight)){
			rightCalibrate();
		}
		if(getButtonPress(buttonDown)){
			//leftCalibrate();
		}
		sleep(300);
	}
}
//Result LeftTurn 332 degrees
//uTurn 660 degrees
//if(getButtonPress(buttonUp))
