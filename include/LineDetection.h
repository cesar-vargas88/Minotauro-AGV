#ifndef LINEDETECTION_H
#define LINEDETECTION_H

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

struct struct_Error
{
    Mat image;
    int value;
};

class LineDetection
{
    public:

        LineDetection();
        virtual ~LineDetection();

        bool OpenCamera(int Camera_ID, int Cols, int Rows);
        struct_Error GetError();

    private:

        int cols;
        int rows;
        int camera_ID;
        VideoCapture capture;
        struct_Error error;

        Mat Gray(Mat src);
        Mat Binary(Mat src);
};

#endif // LINEDETECTION_H
