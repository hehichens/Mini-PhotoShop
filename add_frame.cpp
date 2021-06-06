#include <iostream>
#include<opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "add_frame.h"
#include <QtCore>
#include <QWidget>

using namespace std;
using namespace cv;

Mat QImage2cvMatframe(QImage image) {
    cv::Mat mat;
    cv::Mat dst;

    switch(image.format())
    {
    case QImage::Format_ARGB32:
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32_Premultiplied:

        image = image.convertToFormat(QImage::Format_RGB888);
        mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
        cv::cvtColor(mat, dst, COLOR_BGR2RGB);
        break;
    case QImage::Format_RGB888:
        mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
        cv::cvtColor(mat, dst, COLOR_BGR2RGB);
        break;
    case QImage::Format_Indexed8:
        mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
        break;
    }
    return dst;

}




Mat addframe(Mat img, int frame_num){

   // Mat frame1, frame2, frame3, frame4;

    int parameter = 10;
    if (frame_num == 1)
    {
        parameter = 10;
        QImage *frameImage1;
        frameImage1 = new QImage(":/images/heart.jpg");
        frame = QImage2cvMatframe(*frameImage1);
    }

    if (frame_num == 2)
    {
        parameter = 30;
        QImage *frameImage2;
        frameImage2 = new QImage(":/images/Gauty.jpg");
        frame = QImage2cvMatframe(*frameImage2);
    }

    if (frame_num == 3)
    {
        parameter = 10;
        QImage *frameImage3;
        frameImage3 = new QImage(":/images/COCOa.jpg");
        frame = QImage2cvMatframe(*frameImage3);
    }

    if (frame_num == 4)
    {
        parameter = 100;
        QImage *frameImage4;
        frameImage4 = new QImage(":/images/Vintage.jpg");
        frame = QImage2cvMatframe(*frameImage4);
    }

    resize(frame, frame, Size(img.cols,img.rows), 0, 0, INTER_LINEAR);
    cvtColor(frame,mask,COLOR_BGR2GRAY);
    bitwise_not(mask, mask);
    threshold(mask, mask, parameter, 255, THRESH_BINARY);
    frame.copyTo(img,mask);
    return img.clone();
}


Mat addframe_cv(Mat img, int mode){
    top = int (0.15*img.rows);
    bottom = static_cast<int> (0.15*img.rows);
    int left = static_cast<int> (0.15*img.cols);
    int right = static_cast<int> (0.15*img.cols);

    //边缘模糊
    if(mode == 1){
    borderType=BORDER_REPLICATE;
    copyMakeBorder( img, dst, top, bottom, left, right, borderType);
    }
    //边缘翻转
    if (mode==2){
    borderType=BORDER_REFLECT_101;
    copyMakeBorder( img, dst, top, bottom, left, right, borderType);
    }
    //黑边框
    if(mode == 3){
    Scalar value(0 ,0, 0);
    borderType=BORDER_CONSTANT;
    copyMakeBorder( img, dst, top, bottom, left, right, borderType,value);

    }
    //白边框
    if(mode == 4){
    Scalar value2(255,255,255);
    borderType=BORDER_CONSTANT;
    copyMakeBorder( img, dst, top, bottom, left, right, borderType,value2);

    }
    return dst;
}
