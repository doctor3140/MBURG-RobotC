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
/*
the width and the height: 120 cm & 90 cm
you have to execute the code to check if there is a silver line before executing this file
*/
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

bool rightStart = true;

bool errorRescue = false;

void executeRescueRoom(){

}
task main()
{



}
