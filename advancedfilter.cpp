#include <opencv2/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include "advancedfilter.h"

Mat neon(Mat &srcImg){
    Mat src;
    srcImg.copyTo(src);
    int width=src.cols;
    int heigh=src.rows;

    for(int y = 0; y < heigh-1; y++){
        uchar* srcImage = src.ptr<uchar>(y);
        for(int x = 0; x < width-1; x++){

            // RGB Value of current pixel
            int oldB = srcImage[x*3];
            int oldG = srcImage[x*3+1];
            int oldR = srcImage[x*3+2];

            // RGB Value of pixel in next col
            int oldB2 = srcImage[(x+1)*3];
            int oldG2 = srcImage[(x+1)*3+1];
            int oldR2 = srcImage[(x+1)*3+2];

            // Move the pointer to next row
            srcImage = src.ptr<uchar>(y+1);

            // RGB of the same column in next row
            int oldB3 = srcImage[x*3];
            int oldG3 = srcImage[x*3+1];
            int oldR3 = srcImage[x*3+2];

            // Move pointer back
            srcImage = src.ptr<uchar>(y);

            // Calculate new RGB (May change 10 to other const)
            int newR = static_cast<int>(10*sqrt((oldR-oldR2)*(oldR-oldR2) + (oldR-oldR3)*(oldR-oldR3)));
            int newG = static_cast<int>(10*sqrt((oldG-oldG2)*(oldG-oldG2) + (oldG-oldG3)*(oldG-oldG3)));
            int newB = static_cast<int>(10*sqrt((oldB-oldB2)*(oldB-oldB2) + (oldB-oldB3)*(oldB-oldB3)));

            srcImage[x*3] = static_cast<uchar>(max(0,min(newB,255)));
            srcImage[x*3+1] = static_cast<uchar>(max(0,min(newG,255)));
            srcImage[x*3+2] = static_cast<uchar>(max(0,min(newR,255)));
        }
    }
    return src;
}

Mat highLight(Mat &srcImg){
    Mat src;
    srcImg.copyTo(src);
    int width=src.cols;
    int heigh=src.rows;
    for(int y = 0; y < heigh-1; y++){
        uchar* srcImage = src.ptr<uchar>(y);

        for(int x = 0; x < width; x++){
            // Old BGR
            double oldB = static_cast<double>(srcImage[x*3]);
            double oldG = static_cast<double>(srcImage[x*3+1]);
            double oldR = static_cast<double>(srcImage[x*3+2]);

            // Put pt to next row
            srcImage = src.ptr<uchar>(y+1);

            // Old BGR in next row
            double oldB2 = static_cast<double>(srcImage[(x+1)*3]);
            double oldG2 = static_cast<double>(srcImage[(x+1)*3+1]);
            double oldR2 = static_cast<double>(srcImage[(x+1)*3+2]);

            // pt back
            srcImage = src.ptr<uchar>(y);
            double newB, newG, newR;
            if (oldB > 127.5){
                newB = oldB2 + (255 - oldB2) * ((oldB - 127.5) / 127.5);
            }
            else {
                newB = oldB2 - oldB2 * (127.5 - oldB) / 127.5;
            }

            if (oldG > 127.5){
                newG = oldG2 + (255 - oldG2) * ((oldG - 127.5) / 127.5);
            }
            else {
                newG = oldG2 - oldG2 * (127.5 - oldG) / 127.5;
            }

            if (oldR > 127.5){
                newR = oldR2 + (255 - oldR2) * ((oldR - 127.5) / 127.5);
            }
            else {
                newR = oldR2 - oldR2 * (127.5 - oldR) / 127.5;
            }

            srcImage[x*3] = static_cast<uchar>(newB);
            srcImage[x*3+1] = static_cast<uchar>(newG);
            srcImage[x*3+2] = static_cast<uchar>(newR);
        }
    }

    return src;
}


Mat softLight(Mat &srcImg) {
    Mat src;
    srcImg.copyTo(src);
    int width=src.cols;
    int heigh=src.rows;
    for(int y = 0; y < heigh-1; y++){
        uchar* srcImage = src.ptr<uchar>(y);

        for(int x = 0; x < width; x++){
            // Old BGR
            double oldB = srcImage[x*3];
            double oldG = static_cast<double>(srcImage[x*3+1]);
            double oldR = static_cast<double>(srcImage[x*3+2]);

            // Put pt to next row
            srcImage = src.ptr<uchar>(y+1);

            // Old BGR in next row
            double oldB2 = static_cast<double>(srcImage[(x+1)*3]);
            double oldG2 = static_cast<double>(srcImage[(x+1)*3+1]);
            double oldR2 = static_cast<double>(srcImage[(x+1)*3+2]);

            // pt back
            srcImage = src.ptr<uchar>(y);
            double newB, newG, newR;
            if (oldB > 127.5){
                newB = oldB2 + (255 - oldB2) * ((oldB - 127.5) / 127.5) * (0.5 - abs(oldB2 - 127.5) / 255);
            }
            else {
                newB = oldB2 - oldB2 * (127.5 - oldB) / 127.5 * (0.5 - abs(oldB2 - 127.5)/ 255);
            }

            if (oldG > 127.5){
                newG = oldG2 + (255 - oldG2) * ((oldG - 127.5) / 127.5) * (0.5 - abs(oldG2 - 127.5) / 255);
            }
            else {
                newG = oldG2 - oldG2 * (127.5 - oldG) / 127.5 * (0.5 - abs(oldG2 - 127.5)/ 255);
            }

            if (oldR > 127.5){
                newR = oldR2 + (255 - oldR2) * ((oldR - 127.5) / 127.5) * (0.5 - abs(oldR2 - 127.5) / 255);
            }
            else {
                newR = oldR2 - oldR2 * (127.5 - oldR) / 127.5 * (0.5 - abs(oldR2 - 127.5)/ 255);
            }

            srcImage[x*3] = static_cast<uchar>(newB);
            srcImage[x*3+1] = static_cast<uchar>(newG);
            srcImage[x*3+2] = static_cast<uchar>(newR);
        }
    }
    return src;
}

Mat beauty(Mat &srcImg){
    int beautyParam =3;
    int GuassBlurParam=1;

    Mat src;
    srcImg.copyTo(src);

    // Param1 for Mopi, Param2 for GuassBlur
    int param1 = beautyParam, param2 = GuassBlurParam;

    // bilateralFilter Param1
    int dx = param1 * 5;

    // bilateralFilter Param2
    double fc = param1 * 12.5;

    double p = static_cast<double>(0.1f);

    Mat tmpImg1, tmpImg2, tmpImg3, tmpImg4, tmpImg5, tmpImg6;

    //bilateralFilter (EPFFilter (src))
    bilateralFilter(src, tmpImg1, dx, fc, fc);

    // (EPFFilter (src)) - src
    subtract(tmpImg1, src, tmpImg2);

    // (EPFFilter (src)) - src + 128
    add(tmpImg2, Scalar(128, 128, 128), tmpImg3);

    //GuassBlur
    GaussianBlur(tmpImg3, tmpImg4, Size(2 * param1 - 1, 2 * param2 - 1), 0, 0);

    // Src + 2*GuassBlur -255
    tmpImg4.convertTo(tmpImg5, tmpImg4.type(), 2, -255);
    add(src, tmpImg5, tmpImg6);

    // *opacity / 100
    addWeighted(src, p, tmpImg6, 1 - p, 0.0, src);

    add(src, Scalar(10, 10, 10), src);

    return src;
}


//use random number to generate the replacing pixel
//use pixel value nearby to replce current pixel
Mat diffuse(Mat &srcImg){
    Mat src;
    //Random Number generator
    RNG rng;
    srcImg.copyTo(src);
    int width=src.cols;
    int heigh=src.rows;
    for (int y=1; y<heigh-1; y++){
        uchar* srcImage  = src.ptr<uchar>(y);
        for (int x=1; x<width-1; x++){
            //
            int tmp=rng.uniform(0,9);
            srcImage[3*x]=src.at<uchar>(y-1+tmp/3,3*(x-1+tmp%3));
            srcImage[3*x+1]=src.at<uchar>(y-1+tmp/3,3*(x-1+tmp%3)+1);
            srcImage[3*x+2]=src.at<uchar>(y-1+tmp/3,3*(x-1+tmp%3)+2);
        }
    }
    return src;
}


Mat sketch(Mat &srcImg){
    Mat src;
    srcImg.copyTo(src);
    int width=src.cols;
    int heigh=src.rows;
    Mat gray0,gray1;

    // Remove color
    cvtColor(src,gray0,COLOR_BGR2GRAY);

    // opposite color
    addWeighted(gray0,-1,NULL,0,255,gray1);

    // Gaussian blur
    GaussianBlur(gray1,gray1,Size(11,11),0);

    // Fuse operation
    Mat img(gray1.size(),CV_8UC1);
    for (int y=0; y<heigh; y++){
        uchar* grayImage0 = gray0.ptr<uchar>(y);
        uchar* grayImage1 = gray1.ptr<uchar>(y);
        uchar* srcImage = img.ptr<uchar>(y);
        for (int x=0; x<width; x++){
            int tmp0 = grayImage0[x];
            int tmp1 = grayImage1[x];
            srcImage[x] =static_cast<uchar>(min((tmp0+(tmp0*tmp1)/(256-tmp1)),255));
        }
    }
    return img;
}


Mat strike(Mat &srcImg){
    int strikeParam=25;
    Mat src;
    srcImg.copyTo(src);
    int width=src.cols;
    int heigh=src.rows;

    int strikeNum = strikeParam;//num：the strenth of avg operation

    Mat src1u[3];
    split(src,src1u);

    //strike center
    Point center(width/2,heigh/2);

    for (int y = 0; y < heigh; y++){
        uchar* srcImage = src.ptr<uchar>(y);
        for (int x = 0; x < width; x++){
            int tmp0 = 0, tmp1 = 0, tmp2 = 0;
            int R = static_cast<int>(norm(Point(x,y)-center));
            double angle = static_cast<double>(atan2(static_cast<double>(y-center.y),static_cast<double>(x-center.x)));

            for (int i=0; i < strikeNum; i++){
                int tmpR;
                if (R - i > 0){
                    tmpR = R - i;
                }else{
                    tmpR = 0;
                }

                int newX = static_cast<int>(tmpR*cos(angle) + center.x);
                int newY = static_cast<int>(tmpR*sin(angle) + center.y);

                // adjust out position
                if(newX < 0){
                    newX=0;
                }
                if(newX > width - 1){
                    newX=width-1;
                }
                if(newY < 0){
                    newY=0;
                }
                if(newY > heigh - 1){
                    newY=heigh-1;
                }

                tmp0 += src1u[0].at<uchar>(newY,newX);
                tmp1 += src1u[1].at<uchar>(newY,newX);
                tmp2 += src1u[2].at<uchar>(newY,newX);
            }
            srcImage[3*x]=static_cast<uchar>(tmp0/strikeNum);
            srcImage[3*x+1]=static_cast<uchar>(tmp1/strikeNum);
            srcImage[3*x+2]=static_cast<uchar>(tmp2/strikeNum);
        }
    }
    return src;
}


Mat volution(Mat &srcImg){
    int volutionParam=20;
    Mat src;
    srcImg.copyTo(src);
    int width = src.cols;
    int heigh = src.rows;

    int volutionNum = volutionParam;//num：the strength of avg operation;

    Mat src1u[3];
    split(src,src1u);

    //volution center
    Point center(width/2,heigh/2);

    for (int y=0; y < heigh; y++){
        uchar* srcImage = src.ptr<uchar>(y);
        for (int x=0; x < width; x++){
            int tmp0 = 0, tmp1 = 0, tmp2 = 0;
            int R = static_cast<int>(norm(Point(x,y)-center));
            double angle = static_cast<double>(atan2(static_cast<double>(y-center.y),static_cast<double>(x-center.x)));

            for (int i=0;i < volutionNum; i++){
                //step size
                angle += 0.01;

                int newX = static_cast<int>(R*cos(angle) + center.x);
                int newY = static_cast<int>(R*sin(angle) + center.y);

                if(newX<0)newX=0;
                if(newX>width-1)newX=width-1;
                if(newY<0)newY=0;
                if(newY>heigh-1)newY=heigh-1;

                tmp0 += src1u[0].at<uchar>(newY,newX);
                tmp1 += src1u[1].at<uchar>(newY,newX);
                tmp2 += src1u[2].at<uchar>(newY,newX);

            }
            srcImage[3*x]=static_cast<uchar>(tmp0/volutionNum);
            srcImage[3*x+1]=static_cast<uchar>(tmp1/volutionNum);
            srcImage[3*x+2]=static_cast<uchar>(tmp2/volutionNum);
        }
    }
    return src;
}


Mat wave(Mat &srcImg){
    int Aparam=10;
    int deltaParam=10;
    Mat src, src2;
    srcImg.copyTo(src);
    srcImg.copyTo(src2);
    int width = src.cols;
    int heigh = src.rows;

    double angle = 0.0;
    int deltaI = deltaParam;	//period;
    int A = Aparam;		//Amplitude;

    for (int y=0; y<heigh; y++){
        int changeX = static_cast<int>(A*sin(angle));
        uchar* srcImage = src.ptr<uchar>(y);
        uchar *srcImageCopy = src2.ptr<uchar>(y);
        for (int x=0; x<width; x++){
            if(changeX+x<width && changeX+x>0){
                srcImage[3*x]=srcImageCopy[3*(x+changeX)];
                srcImage[3*x+1]=srcImageCopy[3*(x+changeX)+1];
                srcImage[3*x+2]=srcImageCopy[3*(x+changeX)+2];
            }
             //empty place;
            else if(x<=changeX){
                srcImage[3*x]=srcImageCopy[0];
                srcImage[3*x+1]=srcImageCopy[1];
                srcImage[3*x+2]=srcImageCopy[2];
            }
            else if (x>=width-changeX){
                srcImage[3*x]=srcImageCopy[3*(width-1)];
                srcImage[3*x+1]=srcImageCopy[3*(width-1)+1];
                srcImage[3*x+2]=srcImageCopy[3*(width-1)+2];
            }

        }
        angle += (static_cast<double>(deltaI))/100;
    }
    return src;
}

Mat expand(Mat &srcImg){
    Mat src, src2;
    srcImg.copyTo(src);
    srcImg.copyTo(src2);
    int width = src.cols;
    int heigh = src.rows;
    Point center(width/2,heigh/2);

    int expandRate = static_cast<int>(sqrtf(width*width+heigh*heigh)/2);

    for (int y=0; y<heigh; y++){
        uchar* srcImage = src.ptr<uchar>(y);
        for (int x=0; x<width; x++){
            int distance = static_cast<int>(norm(Point(x,y)-center));
            if (distance<expandRate)
            {
                int newX = (x-center.x)*distance/expandRate+center.x;
                int newY = (y-center.y)*distance/expandRate+center.y;

                srcImage[3*x]=src2.at<uchar>(newY,newX*3);
                srcImage[3*x+1]=src2.at<uchar>(newY,newX*3+1);
                srcImage[3*x+2]=src2.at<uchar>(newY,newX*3+2);
            }
        }
    }
    return src;
}

Mat shrink(Mat &srcImg){
    Mat src, src2;
    srcImg.copyTo(src);
    srcImg.copyTo(src2);
    int width = src.cols;
    int heigh = src.rows;
    Point center(width/2,heigh/2);

    for (int y=0; y<heigh; y++){
        uchar* srcImage = src.ptr<uchar>(y);
        for (int x=0; x<width; x++){
            double theta = atan2(static_cast<double>(y-center.y),static_cast<double>(x-center.x));
            int shrinkRate = static_cast<int>(sqrtf( static_cast<float>(norm(Point(x,y)-center)) )*8);

            int newX = center.x + static_cast<int>(shrinkRate*cos(theta));

            int newY = center.y + static_cast<int>(shrinkRate*sin(theta));

            if(newX < 0){
                newX=0;
            }
            else if(newX >= width){
                newX = width-1;
            }
            if(newY < 0) {
                newY = 0;
            }
            else if(newY >= heigh) {
                newY = heigh-1;
            }

            srcImage[3*x]=src2.at<uchar>(newY,newX*3);
            srcImage[3*x+1]=src2.at<uchar>(newY,newX*3+1);
            srcImage[3*x+2]=src2.at<uchar>(newY,newX*3+2);

        }
    }
    return src;
}

Mat embossment(Mat &srcImg){
    Mat src, src2;
    srcImg.copyTo(src);
    srcImg.copyTo(src2);
    int width = src.cols;
    int heigh = src.rows;
    for (int y=1; y<heigh-1; y++){
        uchar* srcImage1 = src.ptr<uchar>(y);
        // pt to next row
        uchar* srcImage2 = src.ptr<uchar>(y+1);

        // pt to src2
        uchar* src2Image = src2.ptr<uchar>(y);
        for (int x=1; x<width-1; x++){
            for (int i=0; i<3; i++){
                int tmp = srcImage2[3*(x+1)+i] - srcImage1[3*(x-1)+i] + 128;
                if (tmp < 0){
                    src2Image[3*x+i]=0;
                }
                else if(tmp>255){
                    src2Image[3*x+i]= 255;
                }
                else{
                    src2Image[3*x+i]= static_cast<uchar>(tmp);
                }
            }
        }
    }
    return src2;
}


Mat carve(Mat &srcImg){
    Mat src, src2;
    srcImg.copyTo(src);
    srcImg.copyTo(src2);
    int width = src.cols;
    int heigh = src.rows;
    for (int y=1; y<heigh-1; y++){
        uchar* srcImage1 = src.ptr<uchar>(y);
        // pt to next row
        uchar* srcImage2 = src.ptr<uchar>(y+1);

        // pt to src2
        uchar* src2Image = src2.ptr<uchar>(y);
        for (int x=1; x<width-1; x++){
            for (int i=0; i<3; i++){
                int tmp = srcImage2[3*(x-1)+i] - srcImage1[3*(x+1)+i] + 128;
                if (tmp < 0){
                    src2Image[3*x+i]=0;
                }
                else if(tmp>255){
                    src2Image[3*x+i]= 255;
                }
                else{
                    src2Image[3*x+i]= static_cast<uchar>(tmp);
                }
            }
        }
    }
    return src2;
}
