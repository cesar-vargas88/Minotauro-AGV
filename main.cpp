#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "LineFollower.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    LineFollower lineFollower(60,1, 50, 255, 1);
    MotorsControl motorsControl;

    while(true)
    {
        usleep(100000);

        motorsControl = lineFollower.GetMotorsControl();

        //cout << "Error: " << motorsControl.error.PIDValue << endl;
        cout << motorsControl.PIDvariables << endl;
        imshow("Binary", motorsControl.error.ImageBinary);

        if(waitKey(30) >= 0)
            break;
    }
    waitKey(0);
    return 0;
}
