// This is a library made for robotc to quickstart development on basic tasks.
// Developed by Selena Feng and Robert Sellery
// may also have to add #define in main program for movement to work. Requires testing

/* NOTICE: It is not recommended to change the variables directly. Please use getter and setter methods/functions! */

int m = 1; // for motor direction
float wheelDiameter = 5; //diameter of wheel in cm
int a = 1; //for arm direction

float speed = 20;
float armSpeed = 20;
float leanSpeed = 6; //the speed for double sensor lean line tracking
float searchSpeed = 3; //the search speed for when the black line is lost

float robotWidth = 13.6;
float robotLength = 17;

int searchTime = 4000; //Time for SLT & SRT (was 1k)Ft
float tapeThreasholdCM = 2.5; //Width of Green tape (how far it needs to move forward to detect the black line in lilup. Consider making an array with a low and high distance as well as making a blackTape var.
int uTurnValue = 680; //for uturns when two greens are detected //OG 185 //newscrap 155
float dist  = 2.5;

int point = 323; // for leftPointTurn & rightPointTurn //OG is m*320 (-760 for big)

// Setter methods should be called at the beggining of your main proram in order to set values of variables used in other functions.

float getRobotWidth(){
	return robotWidth;	
}

float getRobotLenght(){
	return robotLength;	
}

void setRobotWidth(float rw){
	robotWidth = rw;
}

void setRobotLength(float rl){
	robotLength = rl;
}

void setMotorDirection(char direction){
	if(direction=='f'){
	m = 1;
	}
	else if(direction=='b'){
	m = -1;
	}
	else{
		displayBigTextLine(2, "X setMotorDirection");
	}
}//'f' for Forward 'b' for backward. This is used if you have a gear ratio that inverts the diection of the motors

void setWheelDiameterCM(float diameter){
	wheelDiameter=diameter;
}

void setUTURN(int encoder){
	uTurnValue=encoder;
}

void setPoint(int encoder){
	point=encoder;
}

void setSpeed(float spd){
	speed=spd;
}

void setLeanSpeed(float spd){
	leanSpeed=spd;
}

void setSearchSpeed(float spd){
	searchSpeed=spd;
}

void setSearchTime(int sec){
	searchTime=(sec*1000);
}

void setTapeThreasholdCM(float CM){
	tapeThreasholdCM=CM;
}

void setArmSpeed(int arm){
	armSpeed=arm;
}

void setDist(float d){
	dist=d;
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

float getLeanSpeed(){
	return leanSpeed;
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

void motorForward(){
	motor[leftMotor] = (speed*m);
	motor[rightMotor] = (speed*m);
}

void motorForward(float spd){
	motor[leftMotor] = (spd*m);
	motor[rightMotor] = (spd*m);
}

void encoderForward(){
	resetMotorEncoder(leftMotor);
	resetMotorEncoder(rightMotor);
	setMotorTarget(leftMotor, cmConvertToMotorEncoder(dist)*m, speed);
	setMotorTarget(rightMotor, cmConvertToMotorEncoder(dist)*m, speed);
	waitUntilMotorStop(rightMotor);
	sleep(1000);
}

void encoderForward(float CM){
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
	setMotorTarget(leftMotor, -cmConvertToMotorEncoder(dist)*m, speed);
	setMotorTarget(rightMotor, -cmConvertToMotorEncoder(dist)*m, speed);
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

void motorLeanLeft(){
	motor[leftMotor]=(-leanSpeed*m);
	motor[rightMotor]=(leanSpeed*m);
}

void motorLeanLeft(float spd){
	motor[leftMotor]=(-spd*m);
	motor[rightMotor]=(spd*m);
}

void motorLeanRight(){
	motor[leftMotor]=(leanSpeed*m);
	motor[rightMotor]=(-leanSpeed*m);
}

void motorLeanRight(float spd){
	motor[leftMotor]=(spd*m);
	motor[rightMotor]=(-spd*m);
}

//going to test out different kinds of turns for motorSearch

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


void encoderPointLeft(){
	resetMotorEncoder(leftMotor);
	resetMotorEncoder(rightMotor);
	setMotorTarget(leftMotor, -point*m, speed);
	setMotorTarget(rightMotor, point*m, speed);
	waitUntilMotorStop(rightMotor);
	sleep(1000);
}

void encoderPointLeft(float CM){
	resetMotorEncoder(leftMotor);
	resetMotorEncoder(rightMotor);
	setMotorTarget(leftMotor, -cmConvertToMotorEncoder(CM)*m, speed);
	setMotorTarget(rightMotor, cmConvertToMotorEncoder(CM)*m, speed);
	waitUntilMotorStop(rightMotor);
	sleep(1000);
}

void encoderPointRight(){
	resetMotorEncoder(leftMotor);
	resetMotorEncoder(rightMotor);
	setMotorTarget(leftMotor, point*m, speed);
	setMotorTarget(rightMotor, -point*m, speed);
	waitUntilMotorStop(rightMotor);
	sleep(1000);
}
//don't really get the point of these. Make into function of arc length??
void encoderPointRight(float CM){
	resetMotorEncoder(leftMotor);
	resetMotorEncoder(rightMotor);
	setMotorTarget(leftMotor, cmConvertToMotorEncoder(CM)*m, speed);
	setMotorTarget(rightMotor, -cmConvertToMotorEncoder(CM)*m, speed);
	waitUntilMotorStop(rightMotor);
	sleep(1000);
}

void uTurn()
{
	STP();
	sleep(500);
	resetMotorEncoder(leftMotor);
	resetMotorEncoder(rightMotor);
	setMotorTarget(leftMotor, -uTurnValue, speed);
	setMotorTarget(rightMotor, uTurnValue, speed);
	waitUntilMotorStop(rightMotor);
	sleep(1000);
}

void motorArmUp(){
	motor[armMotor]=(armSpeed*a);
}

void motorArmDown(){
	motor[armMotor]=(-armSpeed*a);
}

void encoderArmDown()
{
	resetMotorEncoder(armMotor);
	setMotorTarget(armMotor, -70, speed);
	waitUntilMotorStop(armMotor);
	sleep(500);
}
void encoderArmUp()
{
	resetMotorEncoder(armMotor);
	setMotorTarget(armMotor, 70, speed);
	waitUntilMotorStop(armMotor);
	sleep(500);
}


//make above encoder functions work better
