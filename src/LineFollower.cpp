#include "LineFollower.h"
#include <string>

LineFollower::LineFollower(int KP, int KI, int KD, int Speed, int CameraID)
{
    kP = KP;
    kI = KI;
    kD  = KD;
    speed = Speed;

    fError      = 0;
    fLast_Error = 0;
    fP      = 0;
    fI      = 0;
    fD      = 0;
    fPID    = 0;
    fLast_I = 0;


    lineDetection.OpenCamera(CameraID);
}

LineFollower::~LineFollower()
{
    //dtor
}

MotorsControl LineFollower::GetMotorsControl()
{
    motorsControl.error = lineDetection.GetError();

    fError = motorsControl.error.PIDValue;


    fP = fError;
	fI = fI + fLast_I;
	fD = fError - fLast_Error;

	fPID = (kP * fP) + (kI * fI) + (kD * fD);

	fLast_I = fI;
	fLast_Error = fError;

	int SpeedMotorFrontLeft 	= speed - fPID;
	int SpeedMotorRearLeft 		= speed - fPID;
	int SpeedMotorFrontRight 	= speed + fPID;
	int SpeedMotorRearRight 	= speed + fPID;

	motorsControl.MotorFrontLeft_PWM;
    motorsControl.MotorFrontRight_PWM;
    motorsControl.MotorRearLeft_PWM;
    motorsControl.MotorRearRight_PWM;
    motorsControl.PIDvariables =    "Error: " + to_string(fError) + "\tfLast_Error: " + to_string(fLast_Error) + "\tfPID: " + to_string(fPID) +
                                    "\tfP: " + to_string(fP) + "\tfI: "+ to_string(fI) + "\tfLast_I: " + to_string(fLast_I) + "\tfD: " + to_string(fD)  +
                                    "\t(kP * fP): " + to_string(kP * fP) + "\t(kI * fI): " + to_string(kI * fI) + "\t(kD * fD): " + to_string(kD * fD);
    return motorsControl;
}
