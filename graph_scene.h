/*
 * File: graph_scene.h
 * -------------------
 * This file exports the GraphScreen class, which
 * is a subclass of QGraphicsScene. It is responsible
 * for mouse control on the canvas.
 */

#ifndef GRAPH_SCENE_H
#define GRAPH_SCENE_H

#include <QWidget>
#include <QPixmap>
#include <QTextEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QFileDialog>
#include <QToolButton>
#include <QLabel>
#include <QImage>
#include <QObject>
#include <QSignalMapper>
#include <QImage>
#include <QGraphicsItem>
#include <stack>
#include "button.h"
#include "ui_main_window.h"
#include <QMouseEvent>
#include<opencv2/opencv.hpp>
#include <QString>

using namespace cv;
using namespace std;

void onMouse(int event, int x, int y, int flags, void *);
Mat crop(Mat org);

class GraphScreen : public QGraphicsScene
{
    Q_OBJECT

    public:

        QImage *ScreenPic;
        void display(QImage * image);
        void add_sticker(int mx,int my,int size);
        void set_m_addsticker(bool state);
        void set_m_crop(bool state);
        void select_sticker(int sticker_idx);
        void set_sticker_size(int size);

        void set_m_mosaic(bool state);
        void mosaic(Point mosaicPTL, Point mosaicPTR, int neighbourHood);
        void set_mosaic_size(int size);
        void set_m_text(bool state);
        void add_text(int mx,int my, int size,QString text_content);
        void set_text_content(QString content);
        void set_text_size(int size);

        void Crop_r(int x, int y);
        void Crop_m(int x, int y);
        void Crop_p(int x, int y);

        Mat QImage2cvMat(QImage image);
        QImage cvMat2QImage(const cv::Mat& mat);

        Point mosaicPtL; //马赛克时左键按下时坐标
        Point mosaicPtR;


    private:

        bool m_addsticker = false;
        bool m_mosaic = false;
        bool m_text = false;
        bool m_crop = false;
        Mat sticker_img;
        int sticker_size = 50;
        int mosaic_size = 10;
        int text_size = 20;
        QString text_content = "Text";


    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent* event);
        void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
        void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

#endif // GRAPH_SCENE_H
