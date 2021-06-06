#include "basicfilter.h"

Mat old(Mat &srcImg){
    Mat src;
    srcImg.copyTo(src);
    int width = src.cols;
    int heigh = src.rows;
    for (int y = 0; y < heigh; y++)
    {
        uchar* srcImage = src.ptr<uchar>(y);
        for (int x = 0; x < width; x++)
        {
            double oldB = srcImage[3*x];
            double oldG = srcImage[3*x+1];
            double oldR = srcImage[3*x+2];
            double newB = 0.272*oldR + 0.534*oldG + 0.131*oldB;
            double newG = 0.349*oldR + 0.686*oldG + 0.168*oldB;
            double newR = 0.393*oldR + 0.769*oldG + 0.189*oldB;
            if(newB < 0) {
                newB = 0;
            }
            if(newB > 255){
                newB = 255;
            }
            if(newG < 0){
                newG = 0;
            }
            if(newG > 255){
                newG = 255;
            }
            if(newR < 0){
                newR = 0;
            }
            if(newR > 255){
                newR = 255;
            }

            srcImage[3*x] = static_cast<uchar>(newB);
            srcImage[3*x+1] = static_cast<uchar>(newG);
            srcImage[3*x+2] = static_cast<uchar>(newR);
        }
    }
    return src;
}


Mat magic(Mat &srcImg){
    Mat src;
    srcImg.copyTo(src);
    int width = src.cols;
    int heigh = src.rows;
    for (int y = 0;y < heigh;y++)
    {
        uchar* srcImage = src.ptr<uchar>(y);
        for (int x = 0; x < width; x++)
        {
            float oldB = srcImage[3*x];
            float oldG = srcImage[3*x+1];
            float oldR = srcImage[3*x+2];
            float newB = oldB*255 / (oldG+oldR+1);
            float newG = oldG*255 / (oldB+oldR+1);
            float newR = oldR*255 / (oldG+oldR+1);
            if(newR <= 0) {
                newR = 0;
            }
            else if (newR > 255){
                newR = 255;
            }

            if(newG <= 0) {
                newG = 0;
            }
            else if (newG > 255) {
                newG = 255;
            }

            if(newB <= 0) {
                newB = 0;
            }
            else if (newB > 255) {
                newB = 255;
            }
            srcImage[3*x] = static_cast<uchar>(newB);
            srcImage[3*x+1] = static_cast<uchar>(newG);
            srcImage[3*x+2] = static_cast<uchar>(newR);
        }
    }
    return src;
}

Mat silence(Mat &srcImg){
    Mat src;
    srcImg.copyTo(src);
    int width=src.cols;
    int heigh=src.rows;
    for (int y = 0; y < heigh; y++){
        uchar* srcImage=src.ptr<uchar>(y);
        for (int x = 0; x < width; x++){
            float oldB=srcImage[3*x];
            float oldG=srcImage[3*x+1];
            float oldR=srcImage[3*x+2];

            float newB = (oldB-oldG-oldR)*3/2;
            float newG = (oldG-oldB-oldR)*3/2;
            float newR = (oldR-oldG-oldB)*3/2;
            if(newR < 0) {
                newR = -newR;
            }
            else if (newR > 255){
                newR = 255;
            }

            if(newG < 0) {
                newG = -newG;
            }
            else if (newG > 255) {
                newG = 255;
            }

            if(newB <0) {
                newB = -newB;
            }
            else if (newB > 255) {
                newB = 255;
            }

            srcImage[3*x] = static_cast<uchar>(newB);
            srcImage[3*x+1] = static_cast<uchar>(newG);
            srcImage[3*x+2] = static_cast<uchar>(newR);
        }
    }
    return src;
}

Mat exposure(Mat &srcImg){
    Mat src;
    srcImg.copyTo(src);
    int width=src.cols;
    int heigh=src.rows;
    for(int y = 0; y < heigh;y++){
        uchar* srcImage = src.ptr<uchar>(y);
        for(int x = 0; x< width; x++){
            float newB, newG, newR;
            float oldB=srcImage[3*x];
            float oldG=srcImage[3*x+1];
            float oldR=srcImage[3*x+2];

            if (oldB < 0){
                newB = 0;
            }
            else if (oldB < 128){
                newB = 255 - oldB;
            }
            else if (oldB < 255){
                newB = oldB;
            }
            else {
                newB = 255;
            }

            if (oldG < 0){
                newG = 0;
            }
            else if (oldG < 128){
                newG = 255 - oldG;
            }
            else if (oldG < 255){
                newG = oldG;
            }
            else {
                newG = 255;
            }

            if (oldR < 0){
                newR = 0;
            }
            else if (oldR < 128){
                newR = 255 - oldR;
            }
            else if (oldR < 255){
                newR = oldR;
            }
            else {
                newR = 255;
            }

            srcImage[3*x] = static_cast<uchar>(newB);
            srcImage[3*x+1] = static_cast<uchar>(newG);
            srcImage[3*x+2] = static_cast<uchar>(newR);
        }
    }
    return src;
}


Mat comic(Mat &srcImg){
    Mat src;
    srcImg.copyTo(src);
    int width=src.cols;
    int heigh=src.rows;
    for (int y=0; y<heigh; y++)
        {
            uchar* srcImage  = src.ptr<uchar>(y);
            for (int x=0; x<width; x++)
            {
                float oldB=srcImage[3*x];
                float oldG=srcImage[3*x+1];
                float oldR=srcImage[3*x+2];
                float newB=abs(oldB-oldG+oldB+oldR)*oldG/256;
                float newG=abs(oldB-oldG+oldB+oldR)*oldR/256;
                float newR=abs(oldG-oldB+oldG+oldR)*oldR/256;
                if(newB < 0){
                    newB = 0;
                }
                if(newB > 255){
                    newB = 255;
                }
                if(newG < 0){
                    newG = 0;
                }
                if(newG > 255){
                    newG = 255;
                }
                if(newR < 0){
                    newR = 0;
                }
                if(newR > 255){
                    newR = 255;
                }
                srcImage[3*x] = static_cast<uchar>(newB);
                srcImage[3*x+1] = static_cast<uchar>(newG);
                srcImage[3*x+2] = static_cast<uchar>(newR);
            }

        }
    // Convert it into gray image
    Mat gray;
    cvtColor(src,gray,COLOR_BGR2GRAY);
    normalize(gray,gray,255,0,NORM_MINMAX);
    return gray;
}
