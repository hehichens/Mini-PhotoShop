#ifndef BLACKWHITE_H
#define BLACKWHITE_H
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/*
 * Method: Mat blackwhite(Mat org);
 * Usage: Mat dst = blackwhite(org);
 * ---------------------------------
 * This method is to convert a colorful image into black-white image.
 * First, we change the channel of the image, then apply the widely-used
 * converting formula to transform image. The formula is
 * BW = 0.2989*R+0.5870*G+0.1140*B.
 */
Mat blackwhite(Mat org, int k, int opt);

#endif // BLACKWHITE_H
