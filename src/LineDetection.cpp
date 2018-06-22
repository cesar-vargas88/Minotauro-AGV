#include "LineDetection.h"

LineDetection::LineDetection()
{
    capture.set(CV_CAP_PROP_FRAME_WIDTH, 640);
    capture.set(CV_CAP_PROP_FRAME_WIDTH, 480);
}

LineDetection::~LineDetection()
{
    //dtor
}

bool LineDetection::OpenCamera(int Camera_ID)
{
    camera_ID = Camera_ID;

    capture.open(1);

    if(capture.isOpened())
        return true;
    else
        return false;
}

struct_Error LineDetection::GetError()
{
    Mat src;
    Mat blur;
    Mat gray;

    int nCount = 0;
    int nSum   = 0;

    capture.read(src);

    medianBlur(src, blur, 101);
    gray = Gray(blur);
    error.ImageBinary = Binary(gray);

    ///Print a line in the half of rows
    for( int x = 0 ; x < error.ImageBinary.cols ; x++ )
    {
        if(error.ImageBinary.at<Vec3b>(error.ImageBinary.rows*0.5, x)[0] == 0)
        {
            error.ImageBinary.at<Vec3b>(error.ImageBinary.rows*0.5, x)[0] = 255;

            nCount++;
            nSum += x;
        }
        else
           error.ImageBinary.at<Vec3b>(240, x)[0] = 0;
    }
    ///Print a vertical line in the half of image
    for( int x = 0 ; x < error.ImageBinary.rows ; x++ )
        error.ImageBinary.at<Vec3b>(x,nSum/nCount)[0] = 255;

    error.PIDValue = (nSum/nCount) - error.ImageBinary.cols * .5;

    return error;
}

Mat LineDetection::Gray(Mat src)
{
	Mat		gray = src.clone();
	Vec3b	vColor;

	for (int y = 0; y < gray.rows; y++)
	{
		for (int x = 0; x < gray.cols; x++)
		{
			// get pixel
			vColor = gray.at<Vec3b>(Point(x, y));
			vColor[0] = (uint8_t) vColor[0] * 0.2989 + vColor[1] * 0.5870 + vColor[2] * 0.1140;
			vColor[1] = vColor[0];
			vColor[2] = vColor[0];

			// set pixel
			gray.at<Vec3b>(Point(x, y)) = vColor;
		}
	}

	return gray;
}

Mat LineDetection::Binary(Mat src)
{
	Mat	mOtsuMethod = src.clone();

	int	   iHistogram[256];
	double dHistogram[256];
	double dSum = 0;
	double dVariance[256];
	double dVarianceMayor = 0;
	int	   ikMayor = 0;
	double dPk = 0;
	double dmk = 0;
	double dmG = 0;

	Vec3b	vColor;

	//Clean histogram
	for (int x = 0; x < 256; x++)
	{
		iHistogram[x] = 0;
		dHistogram[x] = 0;
		dVariance[x]   = 0;
	}

	// Counts the intensity in any pixel
	for (int y = 0; y < mOtsuMethod.rows; y++)
	{
		for (int x = 0; x < mOtsuMethod.cols; x++)
		{
			// get pixel
			vColor = mOtsuMethod.at<Vec3b>(Point(x, y));
			iHistogram[vColor[0]]++;
		}
	}

	// Normalize histogram
	for (int x = 0; x < 256; x++)
	{
		dHistogram[x] = (double)iHistogram[x] / (mOtsuMethod.cols*mOtsuMethod.rows);
		dSum += dHistogram[x];
	}

	// Get mG
	for (int x = 0; x < 256; x++)
	{
		dmG += x * dHistogram[x];
	}

	for (int k = 0; k < 256; k++)
	{
		dPk = 0;
		dmk = 0;

		// Get P(k), m(k)
		for (int x = 0; x <= k; x++)
		{
			dPk += dHistogram[x];
			dmk += x * dHistogram[x];
		}
		// Get variance
		dVariance[k] = (((dmG * dPk) - dmk) * ((dmG * dPk) - dmk)) / (dPk * (1 - dPk));

		// Get variance and the bigger K
		if (dVariance[k] > dVarianceMayor)
		{
			dVarianceMayor = dVariance[k];
			ikMayor = k;
		}
	}

	// Counts the intensity in any pixel
	for (int y = 0; y < mOtsuMethod.rows; y++)
	{
		for (int x = 0; x < mOtsuMethod.cols; x++)
		{
			// get pixel
			vColor = mOtsuMethod.at<Vec3b>(Point(x, y));

			// If the average of the intensities is greater or equal than K, the maximum intensity is assigned
			if (vColor[0] >= ikMayor)
			{
				vColor[0] = 255;
				vColor[1] = 255;
				vColor[2] = 255;
			}
			// If not the minimum intensity is assigned
			else
			{
				vColor[0] = 0;
				vColor[1] = 0;
				vColor[2] = 0;
			}
			mOtsuMethod.at<Vec3b>(Point(x, y)) = vColor;
		}
	}

	return mOtsuMethod;
}
