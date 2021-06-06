#ifndef SATURATION_H
#define SATURATION_H

#include <time.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

/*
 * Method: Mat saturation(Mat org, int value);
 * Usage: dst = saturation(org, k);
 * ------------------------------------------
 * This method is used to adjust the saturation of the picture.
 */
Mat saturation(Mat org, int value);

#endif // SATURATION_H
