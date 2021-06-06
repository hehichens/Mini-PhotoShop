#ifndef BRIGHTNESS_H
#define BRIGHTNESS_H

#include <iostream>
#include <stdio.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

/*
 * Method: on_BetaTrackbar(int m, Mat g_SrcImage)
 * Usage: on_BetaTrackbar(int m, Mat g_SrcImage);
 * ----------------------------------------------
 * This method is to adjust the brightness of the input Mat picture and put
 * result into g_DstImage.
 */
void on_BetaTrackbar(int m, Mat g_SrcImage);

/*
 * Method: Mat brightness(Mat g_SrcImage, int k);
 * Usage: Mat dst = brightness(org, k);
 * ----------------------------------------------
 * This method is to create a new empty dst image and call on_BetaTrackbar to
 * change the brightness.
 */
Mat brightness(Mat g_SrcImage, int k);

#endif // BRIGHTNESS_H
