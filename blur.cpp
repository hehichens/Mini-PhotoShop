#include "blur.h"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

static Mat org;
static Mat dst;



Mat median_blur(Mat org, int k)
{
    k = k*2+1;
    medianBlur(org, dst, k);
    return dst;
}


Mat gussian_blur(Mat org, int k)
{
    k = k*2+1;
    GaussianBlur(org, dst, Size( k, k ), 0, 0 );
    return dst;
}


Mat mean_blur(Mat org, int k)
{
    k = k*2+1;
    blur(org, dst, Size(k, k));
    return dst;
}