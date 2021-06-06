/*
 * File: crop.cpp
 * ------------------
 * This file implements the clipping.h interface.
 * This program outputs a picture after clipping by mouse.
 */
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include "graph_scene.h"

using namespace cv;
using namespace std;



static Mat img, org, org2, tmp;
static int k = 0, width, height, x_rec, y_rec;
Point pre_pt; // Initial coordinates.
Point cur_pt; // Current coordinates.
void onMouse(int event, int x, int y, int flags, void *);

void GraphScreen::set_m_crop(bool state){
    m_crop = state;
    qDebug()<<m_crop;
}

/*
 * Method: void GraphScreen::Crop_p(int x, int y);
 * -------------------------------------------------
 * This method is to obtain the first point of crop area.
 */
void GraphScreen::Crop_p(int x, int y){
    static int k = 0, width, height, x_rec, y_rec;
    static char temp[16];
    org = QImage2cvMat(*ScreenPic);
    org.copyTo(img);
    sprintf(temp, "(%d, %d)", x, y);
    pre_pt = Point(x, y);
    putText(img, temp, pre_pt, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,0, 255)); // Show coordinate on the window
    circle(img, pre_pt, 2, Scalar(255, 0, 0, 0), FILLED, LINE_AA, 0); // Draw a circle

}

/*
 * Method: GraphScreen::Crop_m(int x, int y)
 * -----------------------------------------
 * This method is to obtain the second point of crop area and draw a rectangle on the picture
 */
void GraphScreen::Crop_m(int x, int y){
    static int k = 0, width, height, x_rec, y_rec;
    static char temp[16];
    org = QImage2cvMat(*ScreenPic);
        img.copyTo(tmp); // Copy img to temporary tmp to show current corrdinates.
        sprintf(temp, "(%d, %d)", x, y);
        cur_pt = Point(x, y);
        putText(tmp, temp, cur_pt, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0, 255));
        rectangle(img, pre_pt, cur_pt, Scalar(0, 255, 0, 0), 1, 8, 0); // Based on the initial point and ending point, draw the rectangle on img.
}

/*
 * Method: void GraphScreen::Crop_r(int x, int y)
 * ----------------------------------------------
 * This method is to display the crop area.
 */
 void GraphScreen::Crop_r(int x, int y){
     static int k = 0, width, height, x_rec, y_rec;
     static char temp[16];
     org = QImage2cvMat(*ScreenPic);
        org.copyTo(img);
        sprintf(temp, "(%d, %d)", x, y);
        cur_pt = Point(x, y);
        putText(img, temp, cur_pt, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255));
        circle(img, cur_pt, 2, Scalar(255, 0, 0), FILLED, LINE_AA, 0);
        rectangle(img, pre_pt, cur_pt, Scalar(0, 255, 0, 0), 1, 8, 0); // Based on the initial point and ending point, draw the rectangle on img.

        img.copyTo(tmp);

        // Clip the picture within the rectangle and save it to dst
        width = abs(pre_pt.x - cur_pt.x);
        height = abs(pre_pt.y - cur_pt.y);
        if (width == 0 || height ==0) // Need change.
        {
            return;
        }

        x_rec = min(cur_pt.x, pre_pt.x);
        y_rec = min(cur_pt.y, pre_pt.y);
        cout << x_rec << y_rec<<width<<height;
        Rect rec = Rect(x_rec, y_rec, width, height);
        Mat dst;
        org(rec).copyTo(dst);

        *ScreenPic = cvMat2QImage(dst.clone());
    }
