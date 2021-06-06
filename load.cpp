//#include "load.h"

//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>

//#include <iostream>

///*ran*/
//#include <QFileDialog>
//#include <QtWidgets>
//#include <QtCore>
//#include <QVBoxLayout>
//#include <QPushButton>
//#include <QToolButton>
//#include <QIcon>
//#include <QString>
///*ran*/

//load::~load()
//{
//    delete ui;
//}





//load::load(QWidget *parent):
//    QMainWindow(parent),
//    ui(new Ui::load)
//{

//ui->setupUi(this);

///*ran*/

///*
// * set size of load button and scroll area
// */
//ui->load_button->setFixedSize(QSize(50, 50));
//ui->scrollArea->setFixedSize(QSize(120, 200));

//connect(ui->load_button, SIGNAL(clicked()), this, SLOT(add_image_button()));

//}

///*
// * when the load_button is clicked, it will ask the user to pick
// * an image and show it as a image button in the scroll area
// */
//void load::add_image_button()
//{
//    int i = num;
//    num++;
//    std::cout<<i<<std::endl;
//    QString filename(get_imagefile_name());

//    listButtons.push_back(new QToolButton());
//    QImage* img = new QImage, * scaledimg = new QImage;

//    if(! ( img->load(filename) ) )
//    {
//        QMessageBox::information(this,
//                                 tr("error message"),
//                                 tr("fail to load the image!"));
//        delete img;
//        return;
//    }

//    int Owidth = img->width(),Oheight = img->height();
//    int Fwidth, Fheight;           //the new image size
//    int Mul;

//    if (Owidth >= Oheight) Mul = Owidth/55;
//    else Mul = Oheight/55;

//    Fwidth = Owidth/Mul;
//    Fheight = Oheight/Mul;

//    *scaledimg = img->scaled(Fwidth,Fheight,Qt::KeepAspectRatio);

//    listButtons[i]->setFixedSize(QSize(55, 55));
//    listButtons[i]->setIcon(QPixmap::fromImage(*img));
//    listButtons[i]->setIconSize(QSize(Fwidth, Fheight));

//    ui->addpic_layout->addWidget(listButtons[i]);

//    connect(listButtons[i],SIGNAL(clicked()), buttonMapper, SLOT(map()));
//    buttonMapper->setMapping(listButtons[i], filename);
//    connect(buttonMapper, SIGNAL(mapped(QString)), this, SLOT(display_image(QString)));
//}

//void load::on_button_clicked(){
//    std::cout<<"testing_button"<<std::endl;
//}

///*
// * when the load_button is clicked,
// * this function will get the name of the image
// */
//QString load::get_imagefile_name()
//{
//    QFileDialog dialog(this);
//    dialog.setNameFilter(tr("Images (*.png *.xpm *.jpg *.jpeg)"));
//    dialog.setViewMode(QFileDialog::Detail);
//    QString fileName = QFileDialog::getOpenFileName(this,
//       tr("Open Images"), "/home/rpi/Desktop/Picture/Sample Pictures", tr("Image Files (*.png *.jpg *.jpeg *.bmp)"));
//    if (!fileName.isEmpty())
//    {
//        return fileName;
//    }
//}

///*
// * display the image on the canvas
// */
//void load::display_image(QString filename)
//{   //QString filename = "/Users/rose/Desktop/photo.jpeg";
//    QImage* image = new QImage,* scaledimg = new QImage;
//    if(! ( image->load(filename) ) )
//            {
//                QMessageBox::information(this,
//                                         tr("error message"),
//                                         tr("fail to load the image!"));
//                qDebug()<<"error";
//                delete image;
//                return;
//            }

//    //ui->canvas->setGeometry(0,0,350,350);
////    ui->canvas->setPixmap(QPixmap::fromImage(*image));
//}

///*ran*/
