#include "LineFollower.h"
#include <string>

LineFollower::LineFollower(float kP, float kI, float kD, float tiempoMuestreo, int speed, int CameraID, int Cols, int Rows)
{
    KP  = kP;
    KI  = kI;
    KD  = kD;
    TiempoMuestreo = tiempoMuestreo;
    Speed = speed;

    Error           = 0;
    LastError       = 0;
    Proportional    = 0;
    Integral        = 0;
    Derivative      = 0;
    PID             = 0;

    lineDetection.OpenCamera(CameraID, Cols, Rows);
}

LineFollower::~LineFollower()
{
    //dtor
}

MotorsControl LineFollower::GetMotorsControl()
{
    motorsControl.error = lineDetection.GetError();

    Error        =  motorsControl.error.value;
    Proportional =  Error;
	Integral    +=  Error * TiempoMuestreo;
	Derivative   = (Error - LastError) / TiempoMuestreo;

	PID = (KP * Error) + (KI * Integral) + (KD * Derivative);

	LastError = Error;

	/*int SpeedMotorFrontLeft 	= speed - fPID;
	int SpeedMotorRearLeft 		= speed - fPID;
	int SpeedMotorFrontRight 	= speed + fPID;
	int SpeedMotorRearRight 	= speed + fPID;

	motorsControl.MotorFrontLeft_PWM;
    motorsControl.MotorFrontRight_PWM;
    motorsControl.MotorRearLeft_PWM;
    motorsControl.MotorRearRight_PWM;*/
    motorsControl.PIDvariables =    "Error: "                   + to_string((int)Error) +
                                    //"\tLastError: "             + to_string(LastError) +
                                    "\tfPID: "                  + to_string(PID);// +
                                    //"\tProportional: "          + to_string(Proportional) +
                                    //"\tIntegral: "              + to_string(Integral) +
                                    //"\tDerivative: "            + to_string(Derivative)  +
                                    //"\t(KP * Proportional): "   + to_string(KP * Proportional) +
                                    //"\t(KI * Integral): "       + to_string(KI * Integral) +
                                    //"\t(KD * Derivative): "     + to_string(KD * Derivative);
    return motorsControl;
}
