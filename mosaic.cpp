#include "graph_scene.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <QGraphicsSceneMouseEvent>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;

/*
 * Implementation Note: mosaic
 * -------------------------
 * take 2 points  and  a image as input and
 * it will take these 2 points as diagonals and
 * use mosaic to mask the chosen area
 *
*/
void GraphScreen::mosaic(Point mosaicPtL, Point mosaicPtR, int neighbourHood){

    RNG rng;
    int randomNum; //邻域内随机值
    Mat imageSourceCopy =  QImage2cvMat(*ScreenPic);
    Mat img= imageSourceCopy.clone();

    int l,r,u,d;            //定义左右上下四个边界的值

    if(mosaicPtR.x < mosaicPtL.x){
        l = mosaicPtR.x;
        r =mosaicPtL.x;
    }else {
        l = mosaicPtL.x;
        r = mosaicPtR.x;
    }
    if(mosaicPtR.y > mosaicPtL.y){
        d = mosaicPtR.y;
        u = mosaicPtL.y;
    }else{
        d = mosaicPtL.y;
        u = mosaicPtR.y;
    }
    //对鼠标画出的矩形框超出图像范围做处理，否则会越界崩溃
    r > img.cols - 2 * neighbourHood ? r = img.cols - 2 * neighbourHood : r = r;
    d > img.rows - 2 * neighbourHood ? d = img.rows - 2 * neighbourHood : d = d;

    // ptR存储着图像右下角的坐标 ptL存储着图像左上角的坐标
    mosaicPtR = Point(r,d);
    mosaicPtL = Point(l,u);

    // 对height迭代
    for (int i = 0; i < mosaicPtR.y - mosaicPtL.y; i += neighbourHood)
    {
        //对weight迭代
        for (int j = 0; j < mosaicPtR.x - mosaicPtL.x; j += neighbourHood)
        {

            //模糊后的值为整个模糊block的均值
            randomNum = rng.uniform(-neighbourHood / 2, neighbourHood / 2);

            //根据neighbourhood与顶点坐标来模糊选定区域
            Rect rect = Rect(j + neighbourHood + mosaicPtL.x, i + neighbourHood + mosaicPtL.y, neighbourHood, neighbourHood);
            Mat roi = imageSourceCopy(rect);
            Scalar sca = Scalar(
                img.at<Vec3b>(i + randomNum + mosaicPtL.y, j + randomNum + mosaicPtL.x)[0],
                img.at<Vec3b>(i + randomNum + mosaicPtL.y, j + randomNum + mosaicPtL.x)[1],
                img.at<Vec3b>(i + randomNum + mosaicPtL.y, j + randomNum + mosaicPtL.x)[2]);
            Mat roiCopy = Mat(rect.size(), CV_8UC3, sca);
            roiCopy.copyTo(roi);
        }
    }
    Mat cloneimg = imageSourceCopy.clone();
    *ScreenPic = cvMat2QImage(cloneimg);
}


/*
 * Implementation Note:set_m_mosaic,set_mosaic_size
 * -------------------------
 * 2 methods to control the mosaic state and mosaic size
*/
void GraphScreen::set_m_mosaic(bool state){
    m_mosaic = state;
}

void GraphScreen::set_mosaic_size(int size){
    mosaic_size = size;
}
