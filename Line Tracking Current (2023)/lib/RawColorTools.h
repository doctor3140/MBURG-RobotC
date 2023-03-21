int currentRight[3]= {
		{0, 0, 0}
};
int currentLeft[3]= {
		{0, 0, 0}
};

int black[2][3]= {
		{32, 41, 20},
	  {34, 43, 22}
};
int white[2][3]= {
		{356, 396, 196},
	  {359, 396, 196}
};
int green[2][3]= {
		{71, 183, 35},
	  {73, 185, 36}
};
int red[2][3]= {
		{262, 33, 16},
	  {264, 33, 17}
};

//might add setter methods if deemed necessary, but honestly seems kinda annoying tbh

bool rightEqualsBlack(){
getColorRawRGB(rightS, currentRight[0], currentRight[1], currentRight[2]);
if((black[0][0]<=currentRight[0]<=black[1][0])&&(black[0][1]<=currentRight[1]<=black[1][2])&&(black[0][2]<=currentRight[2]<=black[1][2])){
	return true;
}
else{
	return false;
}
}

bool leftEqualsBlack(){
getColorRawRGB(leftS, currentLeft[0], currentLeft[1], currentLeft[2]);
if((black[0][0]<=currentLeft[0]<=black[1][0])&&(black[0][1]<=currentLeft[1]<=black[1][2])&&(black[0][2]<=currentLeft[2]<=black[1][2])){
	return true;
}
else{
	return false;
}
}

bool rightEqualsWhite(){
getColorRawRGB(rightS, currentRight[0], currentRight[1], currentRight[2]);
if((white[0][0]<=currentRight[0]<=white[1][0])&&(white[0][1]<=currentRight[1]<=white[1][2])&&(white[0][2]<=currentRight[2]<=white[1][2])){
	return true;
}
else{
	return false;
}
}

bool leftEqualsWhite(){
getColorRawRGB(leftS, currentLeft[0], currentLeft[1], currentLeft[2]);
if((white[0][0]<=currentLeft[0]<=white[1][0])&&(white[0][1]<=currentLeft[1]<=white[1][2])&&(white[0][2]<=currentLeft[2]<=white[1][2])){
	return true;
}
else{
	return false;
}
}

bool rightEqualsGreen(){
getColorRawRGB(rightS, currentRight[0], currentRight[1], currentRight[2]);
if((green[0][0]<=currentRight[0]<=green[1][0])&&(green[0][1]<=currentRight[1]<=green[1][2])&&(green[0][2]<=currentRight[2]<=green[1][2])){
	return true;
}
else{
	return false;
}
}

bool leftEqualsGreen(){
getColorRawRGB(leftS, currentRight[0], currentRight[1], currentRight[2]);
if((green[0][0]<=currentLeft[0]<=green[1][0])&&(green[0][1]<=currentLeft[1]<=green[1][2])&&(green[0][2]<=currentLeft[2]<=green[1][2])){
	return true;
}
else{
	return false;
}
}

bool rightEqualsRed(){
getColorRawRGB(rightS, currentRight[0], currentRight[1], currentRight[2]);
if((red[0][0]<=currentRight[0]<=red[1][0])&&(red[0][1]<=currentRight[1]<=red[1][2])&&(red[0][2]<=currentRight[2]<=red[1][2])){
	return true;
}
else{
	return false;
}
}

bool leftEqualsRed(){
getColorRawRGB(leftS, currentLeft[0], currentLeft[1], currentLeft[2]);
if((red[0][0]<=currentLeft[0]<=red[1][0])&&(red[0][1]<=currentLeft[1]<=red[1][2])&&(red[0][2]<=currentLeft[2]<=red[1][2])){
	return true;
}
else{
	return false;
}
}

void displayRightS(int line){
displayBigTextLine(line, "R: %d %d %d", currentRight[0], currentRight[1], currentRight[2]);
}

void displayLeftS(int line){
displayBigTextLine(line, "L: %d %d %d", currentLeft[0], currentLeft[1], currentLeft[2]);
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
