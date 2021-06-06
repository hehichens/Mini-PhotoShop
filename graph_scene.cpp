#include "graph_scene.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <QGraphicsSceneMouseEvent>
#include <QMessageBox>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;

void GraphScreen::display(QImage* image){
    ScreenPic = image;
    this->addPixmap(QPixmap::fromImage(*image));
}

//move mouse event
void GraphScreen::mouseMoveEvent(QGraphicsSceneMouseEvent* event){
    if (m_crop){
        int mx = event->scenePos().x();
        int my = event->scenePos().y();
        Crop_m(mx,my);
        this->addPixmap(QPixmap::fromImage(*ScreenPic));
    }
}

void GraphScreen::mousePressEvent(QGraphicsSceneMouseEvent* event){
    int mx = event->scenePos().x();
    int my = event->scenePos().y();
    this->addPixmap(QPixmap::fromImage(*ScreenPic));
  
 if(m_addsticker){
    add_sticker(mx, my, sticker_size);
    this->addPixmap(QPixmap::fromImage(*ScreenPic));
    }

    else if (m_mosaic){
     if (mx>0 && my>0 && mx<ScreenPic->size().width() && my<ScreenPic->size().width()){
        mosaicPtL = Point(mx, my);
     }
    }
    else if (m_text){
        add_text(mx,my,text_size, text_content);
        this->addPixmap(QPixmap::fromImage(*ScreenPic));
    }
    else if (m_crop){
        if (mx>0 && my>0 && mx<ScreenPic->size().width() && my<ScreenPic->size().width()){
        Crop_p(mx,my);
        this->addPixmap(QPixmap::fromImage(*ScreenPic));
        }
    }
}


void GraphScreen::mouseReleaseEvent(QGraphicsSceneMouseEvent* event){
    int mx = event->scenePos().x();
    int my = event->scenePos().y();

    if(m_mosaic){
        if (mx>0 && my>0 && mx<ScreenPic->size().width() && my<ScreenPic->size().width()){
        mosaicPtR = Point(mx, my);
        mosaic(mosaicPtL, mosaicPtR, mosaic_size);
        this->addPixmap(QPixmap::fromImage(*ScreenPic));
        }
    }
        else if (m_crop){
        if (mx>0 && my>0 && mx<ScreenPic->size().width() && my<ScreenPic->size().width()){
        Crop_r(mx,my);
        this->display(ScreenPic);
        set_m_crop(false);
        }
    }
}

//format change between QImage & cvMat
Mat GraphScreen::QImage2cvMat(QImage image) {
    cv::Mat mat;
    cv::Mat dst;


    qDebug() << image.format();
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

QImage GraphScreen::cvMat2QImage(const cv::Mat& mat)
{

    // 8-bits unsigned, NO. OF CHANNELS = 1
    if(mat.type() == CV_8UC1)
    {
        QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
        // Set the color table (used to translate colour indexes to qRgb values)
        image.setColorCount(256);
        for(int i = 0; i < 256; i++)
        {
            image.setColor(i, qRgb(i, i, i));
        }
        // Copy input Mat
        uchar *pSrc = mat.data;
        for(int row = 0; row < mat.rows; row ++)
        {
            uchar *pDest = image.scanLine(row);
            memcpy(pDest, pSrc, mat.cols);
            pSrc += mat.step;
        }
        return image;
    }
    // 8-bits unsigned, NO. OF CHANNELS = 3
    else if(mat.type() == CV_8UC3)
    {
        // Copy input Mat
        cvtColor(mat, mat,COLOR_BGR2RGB);
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);

        return image;
    }
    else if(mat.type() == CV_8UC4)
    {
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        return image.copy();
    }
    else
    {
        return QImage();
    }
}
