#ifndef ADD_FRAME_H
#define ADD_FRAME_H

#include<opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;

/*
* Function: addframe
* Usage: addframe(Mat img, int frame_num) ;
* ------------------------------
* this function provides four types of frame, and the user can
* choose different frame by different number.
*/
Mat addframe(Mat img, int frame_num);

/*
* Function: addframe_cv
* Usage: addframe_cv(Mat img, int mode);
* ------------------------------
* this function provides four types of frame, which are
* provide in opencv. The user can choose different frame
* by different number.
*/
Mat addframe_cv(Mat img, int mode);
static Mat org,img,mask,frame,dst,final;
static int top, bottom;
static int borderType;

#endif // ADD_FRAME_H
