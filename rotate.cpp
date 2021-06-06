#include "rotate.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace std;

Mat rotate(Mat src, int mode)  {
    Mat dst, dst2, dst3;
    switch(mode){
    case 1:  // Left rotate.
        transpose(src, dst);
        flip(dst, dst2, 0);
        return dst2;
        break;
    case 2: // Right rotate
        transpose(src, dst);
        flip(dst, dst2, 1);
        return dst2;
        break;
    case 3: // Horizontal flip
        flip(src, dst, 1);
        return dst;
        break;
    case 4: // Vertical flip.
        flip(src, dst, 0);
        return dst;
        break;
    case 5: // Diagonal flip.
        flip(src, dst, -1);
        return dst;
        break;
    default:
        break;
    }
}


Mat resize_img(Mat src, int k){
    Mat dst;
    float ratio = (float) k / 100;
    cout<<"ratio: "<<ratio<<endl;
    resize(src, dst, Size(), ratio, ratio, INTER_CUBIC);
    return dst;
}