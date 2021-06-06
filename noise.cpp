#include "noise.h"
#include <cstdlib>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

Mat noise(Mat org, int mode){
    if (mode == 0){
        int num = (org.rows * org.cols)/100;
        Mat dst = addSPNoise(org, num);
        return dst;
    } else {
        Mat dst = addGaussianNoise(org);
        return dst;
    }
}

Mat addSPNoise(const Mat srcImage, int n){
    Mat dstImage = srcImage.clone();
    for (int k = 0; k < n; k++)	{
        //Randomly choose columns and rows
        int i = rand() % dstImage.rows;
        int j = rand() % dstImage.cols;
        //Judge the number of channels
        if (dstImage.channels() == 1) // Salt
        {
            dstImage.at<uchar>(i, j) = 255;
        } else {
            dstImage.at<Vec3b>(i, j)[0] = 255;
            dstImage.at<Vec3b>(i, j)[1] = 255;
            dstImage.at<Vec3b>(i, j)[2] = 255;
        }
    }
    for (int k = 0; k < n; k++)	{
        // Random choose columns and rows
        int i = rand() % dstImage.rows;
        int j = rand() % dstImage.cols;
        if (dstImage.channels() == 1) // Judge the number of channels.
        {
            dstImage.at<uchar>(i, j) = 0; // Pepper
        } else {
            dstImage.at<Vec3b>(i, j)[0] = 0;
            dstImage.at<Vec3b>(i, j)[1] = 0;
            dstImage.at<Vec3b>(i, j)[2] = 0;
        }
    }
    return dstImage;
}

double generateGaussianNoise(double mu, double sigma){
    //Define the minimum number
    const double epsilon = numeric_limits<double>::min();
    static double z0, z1;
    static bool flag = false;
    flag = !flag;	//flag is the random variable for gerenating fake Gaussian
    if (!flag) {
        return z1 * sigma + mu;
    }
    double u1, u2;	//Define random variables
    do	{
        u1 = rand() * (1.0 / RAND_MAX);
        u2 = rand() * (1.0 / RAND_MAX);
    } while (u1 <= epsilon);
    //flag is the random variable for gerenating real Gaussian
    z0 = sqrt(-2.0*log(u1))*cos(2 * CV_PI*u2);
    z1 = sqrt(-2.0*log(u1))*sin(2 * CV_PI*u2);
    return z0*sigma + mu;
}

// Add Gaussian Noise to the image
Mat addGaussianNoise(Mat &srcImag){
    Mat dstImage = srcImag.clone();
    int channels = dstImage.channels();
    int rowsNumber = dstImage.rows;
    int colsNumber = dstImage.cols*channels;
    // Judge whether the image is continuous or not
    if (dstImage.isContinuous())
    {
        colsNumber *= rowsNumber;
        rowsNumber = 1;
    }
    for (int i = 0; i < rowsNumber; i++)
    {
        for (int j = 0; j < colsNumber; j++)
        {
            // Add gaussian noise
            int val = dstImage.ptr<uchar>(i)[j] + generateGaussianNoise(2, 0.8) * 32;
            if (val < 0)
                val = 0;
            if (val>255)
                val = 255;
            dstImage.ptr<uchar>(i)[j] = uchar(val);
        }
    }
    return dstImage;
}
