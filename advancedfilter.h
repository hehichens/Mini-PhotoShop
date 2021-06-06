#ifndef ADVANCEDFILTER_H
#define ADVANCEDFILTER_H

#include <opencv2/opencv.hpp>
using namespace cv;
//using namespace std;

Mat neon(Mat &srcImg);

Mat highLight(Mat &srcImg);

Mat softLight(Mat &srcImg);

/* Two params can be adjust, one is for Beauty, another is for blur
 * Beauty range (1 ~ 5). GaussBlur Param(1 ~ 3)
 * Mat beauty(Mat &srcImg, int beautyParam = 3, int GuassBlurParam = 1);
 */
Mat beauty(Mat &srcImg);

Mat diffuse(Mat &srcImg);

Mat sketch(Mat &srcImg);

/* stikeParam, usually 10 - 50
 * Mat strike(Mat &srcImg, int strikeParam=25);
 */
Mat strike(Mat &srcImg);

/*volutionParam, usually 10 - 30
 * Mat volution(Mat &srcImg, int volutionParam=20);
 */
Mat volution(Mat &srcImg);

/*A is amptitude, delta is period
 * A range (0-100), delta (0-100)
 * Mat wave(Mat &srcImg, int Aparam=10, int deltaParam=10);
 */
Mat wave(Mat &srcImg);

Mat expand(Mat &srcImg);

Mat shrink(Mat &srcImg);

Mat embossment(Mat &srcImg);

Mat carve(Mat &srcImg);

#endif // ADVANCEDFILTER_H
