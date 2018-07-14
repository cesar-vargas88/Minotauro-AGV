#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "LineFollower.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <ctime>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    LineFollower lineFollower(5, 0.5, 2, 0.1, 0.1, 0, 640, 480);
    MotorsControl motorsControl;

    clock_t Start;
    clock_t End;

    int i= 0;

    while(true)
    {
        Start = clock();
        motorsControl = lineFollower.GetMotorsControl();
        cout << "Error: " << motorsControl.error.value << "\t PID: " << motorsControl.PID << endl;

        //imshow("Source", motorsControl.error.image);

        //while(clock() <= Start + 1000000)
        //{
            //usleep(1);
            //cout << "." << endl;
        //}

        //cout << "Start: " << Start << " End: " << clock() << " Diference: " << clock() - Start << endl;
        usleep(100000 - (clock()-Start));

    }
    waitKey(0);
    return 0;
}
