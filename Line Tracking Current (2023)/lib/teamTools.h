// This is a library made for robotc to quickstart development on basic tasks.
// Developed by Selena Feng and Robert Sellery
// may also have to add #define in main program for movement to work. Requires testing

/* NOTICE: It is not recommended to change the variables directly. Please use getter and setter methods/functions! */

int m = 1; // for motor direction
float wheelDiameter = 2.5; //diameter of wheel in cm
int a = 1; //for arm direction

float speed = 20;
float ltSpeed = 6; //the speed for line tracking
float searchSpeed = 3; //the search speed for when the black line is lost

int searchTime = 1000*4; //Time for SLT & SRT (was 1k)Ft
float tapeThreashold = 120; //Width of Green tape (how far it needs to move forward to detect the black line in lilup. Consider making an array with a low and high distance as well as making a blackTape var.
int uTurnValue = 680; //for uturns when two greens are detected //OG 185 //newscrap 155

int point = 700; // for leftPointTurn & rightPointTurn //OG is m*320 (-760 for big)

// Setter methods should be called at the beggining of your main proram in order to set values of variables used in other functions.

setMotorDirection(char direction){
	if(direction=='f'){
	m = 1;
	}
	else if(direction=='b'){
	m = -1;
	}
	else{
		displayBigTextLine(2, "X setMotorDirection");
	}
}//'f' for foward 'b' for backward. This is used if you have a gear ratio that inverts the diection of the motors

setWheelDiameterCM(float diameter){
	wheelDiameter=diameter;
}

setUTURN(int encoder){
	uTurnValue=encoder;
}

setPoint(int encoder){
	point=encoder;
}

setSpeed(float spd){
	speed=spd;
}

setLTSpeed(float spd){
	ltSpeed=spd;
}

setSearchSpeed(float spd){
	SearchSpeed=spd;
}

setSearchTime(int time){
	searchTime=time;
}

setTapeThreasholdCM(float CM){
	tapeThreasholdCM=CM;
}

setArmSpeed(int arm){
	armSpeed=arm;
}



//getter functions
float getWheelDiameterCM(){
	return wheelDiameter;
}

int getUTURN(){
	return uTurnValue;
}

int getPoint(){
	return point;
}

float getSpeed(){
	return speed;
}

float getLTSpeed(){
	return ltSpeed;
}

float getSearchSpeed(){
	return searchSpeed;
}

int getSearchTime(){
	return searchTime;
}

float getTapeThreasholdCM(){
	return tapeThreasholdCM;
}

int getArmSpeed(){
	return armSpeed;
}

float cmConvertToMotorEncoder(float CM){
	return cm/(PI*wheelDiameter)*360;
}

float motorEncoderConvertToCM(float motorEncoder){
	return motorEncoder/360*PI*wheelDiameter;
}



//functions
void STP(){
	motor[leftMotor]=0;
	motor[rightMotor]=0;
}

void motorFoward(){
	motor[leftMotor] = (speed*m);
	motor[rightMotor] = (speed*m);
}

void motorFoward(float spd){
	motor[leftMotor] = (spd*m);
	motor[rightMotor] = (spd*m);
}

void encoderFoward(){
	resetMotorEncoder(leftMotor);
	resetMotorEncoder(rightMotor);
	setMotorTarget(leftMotor, 40*m, speed);
	setMotorTarget(rightMotor, 40*m, speed);
	waitUntilMotorStop(rightMotor);
	sleep(1000);
}

void encoderFoward(float CM){
	resetMotorEncoder(leftMotor);
	resetMotorEncoder(rightMotor);
	setMotorTarget(leftMotor, cmConvertToMotorEncoder(CM)*m, speed);
	setMotorTarget(rightMotor, cmConvertToMotorEncoder(CM)*m, speed);
	waitUntilMotorStop(rightMotor);
	sleep(1000);
}

void motorBackward(){
	motor[leftMotor] = (-speed*m);
	motor[rightMotor] = (-speed*m);
}

void motorBackward(float spd){
	motor[leftMotor] = (-spd*m);
	motor[rightMotor] = (-spd*m);
}

void encoderBackward(){
	resetMotorEncoder(leftMotor);
	resetMotorEncoder(rightMotor);
	setMotorTarget(leftMotor, -40*m, speed);
	setMotorTarget(rightMotor, -40*m, speed);
	waitUntilMotorStop(rightMotor);
	sleep(1000);
}

void encoderBackward(float CM){
	resetMotorEncoder(leftMotor);
	resetMotorEncoder(rightMotor);
	setMotorTarget(leftMotor, -cmConvertToMotorEncoder(CM)*m, speed);
	setMotorTarget(rightMotor, -cmConvertToMotorEncoder(CM)*m, speed);
	waitUntilMotorStop(rightMotor);
	sleep(1000);
}

void motorLTLeft(){
		motor[leftMotor]=(-ltSpeed*m);
		motor[rightMotor]=(ltSpeed*m);
}

void motorLTLeft(float spd){
		motor[leftMotor]=(-spd*m);
		motor[rightMotor]=(spd*m);
}

void motorLTRight(){
		motor[leftMotor]=(ltSpeed*m);
		motor[rightMotor]=(-ltSpeed*m);
}

void motorLTRight(float spd){
		motor[leftMotor]=(spd*m);
		motor[rightMotor]=(-spd*m);
}

void motorSearchLeft(){
		motor[leftMotor]=(-searchSpeed*m);
		motor[rightMotor]=(searchSpeed*m);
}

void motorSearchLeft(float spd){
		motor[leftMotor]=(-spd*m);
		motor[rightMotor]=(spd*m);
}

void motorSearchRight(){
		motor[leftMotor]=(searchSpeed*m);
		motor[rightMotor]=(-searchSpeed*m);
}

void motorSearchRight(float spd){
		motor[leftMotor]=(spd*m);
		motor[rightMotor]=(-spd*m);
}

void armUp(){
	motor[armMotor]=(armSpeed*a);
}

void armDown(){
	motor[armMotor]=(-armSpeed*a);
}
