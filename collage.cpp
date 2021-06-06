#include <iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;


Mat combine_ver(Mat img1, Mat img2){
    int width = img1.cols;

    double row = 1.0*img1.cols/img2.cols*img2.rows;

    int height = img1.rows + int(row);

    cv::Mat combine = cv::Mat::zeros(height, width ,img1.type());

    Mat imageROI1= combine(Rect(0,0,img1.cols,img1.rows));

    resize(img1, imageROI1, imageROI1.size(),INTER_CUBIC);

    Mat imageROI2= combine(Rect(0,img1.rows,img1.cols,row));

    resize(img2, imageROI2, imageROI2.size(),INTER_CUBIC);

    return combine;

}


Mat combine_hor(Mat img1, Mat img2){
    int height = img1.rows;

    double col = 1.0*img1.rows*img2.cols/img2.rows;

    int width = img1.cols + int(col);

    cv::Mat combine = cv::Mat::zeros(height, width ,img1.type());

    Mat imageROI1= combine(Rect(0,0,img1.cols,img1.rows));

    resize(img1, imageROI1, imageROI1.size(),INTER_CUBIC);

    Mat imageROI2= combine(Rect(img1.cols,0,col,img1.rows));

    resize(img2, imageROI2, imageROI2.size(),INTER_CUBIC);

    return combine;

}
