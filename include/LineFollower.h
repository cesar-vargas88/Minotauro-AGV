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

        LineFollower(int KP, int KI, int KD, int Speed, int CameraID);
        virtual ~LineFollower();

        MotorsControl GetMotorsControl();

    private:

        LineDetection lineDetection;

        float kP;
        float kI;
        float kD;
        int   speed;

    	float fError;
        float fP;
        float fI;
        float fD;
        float fPID;
        float fLast_Error;
        float fLast_I;

        MotorsControl motorsControl;
};

#endif // LINEFOLLOWER_H
