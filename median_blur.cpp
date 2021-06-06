#include "median_blur.h"
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
