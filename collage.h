#ifndef COLLAGE_H
#define COLLAGE_H

#include <iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

static Mat img1,img2;

/*
* Function: combine_ver
* Usage: combine_ver(Mat img1, Mat img2);
* ------------------------------
* this function is used to combine two images into one image,
* and they are combined vertically.
*/
Mat combine_ver(Mat img1, Mat img2);

/*
* Function: combine_hor
* Usage: combine_hor(Mat img1, Mat img2);
* ------------------------------
* this function is used to combine two images into one image,
* and they are combined horizontally.
*/
Mat combine_hor(Mat img1, Mat img2);

#endif // COLLAGE_H
