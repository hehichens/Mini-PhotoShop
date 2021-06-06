#ifndef CONTRAST_H
#define CONTRAST_H

#include <iostream>
#include <stdio.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

/*
 * Method: on_AlphaTrackbar(int m,Mat g_SrcImage)
 * Usage: on_AlphaTrackbar(m, g_SrcImage);
 * ----------------------------------------------
 * This method is to adjust the contrast degree of the input Mat picture and put
 * result into g_DstImage.
 */
void on_AlphaTrackbar(int m,Mat g_SrcImage);

/*
 * Method: contrast(Mat g_SrcImage,int k)
 * Usage: Mat dst = contrast(org, k);
 * ----------------------------------------------
 * This method is to create a new empty dst image and call on_AlphaTrackbar to
 * change the contrast degree.
 */
Mat contrast(Mat g_SrcImage,int k);

#endif // CONTRAST_H
