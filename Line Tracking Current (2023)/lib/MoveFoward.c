#pragma config(Motor,  motorB,          leftM,         tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          rightM,        tmotorEV3_Large, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
repeat(forever){
motor[motorB] = 100;
motor[motorC] = 100;
}
}
