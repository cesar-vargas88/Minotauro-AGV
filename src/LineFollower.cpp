#include "LineFollower.h"

LineFollower::LineFollower(int KP, int KI, int KD, int Speed, int CameraID)
{
    kP = KP;
    kI = KI;
    kD  = KD;
    speed = Speed;

    lineDetection.OpenCamera(CameraID);
}

LineFollower::~LineFollower()
{
    //dtor
}

MotorsControl LineFollower::GetMotorsControl()
{
    motorsControl.error = lineDetection.GetError();

    return motorsControl;
}
