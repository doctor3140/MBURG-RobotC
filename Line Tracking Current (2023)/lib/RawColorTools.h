int currentRight[3]= {
		{0, 0, 0}
};
int currentLeft[3]= {
		{0, 0, 0}
};
//Base values if using colorMargin()
int blackRightBase[3]= {
	  {18, 32, 9}
};
int whiteRightBase[3]= {
	  {250, 22, 157}
};
int greenRightBase[3]= {
	  {50, 131, 26}
};
int redRightBase[3]= {
	  {240, 47, 16}
};

int blackLeftBase[3]= {
	  {25, 40, 18}
};
int whiteLeftBase[3]= {
	  {235, 273, 192}
};

int greenLeftBase[3]= {
	  {55, 136, 31}
};

int redLeftBase[3]= {
	  {220, 51, 24}
};

//Values for fine tweaking otherwise
int blackRight[2][3]= {
		{13, 28, 4},
	  {23, 37, 14}
};
int whiteRight[2][3]= {
		{245, 260, 152},
	  {255, 270, 162}
};
int greenRight[2][3]= {
		{22, 87, 27},
	  {55, 136, 31}
};
int redRight[2][3]= {
		{235, 42, 11},
	  {245, 52, 21}
};


int blackLeft[2][3]= {
		{20, 35, 13},
	  {30, 45, 23}
};
int whiteLeft[2][3]= {
		{230, 268, 187},
	  {240, 278, 198}
};
int greenLeft[2][3]= {
		{18, 90, 28},
	  {54, 138, 33}
};
int redLeft[2][3]= {
		{215, 46, 19},
	  {225, 56, 29}
};

int test[2][3]= {
		{0, 0, 0},
	  {0, 0, 0}
};

//might add setter methods if deemed necessary, but honestly seems kinda annoying tbh

bool rightEqualsBlack(){
getColorRawRGB(rightS, currentRight[0], currentRight[1], currentRight[2]);
if(((blackRight[0][0]<=currentRight[0])&&(currentRight[0]<=blackRight[1][0]))&&((blackRight[0][1]<=currentRight[1])&&(currentRight[1]<=blackRight[1][1]))&&((blackRight[0][2]<=currentRight[2])&&(currentRight[2]<=blackRight[1][2]))){
	return true;
}
else{
	return false;
}
}

bool leftEqualsBlack(){
getColorRawRGB(leftS, currentLeft[0], currentLeft[1], currentLeft[2]);
if(((blackLeft[0][0]<=currentLeft[0])&&(currentLeft[0]<=blackLeft[1][0]))&&((blackLeft[0][1]<=currentLeft[1])&&(currentLeft[1]<=blackLeft[1][1]))&&((blackLeft[0][2]<=currentLeft[2])&&(currentLeft[2]<=blackLeft[1][2]))){
	return true;
}
else{
	return false;
}
}

bool rightEqualsWhite(){
getColorRawRGB(rightS, currentRight[0], currentRight[1], currentRight[2]);
if(((whiteRight[0][0]<=currentRight[0])&&(currentRight[0]<=whiteRight[1][0]))&&((whiteRight[0][1]<=currentRight[1])&&(currentRight[1]<=whiteRight[1][1]))&&((whiteRight[0][2]<=currentRight[2])&&(currentRight[2]<=whiteRight[1][2]))){
	return true;
}
else{
	return false;
}
}

bool leftEqualsWhite(){
getColorRawRGB(leftS, currentLeft[0], currentLeft[1], currentLeft[2]);
if(((whiteLeft[0][0]<=currentLeft[0])&&(currentLeft[0]<=whiteLeft[1][0]))&&((whiteLeft[0][1]<=currentLeft[1])&&(currentLeft[1]<=whiteLeft[1][1]))&&((whiteLeft[0][2]<=currentLeft[2])&&(currentLeft[2]<=whiteLeft[1][2]))){
	return true;
}
else{
	return false;
}
}

bool rightEqualsGreen(){
getColorRawRGB(rightS, currentRight[0], currentRight[1], currentRight[2]);
if(((greenRight[0][0]<=currentRight[0])&&(currentRight[0]<=greenRight[1][0]))&&((greenRight[0][1]<=currentRight[1])&&(currentRight[1]<=greenRight[1][1]))&&((greenRight[0][2]<=currentRight[2])&&(currentRight[2]<=greenRight[1][2]))){
	return true;
}
else{
	return false;
}
}

bool leftEqualsGreen(){
getColorRawRGB(leftS, currentLeft[0], currentLeft[1], currentLeft[2]);
if(((greenLeft[0][0]<=currentLeft[0])&&(currentLeft[0]<=greenLeft[1][0]))&&((greenLeft[0][1]<=currentLeft[1])&&(currentLeft[1]<=greenLeft[1][1]))&&((greenLeft[0][2]<=currentLeft[2])&&(currentLeft[2]<=greenLeft[1][2]))){
	return true;
}
else{
	return false;
}
}

bool rightEqualsRed(){
getColorRawRGB(rightS, currentRight[0], currentRight[1], currentRight[2]);
if(((redRight[0][0]<=currentRight[0])&&(currentRight[0]<=redRight[1][0]))&&((redRight[0][1]<=currentRight[1])&&(currentRight[1]<=redRight[1][1]))&&((redRight[0][2]<=currentRight[2])&&(currentRight[2]<=redRight[1][2]))){
	return true;
}
else{
	return false;
}
}

bool leftEqualsRed(){
getColorRawRGB(leftS, currentLeft[0], currentLeft[1], currentLeft[2]);
if(((redLeft[0][0]<=currentLeft[0])&&(currentLeft[0]<=redLeft[1][0]))&&((redLeft[0][1]<=currentLeft[1])&&(currentLeft[1]<=redLeft[1][1]))&&((redLeft[0][2]<=currentLeft[2])&&(currentLeft[2]<=redLeft[1][2]))){
	return true;
}
else{
	return false;
}
}

void colorMarginBlack(int margin){
	blackLeft[0][0]=blackLeftBase[0]-margin;
	blackRight[0][0]=blackRightBase[0]-margin;
	blackLeft[0][1]=blackLeftBase[1]-margin;
	blackRight[0][1]=blackRightBase[1]-margin;
	blackLeft[0][2]=blackLeftBase[2]-margin;
	blackRight[0][2]=blackRightBase[2]-margin;

	blackLeft[0][0]=blackLeftBase[0]+margin;
	blackRight[0][0]=blackRightBase[0]+margin;
	blackLeft[0][1]=blackLeftBase[1]+margin;
	blackRight[0][1]=blackRightBase[1]+margin;
	blackLeft[0][2]=blackLeftBase[2]+margin;
	blackRight[0][2]=blackRightBase[2]+margin;
}

void colorMarginWhite(int margin){
	whiteLeft[0][0]=whiteLeftBase[0]-margin;
	whiteRight[0][0]=whiteRightBase[0]-margin;
	whiteLeft[0][1]=whiteLeftBase[1]-margin;
	whiteRight[0][1]=whiteRightBase[1]-margin;
	whiteLeft[0][2]=whiteLeftBase[2]-margin;
	whiteRight[0][2]=whiteRightBase[2]-margin;

	whiteLeft[0][0]=whiteLeftBase[0]+margin;
	whiteRight[0][0]=whiteRightBase[0]+margin;
	whiteLeft[0][1]=whiteLeftBase[1]+margin;
	whiteRight[0][1]=whiteRightBase[1]+margin;
	whiteLeft[0][2]=whiteLeftBase[2]+margin;
	whiteRight[0][2]=whiteRightBase[2]+margin;
}

void displayRightS(int line){
getColorRawRGB(rightS, currentRight[0], currentRight[1], currentRight[2]);
displayBigTextLine(line, "R: %d %d %d", currentRight[0], currentRight[1], currentRight[2]);
}

void displayLeftS(int line){
getColorRawRGB(leftS, currentLeft[0], currentLeft[1], currentLeft[2]);
displayBigTextLine(line, "L: %d %d %d", currentLeft[0], currentLeft[1], currentLeft[2]);
}

bool leftEqualsTest(){
if(((test[0][0]<=currentLeft[0])&&(currentLeft[0]<=test[1][0]))&&((test[0][1]<=currentLeft[1])&&(currentLeft[1]<=test[1][1]))&&((test[0][2]<=currentLeft[2])&&(currentLeft[2]<=test[1][2]))){
	return true;
}
else{
	return false;
}
}

bool rightEqualsTest(){
if(((test[0][0]<=currentRight[0])&&(currentRight[0]<=test[1][0]))&&((test[0][1]<=currentRight[1])&&(currentRight[1]<=test[1][1]))&&((test[0][2]<=currentRight[2])&&(currentRight[2]<=test[1][2]))){
	return true;
}
else{
	return false;
}
}



/*
void getRightS(){
getColorRawRGB(rightS, currentRight[0], currentRight[1], currentRight[2]);
}

void getLeftS(){
getColorRawRGB(leftS, currentLeft[0], currentLeft[1], currentLeft[2]);
}

not needed rn
*/
