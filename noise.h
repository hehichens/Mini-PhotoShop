#ifndef NOISE_H
#define NOISE_H
#include <cstdlib>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

/*
 * Method: double generateGaussianNoise(double m, double sigma);
 * Usage: k = generateGaussianNoise(m, sigma);
 * -------------------------------------------
 * This method is to generate a random number based on algorithm.
 */
double generateGaussianNoise(double m, double sigma);

/*
 * Method: Mat addGaussianNoise(Mat &srcImag);
 * Usage: dst = addGaussianNoise(org);
 * -----------------------------------------
 * This method is to add Gaussian noise on the picture.
 */
Mat addGaussianNoise(Mat &srcImag);

/*
 * Method: Mat noise(Mat org, int mode);
 * Usage: dst = noise(org, mode);
 * -------------------------------------
 * This method is to call relevant functions based mode.
 */
Mat noise(Mat org, int mode);

/*
 * Method: Mat addSPNoise(const Mat &srcImag, int n);
 * Usage: dst = addGaussianNoise(org, num);
 * -----------------------------------------
 * This method is to add salt and pepper noise on the picture.
 */
Mat addSPNoise(const Mat srcImage, int n);

#endif // NOISE_H
