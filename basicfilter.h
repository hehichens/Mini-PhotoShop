#ifndef BASICFILTER_H
#define BASICFILTER_H

#include <opencv2/opencv.hpp>

using namespace cv;

Mat old(Mat &srcImg);

Mat magic(Mat &srcImg);

Mat silence(Mat &srcImg);

Mat exposure(Mat &srcImg);

Mat comic(Mat &srcImg);

#endif // BASICFILTER_H
