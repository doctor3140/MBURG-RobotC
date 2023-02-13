#pragma config(Sensor, S1,     leftS,          sensorEV3_Color, modeEV3Color_RGB_Raw)
#pragma config(Sensor, S2,     rightS,         sensorEV3_Color, modeEV3Color_RGB_Raw)
#pragma config(Sensor, S3,     ,               sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S4,     sonarSensor,    sensorEV3_Ultrasonic)
#pragma config(Motor,  motorA,          armMotor,      tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, driveRight, encoder)
task main(){
	string str1 = "hello";
	string str2 = "hello";

	if(stringFind(str1, "hello")>=0){
		playTone();
	}
	else{
	motor[leftMotor] = 50;
	}
}

//In this example since the string is within the other string the robot plays a tone

//*edit so that it uses length of string as well to actually verify equals
