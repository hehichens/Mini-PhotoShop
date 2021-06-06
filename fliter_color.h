#ifndef FLITER_COLOR_H
#define FLITER_COLOR_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>

using namespace cv;
using namespace std;

/*
 * Method: Mat filter_color(Mat org, int mode);
 * Usage: dst = filter_color(org, 2);
 * ---------------------------------------------
 * This method is transform the non-matched color part into black-white, and leave the
 * matched color part unchanges. This method is based on the division of colors on H
 * degree.
 */
Mat filter_color(Mat org, int mode);
#endif // FLITER_COLOR_H
