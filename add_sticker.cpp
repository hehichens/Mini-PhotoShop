#include "graph_scene.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <QGraphicsSceneMouseEvent>
#include <QtCore>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <unistd.h>

using std:: string;
using namespace cv;

void GraphScreen::add_sticker(int mx,int my, int size){
    Mat logo = sticker_img.clone();
    Mat img = QImage2cvMat(*ScreenPic).clone();
    cv::resize(logo, logo, Size(size,size), 0, 0, INTER_LINEAR);
    Mat mask;
    cvtColor(logo,mask,COLOR_BGR2GRAY);
    bitwise_not(mask, mask);
    threshold(mask, mask, 15, 255, THRESH_BINARY);

    if((mx<img.cols-logo.cols/2 && mx>logo.cols/2)&&(my<img.rows-logo.rows/2 && my>logo.rows/2)){
        Mat imgROI = img(Rect(mx-logo.cols/2, my-logo.rows/2, logo.cols, logo.rows));
        logo.copyTo(imgROI, mask);
    }

    Mat cloneimg=img.clone();
    *ScreenPic = cvMat2QImage(cloneimg);
}

void GraphScreen::set_m_addsticker(bool state){
    m_addsticker = state;
}

void GraphScreen::set_sticker_size(int size){
    sticker_size = size;
}

void GraphScreen::select_sticker(int sticker_idx){
    if (sticker_idx == 1){
        QImage *sticker1;
        sticker1 = new QImage(":/images/s1.jpg");
        sticker_img = QImage2cvMat(*sticker1);
    }
    else if (sticker_idx == 2){
        QImage *sticker2;
        sticker2 = new QImage(":/images/s2.jpg");
        sticker_img = QImage2cvMat(*sticker2);
    }
    else if (sticker_idx == 3){
        QImage *sticker3;
        sticker3 = new QImage(":/images/s3.jpg");
        sticker_img = QImage2cvMat(*sticker3);
    }
    else if (sticker_idx == 4){
        QImage *sticker4;
        sticker4 = new QImage(":/images/s4.jpg");
        sticker_img = QImage2cvMat(*sticker4);
    }
    else if (sticker_idx == 5){
        QImage *sticker5;
        sticker5 = new QImage(":/images/s5.jpg");
        sticker_img = QImage2cvMat(*sticker5);
    }
    else if (sticker_idx == 6){
        QImage *sticker6;
        sticker6 = new QImage(":/images/s6.jpeg");
        sticker_img = QImage2cvMat(*sticker6);
    }
}
