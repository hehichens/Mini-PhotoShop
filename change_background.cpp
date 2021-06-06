#include <opencv2/opencv.hpp>
//#include <opencv2/xfeatures2d.hpp>

//#include<opencv2/face.hpp>
#include<iostream>
#include<math.h>
#include <string>
#include<fstream>
#include "big_eye.h"

// using namespace cv::face;
using namespace cv;
using namespace std;
//using namespace cv::xfeatures2d;


/*
 * Implementation Note: changeBackground
 * -------------------------
 * this method take the image as the input and the chosen color_flag from the user
 * and then it will change the background of this identification photo to the corresponding
 * color user choose.
 *
*/
Mat changeBackground(Mat image,int color_flag) {
    Mat src =  image;

    //初始化图片背景的长度与宽度
    int width = src.cols;
    int height = src.rows;
    int samplecount = width * height;
    int dims = src.channels();

    //行数为src的像素点数，列数为通道数，每列数据分别为src的bgr，从上到下 从左到右顺序读数据,把数据读取后传递给“points”
    Mat points(samplecount, dims, CV_32F, Scalar(10));
    int ind = 0;
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            ind = row * width + col;
            Vec3b bgr = src.at<Vec3b>(row, col);
            points.at<float>(ind, 0) = static_cast<int>(bgr[0]);
            points.at<float>(ind, 1) = static_cast<int>(bgr[1]);
            points.at<float>(ind, 2) = static_cast<int>(bgr[2]);
        }
    }


    //运行kmeans 算法
    int numCluster = 5;
    Mat labels;
    Mat centers;

    //最多迭代10次
    TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 0.1);


    kmeans(points, numCluster, labels, criteria, 3, KMEANS_PP_CENTERS, centers);


    //去背景+遮罩生成
    Mat mask = Mat::zeros(src.size(), CV_8UC1);
    int index = src.rows * 2 + 2;//不取边缘的左上点，往里靠2个位置
    int cindex = labels.at<int>(index, 0);
    int height1 = src.rows;
    int width1 = src.cols;
    Mat dst;//人的轮廓周围会有一些杂点，所以需要腐蚀和高斯模糊取干扰


    //原始图像拷贝给dst
    src.copyTo(dst);
    for (int row = 0; row < height1; row++) {
        for (int col = 0; col < width1; col++) {
            index = row * width1 + col;
            int label = labels.at<int>(index, 0);
            if (label == cindex) {
                dst.at<Vec3b>(row, col)[0] = 0;
                dst.at<Vec3b>(row, col)[1] = 0;
                dst.at<Vec3b>(row, col)[2] = 0;
                mask.at<uchar>(row, col) = 0;
            }
            else {
                dst.at<Vec3b>(row, col) = src.at<Vec3b>(row, col);
                mask.at<uchar>(row, col) = 255;//人脸部分设为白色，以便于下面的腐蚀与高斯模糊
            }
        }
    }

    //腐蚀+高斯模糊
    Mat k = getStructuringElement(MORPH_RECT, Size(3, 3));
    erode(mask, mask, k);
    GaussianBlur(mask, mask, Size(3, 3), 0, 0);

    //通道混合
    RNG rng(12345);



//调整这个来改变颜色
    Vec3b color; //填充进背景的颜色 默认白色 调三通道配比改变颜色
    if(color_flag == 0){
        color[0] = 255;//rng.uniform(0, 255);
        color[1] = 255;//rng.uniform(0, 255);
        color[2] = 255;//rng.uniform(0, 255);
    }else if (color_flag == 1 ) {
        color[0] = 33;//rng.uniform(0, 255);
        color[1] = 40;//rng.uniform(0, 255);
        color[2] = 193;//rng.uniform(0, 255);

    }else if(color_flag == 2 ){
        color[0] = 227;//rng.uniform(0, 255);
        color[1] = 160;//rng.uniform(0, 255);
        color[2] = 66;//rng.uniform(0, 255);
    }


    Mat result(src.size(), src.type());

    double w = 0.0;
    int b = 0, g = 0, r = 0;
    int b1 = 0, g1 = 0, r1 = 0;
    int b2 = 0, g2 = 0, r2 = 0;

    double time = getTickCount();
    for (int row = 0; row < height1; row++) {
        for (int col = 0; col < width; col++) {
            int m = mask.at<uchar>(row, col);
            if (m == 255) {
                result.at<Vec3b>(row, col) = src.at<Vec3b>(row, col);//前景
            }
            else if (m == 0) {
                result.at<Vec3b>(row, col) = color; // 背景
            }
            else {//因为高斯模糊的关系，所以mask元素的颜色除了黑白色还有黑白边缘经过模糊后的非黑白值
                w = m / 255.0;
                b1 = src.at<Vec3b>(row, col)[0];
                g1 = src.at<Vec3b>(row, col)[1];
                r1 = src.at<Vec3b>(row, col)[2];
                b2 = color[0];
                g2 = color[0];
                r2 = color[0];

                b = b1 * w + b2 * (1.0 - w);
                g = g1 * w + g2 * (1.0 - w);
                r = r1 * w + r2 * (1.0 - w);

                result.at<Vec3b>(row, col)[0] = b;//最终边缘颜色值
                result.at<Vec3b>(row, col)[1] = g;
                result.at<Vec3b>(row, col)[2] = r;

            }
        }
    }
    cout << "time=" << (getTickCount() - time) / getTickFrequency() << endl;

    return  result;
}
