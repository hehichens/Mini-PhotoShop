#include "fliter_color.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>

using namespace cv;
using namespace std;

static Mat org, pic;
static int Hmin[8] = {0, 325, 8, 28, 65, 160, 240, 280};
static int Hmax[8] = {15, 360, 45, 70, 165, 240, 300, 340};

//Input: Red-1, Orange-2, Yellow-3, Green-4, Blue-5, Purple-6, Pink-7

Mat filter_color(Mat org, int mode){ // 01 2 3 4 5 6 7
    Mat dst(org.size(), CV_8UC3); //Mat float and channel 3.
    org.convertTo(dst, CV_8UC1);

    Mat R(org.size(), CV_8UC1);
    Mat G(org.size(), CV_8UC1);
    Mat B(org.size(), CV_8UC1);
    Mat I(org.size(), CV_8UC1);
    Mat bw(org.size(), CV_8UC1);

    Mat rgb[] = {B, G, R};
    cv::split(dst, rgb);
    I = R+G+B;

    double maxVal, minVal, hVal = 0;
    for(int i = 0; i < I.rows; i++)
    {
        for(int j = 0; j < I.cols; j++) // for each pixel
        {
            bw.at<uchar>(i,j) = (0.2989*R.at<uchar>(i,j) + 0.5870*G.at<uchar>(i,j) + 0.1140*B.at<uchar>(i,j));
        }
    }
    Mat pic = Mat::zeros(bw.rows, bw.cols, CV_32FC3);
    vector<Mat> channels;
    for (int i=0;i<3;i++)
    {
        channels.push_back(bw);
    }
    merge(channels, pic);


    for(int i = 0; i < I.rows; i++)
    {
        for(int j = 0; j < I.cols; j++) // for each pixel
        {
            maxVal = std::max(R.at<uchar>(i,j), std::max(G.at<uchar>(i,j), B.at<uchar>(i,j))); // max value of RGB
            minVal = std::min(R.at<uchar>(i,j), std::min(G.at<uchar>(i,j), B.at<uchar>(i,j))); // min value of RGB
            if (R.at<uchar>(i,j) >= G.at<uchar>(i,j) && R.at<uchar>(i,j) >= B.at<uchar>(i,j)){
                hVal = (G.at<uchar>(i,j)-B.at<uchar>(i,j)) / (maxVal - minVal) * 60;
            } else if (G.at<uchar>(i,j) >= R.at<uchar>(i,j) && G.at<uchar>(i,j) >= B.at<uchar>(i,j)){
                hVal = 120 + (B.at<uchar>(i,j)-R.at<uchar>(i,j)) / (maxVal - minVal) * 60;
            } else if (B.at<uchar>(i,j) >= R.at<uchar>(i,j) && B.at<uchar>(i,j) >= G.at<uchar>(i,j)){
                hVal = 240 + (R.at<uchar>(i,j)-G.at<uchar>(i,j)) / (maxVal - minVal) * 60;
            }

            if (hVal < 0){
                hVal = hVal+360;
            }

            if (hVal <= Hmax[mode] && hVal >= Hmin[mode]){
                pic.at<Vec3b>(i, j)[0] = org.at<Vec3b>(i, j)[0];
                pic.at<Vec3b>(i, j)[1] = org.at<Vec3b>(i, j)[1];
                pic.at<Vec3b>(i, j)[2] = org.at<Vec3b>(i, j)[2];
            } else if (mode == 1 && hVal <= Hmax[0] && hVal >= Hmin[0]){
                pic.at<Vec3b>(i, j)[0] = org.at<Vec3b>(i, j)[0];
                pic.at<Vec3b>(i, j)[1] = org.at<Vec3b>(i, j)[1];
                pic.at<Vec3b>(i, j)[2] = org.at<Vec3b>(i, j)[2];
            }
        }
    }

    return pic;
}
