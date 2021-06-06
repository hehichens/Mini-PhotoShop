#ifndef MEDIAN_BLUR_H
#define MEDIAN_BLUR_H

/* This is to deal with salt-and-pepper noise. */
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

/*
 * Method median_blur(Mat org, int k)
 * Usage: Mat dst = median_blur(org, k);
 * ------------------------------------
 * This method is to blur the picture using medianBlur function.
 */

Mat median_blur(Mat org, int k);
Mat gussian_blur(Mat org, int k);
Mat mean_blur(Mat org, int k);

#endif // MEDIAN_BLUR_H
