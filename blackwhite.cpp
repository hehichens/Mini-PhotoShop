#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>

#include <iostream>

using namespace cv;
using namespace std;

// Mat blackwhite(Mat org){
//     Mat dst(org.size(), CV_8UC3); //Mat float and channel 3.
//     org.convertTo(dst, CV_8UC3);

//     Mat R(org.size(), CV_8UC1);
//     Mat G(org.size(), CV_8UC1);
//     Mat B(org.size(), CV_8UC1);
//     Mat I(org.size(), CV_8UC1);
//     Mat BW_out(org.size(), CV_8UC1);

//     Mat rgb[] = {B, G, R}; // The order of channels.
//     cv::split(dst, rgb); //Split channels.

//     I = R+G+B;

//     for(int i = 0; i < I.rows; i++)
//     {
//         for(int j = 0; j < I.cols; j++) // for each pixel
//         {

//           BW_out.at<uchar>(i,j) = 0.2989*R.at<uchar>(i,j) + 0.5870*G.at<uchar>(i,j) + 0.1140*B.at<uchar>(i,j);

//         }
//     }

//     return BW_out;
// }


Mat blackwhite(Mat org, int k, int opt){
  // int k = 30;
  Mat dst;
  cvtColor(org, dst, CV_BGR2GRAY);
  if(opt == 1)
      threshold(dst, dst, k, 255, CV_THRESH_BINARY);
  else
      threshold(dst, dst, k, 255, CV_THRESH_OTSU);
  return dst;
}