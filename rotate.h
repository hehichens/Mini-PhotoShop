#ifndef ROTATE_H
#define ROTATE_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace std;

/* Method: Mat rotate(Mat src, int mode);
 * Usage: org = rotate(src, 1);
 * -------------------------------------
 * This method is used to rotate pictures based on mode.
 */

Mat rotate(Mat src, int mode);

Mat resize_img(Mat src, int k);

#endif // ROTATE_H
