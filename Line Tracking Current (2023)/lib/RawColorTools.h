bool rawColorSensing = true;

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
//Black fixed by Masa 3/29/2023
int blackRight[2][3]= {
		{13, 19, 4},
	  {25, 44, 14}
};

int whiteRight[2][3]= {
		{202, 260, 115},
	  {265, 270, 150}
};
//green changed by Masa 3/29/2023
int greenRight[2][3]= {
		{34, 117, 17},
	  {55, 142, 31}
};
//Red fixed by Masa 3/29/2023
int redRight[2][3]= {
		{165, 28, 8},
	  {195, 60, 21}
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
if(rawColorSensing == true){
	getColorRawRGB(rightS, currentRight[0], currentRight[1], currentRight[2]);
	if(((blackRight[0][0]<=currentRight[0])&&(currentRight[0]<=blackRight[1][0]))&&((blackRight[0][1]<=currentRight[1])&&(currentRight[1]<=blackRight[1][1]))&&((blackRight[0][2]<=currentRight[2])&&(currentRight[2]<=blackRight[1][2]))){
		return true;
	}
	else{
		return false;
	}
	}
else{
	return (getColorName(rightS) == colorBlack);
}
}

bool leftEqualsBlack(){
if(rawColorSensing == true){
getColorRawRGB(leftS, currentLeft[0], currentLeft[1], currentLeft[2]);
if(((blackLeft[0][0]<=currentLeft[0])&&(currentLeft[0]<=blackLeft[1][0]))&&((blackLeft[0][1]<=currentLeft[1])&&(currentLeft[1]<=blackLeft[1][1]))&&((blackLeft[0][2]<=currentLeft[2])&&(currentLeft[2]<=blackLeft[1][2]))){
	return true;
}
else{
	return false;
}
}
else{
	return (getColorName(leftS) == colorBlack);
}
}

bool rightEqualsWhite(){
if(rawColorSensing == true){
	getColorRawRGB(rightS, currentRight[0], currentRight[1], currentRight[2]);
	if(((whiteRight[0][0]<=currentRight[0])&&(currentRight[0]<=whiteRight[1][0]))&&((whiteRight[0][1]<=currentRight[1])&&(currentRight[1]<=whiteRight[1][1]))&&((whiteRight[0][2]<=currentRight[2])&&(currentRight[2]<=whiteRight[1][2]))){
		return true;
	}
	else{
		return false;
	}
}
else{
	return (getColorName(rightS) == colorWhite);
}
}

bool leftEqualsWhite(){
	if(rawColorSensing == true){
getColorRawRGB(leftS, currentLeft[0], currentLeft[1], currentLeft[2]);
if(((whiteLeft[0][0]<=currentLeft[0])&&(currentLeft[0]<=whiteLeft[1][0]))&&((whiteLeft[0][1]<=currentLeft[1])&&(currentLeft[1]<=whiteLeft[1][1]))&&((whiteLeft[0][2]<=currentLeft[2])&&(currentLeft[2]<=whiteLeft[1][2]))){
	return true;
}
else{
	return false;
}
}
else{
	return (getColorName(leftS) == colorWhite);
}
}

bool rightEqualsGreen(){
if(rawColorSensing == true){
	getColorRawRGB(rightS, currentRight[0], currentRight[1], currentRight[2]);
	if(((greenRight[0][0]<=currentRight[0])&&(currentRight[0]<=greenRight[1][0]))&&((greenRight[0][1]<=currentRight[1])&&(currentRight[1]<=greenRight[1][1]))&&((greenRight[0][2]<=currentRight[2])&&(currentRight[2]<=greenRight[1][2]))){
		return true;
	}
	else{
		return false;
	}
}
else{
	return (getColorName(rightS) == colorWhite);
}
}

bool leftEqualsGreen(){
if(rawColorSensing == true){
getColorRawRGB(leftS, currentLeft[0], currentLeft[1], currentLeft[2]);
if(((greenLeft[0][0]<=currentLeft[0])&&(currentLeft[0]<=greenLeft[1][0]))&&((greenLeft[0][1]<=currentLeft[1])&&(currentLeft[1]<=greenLeft[1][1]))&&((greenLeft[0][2]<=currentLeft[2])&&(currentLeft[2]<=greenLeft[1][2]))){
	return true;
}
else{
	return false;
}
}
else{
	return (getColorName(leftS) == colorGreen);
}
}

bool rightEqualsRed(){
if(rawColorSensing == true){
getColorRawRGB(rightS, currentRight[0], currentRight[1], currentRight[2]);
if(((redRight[0][0]<=currentRight[0])&&(currentRight[0]<=redRight[1][0]))&&((redRight[0][1]<=currentRight[1])&&(currentRight[1]<=redRight[1][1]))&&((redRight[0][2]<=currentRight[2])&&(currentRight[2]<=redRight[1][2]))){
	return true;
}
else{
	return false;
}
}
else{
	return (getColorName(rightS) == colorRed);
}
}

bool leftEqualsRed(){
if(rawColorSensing == true){
getColorRawRGB(leftS, currentLeft[0], currentLeft[1], currentLeft[2]);
if(((redLeft[0][0]<=currentLeft[0])&&(currentLeft[0]<=redLeft[1][0]))&&((redLeft[0][1]<=currentLeft[1])&&(currentLeft[1]<=redLeft[1][1]))&&((redLeft[0][2]<=currentLeft[2])&&(currentLeft[2]<=redLeft[1][2]))){
	return true;
}
else{
	return false;
}
}
else{
	return (getColorName(leftS) == colorRed);
}
}

void colorMarginBlack(int margin){
	blackLeft[0][0]=blackLeftBase[0]-margin;
	blackRight[0][0]=blackRightBase[0]-margin;
	blackLeft[0][1]=blackLeftBase[1]-margin;
	blackRight[0][1]=blackRightBase[1]-margin;
	blackLeft[0][2]=blackLeftBase[2]-margin;
	blackRight[0][2]=blackRightBase[2]-margin;

	blackLeft[1][0]=blackLeftBase[0]+margin;
	blackRight[1][0]=blackRightBase[0]+margin;
	blackLeft[1][1]=blackLeftBase[1]+margin;
	blackRight[1][1]=blackRightBase[1]+margin;
	blackLeft[1][2]=blackLeftBase[2]+margin;
	blackRight[1][2]=blackRightBase[2]+margin;
}

void colorMarginWhite(int margin){
	whiteLeft[0][0]=whiteLeftBase[0]-margin;
	whiteRight[0][0]=whiteRightBase[0]-margin;
	whiteLeft[0][1]=whiteLeftBase[1]-margin;
	whiteRight[0][1]=whiteRightBase[1]-margin;
	whiteLeft[0][2]=whiteLeftBase[2]-margin;
	whiteRight[0][2]=whiteRightBase[2]-margin;

	whiteLeft[1][0]=whiteLeftBase[0]+margin;
	whiteRight[1][0]=whiteRightBase[0]+margin;
	whiteLeft[1][1]=whiteLeftBase[1]+margin;
	whiteRight[1][1]=whiteRightBase[1]+margin;
	whiteLeft[1][2]=whiteLeftBase[2]+margin;
	whiteRight[1][2]=whiteRightBase[2]+margin;
}

void colorMarginRed(int margin){
	redLeft[0][0]=redLeftBase[0]-margin;
	redRight[0][0]=redRightBase[0]-margin;
	redLeft[0][1]=redLeftBase[1]-margin;
	redRight[0][1]=redRightBase[1]-margin;
	redLeft[0][2]=redLeftBase[2]-margin;
	redRight[0][2]=redRightBase[2]-margin;

	redLeft[1][0]=redLeftBase[0]+margin;
	redRight[1][0]=redRightBase[0]+margin;
	redLeft[1][1]=redLeftBase[1]+margin;
	redRight[1][1]=redRightBase[1]+margin;
	redLeft[1][2]=redLeftBase[2]+margin;
	redRight[1][2]=redRightBase[2]+margin;
}

void colorMarginGreen(int margin){
	greenLeft[0][0]=greenLeftBase[0]-margin;
	greenRight[0][0]=greenRightBase[0]-margin;
	greenLeft[0][1]=greenLeftBase[1]-margin;
	greenRight[0][1]=greenRightBase[1]-margin;
	greenLeft[0][2]=greenLeftBase[2]-margin;
	greenRight[0][2]=greenRightBase[2]-margin;

	greenLeft[1][0]=greenLeftBase[0]+margin;
	greenRight[1][0]=greenRightBase[0]+margin;
	greenLeft[1][1]=greenLeftBase[1]+margin;
	greenRight[1][1]=greenRightBase[1]+margin;
	greenLeft[1][2]=greenLeftBase[2]+margin;
	greenRight[1][2]=greenRightBase[2]+margin;
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

void setRawColorSensing(bool value){
	rawColorSensing = value;
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
