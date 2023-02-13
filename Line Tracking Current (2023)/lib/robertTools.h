// This is a library made for robotc to quickstart development on basic tasks.
// Developed by Robert Sellery
// may also have to add #define in main program for movement to work. Requires testing

/* NOTICE: It is not recommended to change the variables directly. Please use getter and setter methods/functions! */

int m = 1; // for motor direction
float wheelDiameter = 2.5; //diameter of wheel in cm

float speed = 20;
float leanSpeed = 6;
float ltSpeed = 3;

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

setLeanSpeed(float spd){
	leanSpeed=spd;
}

setLTSpeed(float spd){
	ltSpeed=spd;
}

setSearchTime(int time){
	searchTime = time;
}
setTapeThreasholdCM(float CM){

}

void moveFoward(){
motor[leftMotor] = (speed*m);
motor[rightMotor] = (speed*m);
}
