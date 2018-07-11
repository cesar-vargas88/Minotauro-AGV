#ifndef LINEFOLLOWER_H
#define LINEFOLLOWER_H
#include "LineDetection.h"
#include <iostream>

using namespace std;

struct MotorsControl
{
    int MotorFrontLeft_PWM;
    int MotorFrontRight_PWM;
    int MotorRearLeft_PWM;
    int MotorRearRight_PWM;
    struct_Error error;
    string PIDvariables;
};

class LineFollower
{
    public:

        LineFollower(float kP, float kI, float kD, float tiempoMuestreo, int speed, int CameraID, int Cols, int Rows);
        virtual ~LineFollower();

        MotorsControl GetMotorsControl();

    private:

        LineDetection lineDetection;

        int   Speed;

        float KP;
        float KI;
        float KD;

    	float Error;
        float LastError;

        float Proportional;
        float Integral;
        float Derivative;
        float PID;

        float TiempoMuestreo;

        MotorsControl motorsControl;
};

#endif // LINEFOLLOWER_H
