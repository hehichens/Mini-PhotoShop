/*
This program adjust the saturation.
*/
#include "saturation.h"
#include <time.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
using namespace std;
using namespace cv;
static Mat dst, tmp;

Mat saturation(Mat org, int value)
{

    dst = Mat::zeros(org.size(), CV_32FC3);
    org.convertTo(dst, CV_32FC3);
    tmp = Mat::zeros(org.size(), CV_32FC3);
    org.convertTo(tmp, CV_32FC3);

    // define the iterator of the input image
    MatIterator_<Vec3f> inp_begin, inp_end;
    inp_begin = tmp.begin<Vec3f>();
    inp_end = tmp.end<Vec3f>();

    // define the iterator of the output image
    MatIterator_<Vec3f> out_begin, out_end;
    out_begin = dst.begin<Vec3f>();
    out_end = dst.end<Vec3f>();

    // increment (-100.0, 100.0)
    float Increment = value/100.0;
    float delta = 0;
    float minVal, maxVal;
    float t1, t2, t3;
    float L,S;
    float alpha;

    for(; inp_begin != inp_end; inp_begin++, out_begin++)
    {
        t1 = (*inp_begin)[0];
        t2 = (*inp_begin)[1];
        t3 = (*inp_begin)[2];
        minVal = std::min(std::min(t1,t2),t3);
        maxVal = std::max(std::max(t1,t2),t3);
        delta = (maxVal - minVal)/255;
        L = (maxVal + minVal)/510;
        S = std::max(delta / (2*L), delta / (2-2*L));

        if (Increment>0)
        {
            alpha = max(S, 1-Increment);
            alpha = 1/alpha - 1;
            (*out_begin)[0] = (*inp_begin)[0] + ((*inp_begin)[0] - L*255) * alpha;
            (*out_begin)[1] = (*inp_begin)[1] + ((*inp_begin)[1] - L*255) * alpha;
            (*out_begin)[2] = (*inp_begin)[2] + ((*inp_begin)[2] - L*255) * alpha;
        }
        else
        {
            alpha=Increment;
            (*out_begin)[0] = L*255 + ((*inp_begin)[0] - L*255) * (1+alpha);
            (*out_begin)[1] = L*255 + ((*inp_begin)[1] - L*255) * (1+alpha);
            (*out_begin)[2] = L*255 + ((*inp_begin)[2] - L*255) * (1+alpha);
        }
    }

    Mat dst8 = dst.clone();
    dst8.convertTo(dst8, CV_8UC3);
    return dst8;
}
