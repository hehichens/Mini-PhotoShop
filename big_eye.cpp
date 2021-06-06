#include<opencv2/opencv.hpp>
#include "big_eye.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <iostream>
#include <stdio.h>
#include<QtCore>

using namespace std;
using namespace cv;

// input_image : 输入图像, howBig: 放大的比例 推荐1.15-1.25 太大不自然
Mat eyesBigger(Mat input_image,double howBig)
{
    String eyes_cascade_name = "./haarcascade_eye_tree_eyeglasses.xml";
    std::vector<Rect> eyes; // 眼睛的
    CascadeClassifier eyes_cascade;
    Mat frame_gray;
    Mat latten;
    Mat roi; //放大后的人眼局部图像

    eyes_cascade.load(eyes_cascade_name);
    input_image.copyTo(latten);
    cvtColor(input_image, frame_gray, COLOR_BGR2GRAY);
    eyes_cascade.detectMultiScale(frame_gray, eyes, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
    if (eyes.size() > 0)
    {
            for (int i = 0; i < eyes.size(); i++)
            {
                    //不断循环 根据放大的比例来扩大eyes的rect 然后贴回原图
                    Rect eye = eyes[i];
                    //rectangle(latten, eye, Scalar(0, 0, 255), 2);
                    roi = input_image(eye);
                    resize(roi, roi, Size(eye.height*howBig, eye.width*howBig));//把人眼放大到原本的n倍
                    roi.copyTo(latten(Rect(eye.x- (eye.height*howBig-roi.cols)/2, eye.y - (eye.width*howBig- roi.rows)/2, roi.cols, roi.rows)));
            }
    }
    return latten.clone();
}


///*
// * File : big_eyes.cpp
// * -------------------
// * this program implement a pictur_club classs
// */

//#include "big_eye.h"
//#include <cmath>
//const string EYE_XML = "/Users/rose/Desktop/cpp_project/unipicture0518/haarcascade_eye_tree_eyeglasses.xml";
//const string FACE_XML = "/Users/rose/Desktop/cpp_project/unipicture0518/haarcascade_frontalface_alt.xml";
//const Scalar c_GREEN(0,255,0);
//const Scalar c_RED(0,0,255);
//const Scalar c_BLUE(255,0,0);


///*
// * Implementation Note: eyesBigger
// * -------------------------
// * call the detect eyes and detect face function and
// * pass the eyeRect to the enlarge rect function.
//*/

////main function to implement the enlarge eye function
//Mat eyesBigger(Mat input_image, double size){

//    picture_club pc;
//    pc.GrabImage(input_image);
//    pc.cvtGray();
//    auto faces = pc.DetectFace();
//    auto eyes = pc.DetectEyes(faces[0]);
//    pc.EnlargeRects(eyes[0],size);
//    pc.EnlargeRects(eyes[1],size);

//    return pc.capture_image;
//}


///*
// * Implementation Note: EnlargeRects
// * -------------------------
// * use a circle area to take the points and update the pixel
// * according to the original image.
// *
//*/
//// enlarge specific part of the image
//void picture_club::EnlargeRects(const Rect & rect , double size){
//    Mat_<Vec3b> roi_image(capture_image,rect);
//    const Point2i roi_origin(rect.x,rect.y);
//    const Point2d center(
//        rect.x + rect.width*0.5,
//        rect.y + rect.height*0.5
//                );

//    const double kernel_radius = std::min(rect.height,rect.width)*0.5;

//    Mat_<Point2f> differential_kernel(rect.size());
//    Mat_<Vec3b> original_image = roi_image.clone();

//    for (int r = 0;r<differential_kernel.rows;++r) {
//        for (int c = 0;c<differential_kernel.cols;++c) {
//            const Point2f diff(r-rect.width*0.5,c-rect.width*0.5);

//            auto &p = differential_kernel(r,c);
//            const float distance = sqrt(diff.dot(diff));
//            if (distance < kernel_radius){
//                double rho_differential = (1-cos(distance/kernel_radius *M_PI))*size;

//                p = - diff * (rho_differential/kernel_radius);
//            }else{
//                p *= 0;
//            }
//            roi_image(c,r) = original_image(Point2f(r,c)+p);

//        }

//    }
//}

///*
// * Implementation Note: DetectFace DetectEyes
// * -------------------------
// * use opencv to detect the human face and eyes in the image
// *
//*/
////main method for face detection
//picture_club::RectVector
//picture_club::DetectFace(){
//    vector<Rect> face_region;
//    face_c.detectMultiScale(grayscaled_capture,face_region);
//    return  face_region;
//}


////main method for Eyes detection
//picture_club::RectVector
//picture_club::DetectEyes(const Rect & face_rect){
//    Mat eye_region_image(grayscaled_capture,face_rect);
//    RectVector eye_region;
//    eyes_c.detectMultiScale(grayscaled_capture,eye_region);

//    return  eye_region;
//}


///*
// * Implementation Note: GrabImage
// * -------------------------
// * 2 ways to grab the Image
// *
//*/
//// grab image into cature_image
//void picture_club::GrabImage(){
//    *capture_device >> capture_image;
//}


//// take input image as capture_image
//void picture_club::GrabImage(const Mat &image){
//    capture_image = image.clone();

//}


//picture_club::picture_club()
//    : processing_size(640,480)
//    ,face_c(FACE_XML)
//    ,eyes_c(EYE_XML)
//{
//    capture_device = new VideoCapture;
//}
//picture_club::~picture_club(){
//    delete  capture_device;
//}
