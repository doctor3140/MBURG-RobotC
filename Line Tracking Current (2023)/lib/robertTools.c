// use set to change the base varible for movement
// may also have to add #define in main program for movement to work. Requires testing

int m = 1; // for motor direction

float fSpeed = 4.5*m; //10 old //7.5 OG

float leanSpeed = 6; //for leaning (Ussually 20 for Bot1) //20 old
float ltSpeed =3; //for Line Tracking

float searchTime = 4000; //Time for SLT & SRT (was 1k)Ft
int tapeThreashold = 120; //Width of Green tape (how far it needs to move forward to detect the line in lilup //OG is 40 //60
int uTurnValue = m*680; //for uturns when two greens are detected //OG 185 //newscrap 155

int face = m*-320; // for faceLeft & faceRight //OG is m*190 (-320 total for big) //newscrap 160
int point = m*-700; // for leftPointTurn & rightPointTurn //OG is m*320 (-760 for big)

/
