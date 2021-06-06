#include "main_window.h"
#include <iostream>
#include <QFileDialog>
#include <QtWidgets>
#include <QtCore>
#include <QVBoxLayout>
#include <QPushButton>
#include <QToolButton>
#include <QIcon>
#include <QImage>
#include <QString>
#include "string.h"
#include "graph_scene.h"
#include "big_eye.h"
#include "collage.h"
#include "add_frame.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <time.h>
using namespace cv;
using namespace std;


/*
 * Implementation notes: main_window constructor
 * ------------------------------------------------
 * The constructor creates an GUI interface with initialized settings.
 */
main_window::main_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::main_window)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setAddition();
    setMainButtons();
    setDicText();
    Set_Filter();
    Set_Tool();
    Set_Sticker();
    Set_Mosaic();
    Set_Frame();
    Set_background();

    QPalette pal = this->palette();
    pal.setBrush(QPalette::Background,QBrush(QPixmap(":/images/background5.jpeg")));
    setPalette(pal);
}

main_window::~main_window()
{
    delete ui;
}

/*
 * Implementation notes: setMainButtons()
 * ------------------------------------------------
 * Set main functional buttons.
 */
void main_window::setMainButtons(){
    ui->horizontalLayout->addWidget(return_Button);
    ui->horizontalLayout->addWidget(changeSize_Button);
    ui->horizontalLayout->addWidget(close_Button);

    return_Button->setButtonPicture(return_Img);
    return_Button->setPressPicture(return_PressImg);
    close_Button->setButtonPicture(close_Img);
    close_Button->setPressPicture(close_PressImg);
    changeSize_Button->setButtonPicture(large_Img);
    changeSize_Button->setPressPicture(large_PressImg);
    return_Button->setIconSize(QSize(30,30));
    close_Button->setIconSize(QSize(30,30));
    changeSize_Button->setIconSize(QSize(30,30));


    ui->verticalLayout_4->addWidget(Tool_Button);
    ui->verticalLayout_4->addWidget(Filter_Button);
    ui->verticalLayout_4->addWidget(Sticker_Button);
    ui->verticalLayout_4->addWidget(Text_Button);
    ui->verticalLayout_4->addWidget(Bigeye_Button);
    ui->verticalLayout_4->addWidget(Frame_Button);
    ui->verticalLayout_4->addWidget(Mosaic_Button);
    ui->verticalLayout_4->addWidget(Colorchange_Button);
    ui->verticalLayout_4->addWidget(Collage_Button);

    ui->scrollArea->setFixedSize(QSize(120, 170));
    ui->widget_2->setFixedSize(QSize(120, 170));
    ui->load_button->setFixedSize(QSize(50, 50));
    ui->top_layout->setContentsMargins(5,5,5,5);

    ui->horizontalLayout_5->addWidget(Undo_Button);
    ui->horizontalLayout_5->addWidget(Redo_Button);
    ui->horizontalLayout_5->addWidget(TempSave_Button);
    ui->horizontalLayout_5->addWidget(Delete_Button);
    ui->horizontalLayout_5->addWidget(Download_Button);


    Tool_Button->setButtonPicture(Tool_Img);
    Tool_Button->setPressPicture(Tool_PressImg);

    Filter_Button->setButtonPicture(Filter_Img);
    Filter_Button->setPressPicture(Filter_PressImg);
    Sticker_Button->setButtonPicture(Sticker_Img);
    Sticker_Button->setPressPicture(Sticker_PressImg);
    Text_Button->setButtonPicture(Text_Img);
    Text_Button->setPressPicture(Text_PressImg);
    Bigeye_Button->setButtonPicture(Bigeye_Img);
    Bigeye_Button->setPressPicture(Bigeye_PressImg);

    Frame_Button->setButtonPicture(Frame_Img);
    Frame_Button->setPressPicture(Frame_PressImg);

    Mosaic_Button->setButtonPicture(Mosaic_Img);
    Mosaic_Button->setPressPicture(Mosaic_PressImg);
    Colorchange_Button->setButtonPicture(BackColor_Img);
    Colorchange_Button->setPressPicture(BackColor_PressImg);
    Collage_Button->setButtonPicture(Collage_Img);
    Collage_Button->setPressPicture(Collage_PressImg);

    Undo_Button->setButtonPicture(undo_Img);
    Undo_Button->setPressPicture(undo_PressImg);
    Redo_Button->setButtonPicture(redo_Img);
    Redo_Button->setPressPicture(redo_PressImg);
    TempSave_Button->setButtonPicture(tempsave_Img);
    TempSave_Button->setPressPicture(tempsave_PressImg);
    Delete_Button->setButtonPicture(delete_Img);
    Delete_Button->setPressPicture(delete_PressImg);
    Download_Button->setButtonPicture(download_Img);
    Download_Button->setPressPicture(download_PressImg);
    Undo_Button->setIconSize(QSize(40,40));
    Redo_Button->setIconSize(QSize(40,40));
    TempSave_Button->setIconSize(QSize(40,40));
    Delete_Button->setIconSize(QSize(40,40));
    Download_Button->setIconSize(QSize(40,40));

    connect(changeSize_Button, SIGNAL(released()), this, SLOT(changeWindowSize()));
    connect(close_Button, SIGNAL(released()), this, SLOT(close()));
    connect(return_Button, SIGNAL(released()), this, SLOT(Hide_Filter()));
    connect(return_Button, SIGNAL(released()), this, SLOT(Hide_Tool()));
    connect(return_Button, SIGNAL(released()), this, SLOT(Hide_Sticker()));
    connect(return_Button, SIGNAL(released()), this, SLOT(Hide_Mosaic()));
    connect(return_Button, SIGNAL(released()), this, SLOT(Hide_Frame()));
    connect(return_Button, SIGNAL(released()), this, SLOT(Hide_FilterColor_Button()));
    connect(return_Button, SIGNAL(released()), this, SLOT(Hide_Bright_Slider()));
    connect(return_Button, SIGNAL(released()), this, SLOT(Hide_Contrast_Slider()));
    connect(return_Button, SIGNAL(released()), this, SLOT(Hide_Blur_Slider()));
    connect(return_Button, SIGNAL(released()), this, SLOT(Hide_Saturation_Slider()));
    connect(return_Button, SIGNAL(released()), this, SLOT(Hide_crop()));
    connect(return_Button, SIGNAL(released()), this, SLOT(Hide_Rotate_Button()));
    connect(return_Button, SIGNAL(released()), this, SLOT(Hide_background()));
    connect(return_Button, SIGNAL(released()), this, SLOT(ButtonShow()));
    connect(return_Button, SIGNAL(released()), this, SLOT(Hide_eyeSlider()));
    connect(return_Button, SIGNAL(released()), this, SLOT(Hide_text()));
    connect(return_Button, SIGNAL(released()), this, SLOT(initialization()));

    connect(Tool_Button, SIGNAL(released()), this, SLOT(ButtonHide()));
    connect(Tool_Button, SIGNAL(released()), this, SLOT(Hide_eyeSlider()));
    connect(Tool_Button, SIGNAL(released()), this, SLOT(Hide_collageButton()));
    connect(Tool_Button, SIGNAL(released()), this, SLOT(Hide_text()));
    connect(Tool_Button, SIGNAL(released()), this, SLOT(Show_Tool()));

    connect(Filter_Button, SIGNAL(released()), this, SLOT(ButtonHide()));
    connect(Filter_Button, SIGNAL(released()), this, SLOT(Hide_eyeSlider()));
    connect(Filter_Button, SIGNAL(released()), this, SLOT(Hide_collageButton()));
    connect(Filter_Button, SIGNAL(released()), this, SLOT(Hide_text()));
    connect(Filter_Button, SIGNAL(released()), this, SLOT(Show_Filter()));

    connect(Sticker_Button, SIGNAL(released()), this, SLOT(ButtonHide()));
    connect(Sticker_Button, SIGNAL(released()), this, SLOT(Hide_eyeSlider()));
    connect(Sticker_Button, SIGNAL(released()), this, SLOT(Hide_collageButton()));
    connect(Sticker_Button, SIGNAL(released()), this, SLOT(Hide_text()));
    connect(Sticker_Button, SIGNAL(released()), this, SLOT(Show_Sticker()));

    connect(Bigeye_Button, SIGNAL(released()), this, SLOT(Show_eyeSlider()));
    connect(Bigeye_Button, SIGNAL(released()), this, SLOT(Hide_collageButton()));
    connect(Bigeye_Button, SIGNAL(released()), this, SLOT(Hide_text()));
    connect(Bigeye_Button, SIGNAL(released()), this, SLOT(Big_eye()));

    connect(Mosaic_Button, SIGNAL(released()), this, SLOT(ButtonHide()));
    connect(Mosaic_Button, SIGNAL(released()), this, SLOT(Hide_eyeSlider()));
    connect(Mosaic_Button, SIGNAL(released()), this, SLOT(Hide_collageButton()));
    connect(Mosaic_Button, SIGNAL(released()), this, SLOT(Hide_text()));
    connect(Mosaic_Button, SIGNAL(released()), this, SLOT(Show_Mosaic()));

    connect(Frame_Button, SIGNAL(released()), this, SLOT(ButtonHide()));
    connect(Frame_Button, SIGNAL(released()), this, SLOT(Hide_eyeSlider()));
    connect(Frame_Button, SIGNAL(released()), this, SLOT(Hide_collageButton()));
    connect(Frame_Button, SIGNAL(released()), this, SLOT(Hide_text()));
    connect(Frame_Button, SIGNAL(released()), this, SLOT(Show_Frame()));

    connect(Collage_Button, SIGNAL(released()), this, SLOT(Hide_eyeSlider()));
    connect(Collage_Button, SIGNAL(released()), this, SLOT(Hide_text()));
    connect(Collage_Button, SIGNAL(released()), this, SLOT(Show_collageButton()));
    connect(Collage_Button, SIGNAL(released()), this, SLOT(Collage()));

    connect(Colorchange_Button, SIGNAL(released()), this, SLOT(ButtonHide()));
    connect(Colorchange_Button, SIGNAL(released()), this, SLOT(Hide_eyeSlider()));
    connect(Colorchange_Button, SIGNAL(released()), this, SLOT(Hide_text()));
    connect(Colorchange_Button, SIGNAL(released()), this, SLOT(Hide_collageButton()));
    connect(Colorchange_Button, SIGNAL(released()), this, SLOT(Show_background()));

    connect(Text_Button, SIGNAL(released()), this, SLOT(Hide_eyeSlider()));
    connect(Text_Button, SIGNAL(released()), this, SLOT(Hide_collageButton()));
    connect(Text_Button, SIGNAL(released()), this, SLOT(Show_text()));
    connect(Text_Button, SIGNAL(released()), this, SLOT(text()));

    connect(ui->load_button, SIGNAL(clicked()), this, SLOT(add_image_button()));

    //rotate
    connect(tool_button_RT, SIGNAL(released()), this, SLOT(Hide_Bright_Slider()));
    connect(tool_button_RT, SIGNAL(released()), this, SLOT(Hide_Saturation_Slider()));
    connect(tool_button_RT, SIGNAL(released()), this, SLOT(Hide_Contrast_Slider()));
    connect(tool_button_RT, SIGNAL(released()), this, SLOT(Hide_Blur_Slider()));
    connect(tool_button_RT, SIGNAL(released()), this, SLOT(Hide_FilterColor_Button()));
    connect(tool_button_RT, SIGNAL(released()), this, SLOT(Hide_crop()));
    connect(tool_button_RT, SIGNAL(released()), this, SLOT(Show_Rotate_Button()));

    //crop
    connect(tool_button_CP, SIGNAL(released()), this, SLOT(Hide_Bright_Slider()));
    connect(tool_button_CP, SIGNAL(released()), this, SLOT(Hide_Saturation_Slider()));
    connect(tool_button_CP, SIGNAL(released()), this, SLOT(Hide_Contrast_Slider()));
    connect(tool_button_CP, SIGNAL(released()), this, SLOT(Hide_Blur_Slider()));
    connect(tool_button_CP, SIGNAL(released()), this, SLOT(Hide_FilterColor_Button()));
    connect(tool_button_CP, SIGNAL(released()), this, SLOT(Hide_Rotate_Button()));
    connect(tool_button_CP, SIGNAL(released()), this, SLOT(Show_crop()));
    connect(tool_button_CP, SIGNAL(released()), this, SLOT(Tool_crop()));

    //black_white
    connect(tool_button_BW, SIGNAL(released()), this, SLOT(Tool_blackwhite()));
    connect(tool_button_BW, SIGNAL(released()), this, SLOT(Hide_Bright_Slider()));
    connect(tool_button_BW, SIGNAL(released()), this, SLOT(Hide_Saturation_Slider()));
    connect(tool_button_BW, SIGNAL(released()), this, SLOT(Hide_Contrast_Slider()));
    connect(tool_button_BW, SIGNAL(released()), this, SLOT(Hide_Blur_Slider()));
    connect(tool_button_BW, SIGNAL(released()), this, SLOT(Hide_FilterColor_Button()));
    connect(tool_button_BW, SIGNAL(released()), this, SLOT(Hide_crop()));
    connect(tool_button_BW, SIGNAL(released()), this, SLOT(Hide_Rotate_Button()));

    //Brightness
    connect(tool_button_BR, SIGNAL(released()), this, SLOT(Tool_brightness()));
    connect(tool_button_BR, SIGNAL(released()), this, SLOT(Show_Bright_Slider()));
    connect(tool_button_BR, SIGNAL(released()), this, SLOT(Hide_Contrast_Slider()));
    connect(tool_button_BR, SIGNAL(released()), this, SLOT(Hide_Blur_Slider()));
    connect(tool_button_BR, SIGNAL(released()), this, SLOT(Hide_Saturation_Slider()));
    connect(tool_button_BR, SIGNAL(released()), this, SLOT(Hide_FilterColor_Button()));
    connect(tool_button_BR, SIGNAL(released()), this, SLOT(Hide_Rotate_Button()));
    connect(tool_button_BR, SIGNAL(released()), this, SLOT(Hide_crop()));

    //contrast
    connect(tool_button_CT, SIGNAL(released()), this, SLOT(Tool_contrast()));
    connect(tool_button_CT, SIGNAL(released()), this, SLOT(Show_Contrast_Slider()));
    connect(tool_button_CT, SIGNAL(released()), this, SLOT(Hide_Blur_Slider()));
    connect(tool_button_CT, SIGNAL(released()), this, SLOT(Hide_Saturation_Slider()));
    connect(tool_button_CT, SIGNAL(released()), this, SLOT(Hide_Bright_Slider()));
    connect(tool_button_CT, SIGNAL(released()), this, SLOT(Hide_FilterColor_Button()));
    connect(tool_button_CT, SIGNAL(released()), this, SLOT(Hide_Rotate_Button()));
    connect(tool_button_CT, SIGNAL(released()), this, SLOT(Hide_crop()));

    //color filter
    connect(tool_button_FT, SIGNAL(released()), this, SLOT(Hide_Contrast_Slider()));
    connect(tool_button_FT, SIGNAL(released()), this, SLOT(Hide_Blur_Slider()));
    connect(tool_button_FT, SIGNAL(released()), this, SLOT(Hide_Saturation_Slider()));
    connect(tool_button_FT, SIGNAL(released()), this,SLOT(Hide_Bright_Slider()));
    connect(tool_button_FT, SIGNAL(released()), this, SLOT(Show_FilterColor_Button()));
    connect(tool_button_FT, SIGNAL(released()), this, SLOT(Hide_Rotate_Button()));
    connect(tool_button_FT, SIGNAL(released()), this, SLOT(Hide_crop()));

    //saturation
    connect(tool_button_ST, SIGNAL(released()), this, SLOT(Tool_saturation()));
    connect(tool_button_ST, SIGNAL(released()), this, SLOT(Hide_Contrast_Slider()));
    connect(tool_button_ST, SIGNAL(released()), this, SLOT(Hide_Blur_Slider()));
    connect(tool_button_ST, SIGNAL(released()), this,SLOT(Hide_Bright_Slider()));
    connect(tool_button_ST, SIGNAL(released()), this, SLOT(Hide_FilterColor_Button()));
    connect(tool_button_ST, SIGNAL(released()), this, SLOT(Show_Saturation_Slider()));
    connect(tool_button_ST, SIGNAL(released()), this, SLOT(Hide_Rotate_Button()));
    connect(tool_button_ST, SIGNAL(released()), this, SLOT(Hide_crop()));

    //blur
    connect(tool_button_BL, SIGNAL(released()), this, SLOT(Tool_blur()));
    connect(tool_button_BL, SIGNAL(released()), this, SLOT(Show_Blur_Slider()));
    connect(tool_button_BL, SIGNAL(released()), this, SLOT(Hide_Contrast_Slider()));
    connect(tool_button_BL, SIGNAL(released()), this, SLOT(Hide_Saturation_Slider()));
    connect(tool_button_BL, SIGNAL(released()), this, SLOT(Hide_Bright_Slider()));
    connect(tool_button_BL, SIGNAL(released()), this, SLOT(Hide_FilterColor_Button()));
    connect(tool_button_BL, SIGNAL(released()), this, SLOT(Hide_Rotate_Button()));
    connect(tool_button_BL, SIGNAL(released()), this, SLOT(Hide_crop()));
}


/*
 * Implementation notes: setAddition()
 * ------------------------------------------------
 * Set components which are shown after functional buttons are pushed.
 */
void main_window::setAddition(){
    //brightness
    ui->horizontalLayout->addWidget(spinBox1);
    ui->horizontalLayout->addWidget(slider1);
    spinBox1->setRange(0,100);
    slider1->setRange(0,100);
    connect(spinBox1, SIGNAL(valueChanged(int)), slider1, SLOT(setValue(int)));
    connect(slider1, SIGNAL(valueChanged(int)), spinBox1, SLOT(setValue(int)));
    spinBox1->setVisible(false);
    slider1->setVisible(false);

    //contrast
    ui->horizontalLayout->addWidget(spinBox2);
    ui->horizontalLayout->addWidget(slider2);
    spinBox2->setRange(0,30);
    slider2->setRange(0,30);
    connect(spinBox2, SIGNAL(valueChanged(int)), slider2, SLOT(setValue(int)));
    connect(slider2, SIGNAL(valueChanged(int)), spinBox2, SLOT(setValue(int)));
    spinBox2->setVisible(false);
    slider2->setVisible(false);

    //blur
    ui->horizontalLayout->addWidget(spinBox_blur);
    ui->horizontalLayout->addWidget(slider_blur);
    spinBox_blur->setRange(0,30);
    slider_blur->setRange(0,30);
    connect(spinBox_blur, SIGNAL(valueChanged(int)), slider_blur, SLOT(setValue(int)));
    connect(slider_blur, SIGNAL(valueChanged(int)), spinBox_blur, SLOT(setValue(int)));
    spinBox_blur->setVisible(false);
    slider_blur->setVisible(false);

    //saturation
    ui->horizontalLayout->addWidget(spinBox_saturation);
    ui->horizontalLayout->addWidget(slider_saturation);
    spinBox_saturation->setRange(-100,100);
    slider_saturation->setRange(-100,100);
    connect(spinBox_saturation, SIGNAL(valueChanged(int)), slider_saturation, SLOT(setValue(int)));
    connect(slider_saturation, SIGNAL(valueChanged(int)), spinBox_saturation, SLOT(setValue(int)));
    spinBox_saturation->setVisible(false);
    slider_saturation->setVisible(false);

    //crop
    ui->horizontalLayout->addWidget(crop_Button);
    crop_Button->setButtonPicture(confirm_Img);
    crop_Button->setPressPicture(confirm_PressImg);
    crop_Button->setButtonSize(30,30);
    crop_Button->setVisible(false);

    //rotate
    ui->horizontalLayout->addWidget(LeftRotate_Button);
    ui->horizontalLayout->addWidget(RightRotate_Button);
    ui->horizontalLayout->addWidget(HorizontalFlip_Button);
    ui->horizontalLayout->addWidget(VerticalFlip_Button);
    ui->horizontalLayout->addWidget(DiagonalFlip_Button);

    LeftRotate_Button->setIconSize(QSize(80,40));
    RightRotate_Button->setIconSize(QSize(80,40));
    HorizontalFlip_Button->setIconSize(QSize(80,40));
    DiagonalFlip_Button->setIconSize(QSize(80,40));
    VerticalFlip_Button->setIconSize(QSize(80,40));

    LeftRotate_Button->setText("Left Rotate");
    RightRotate_Button->setText("Right Rotate");
    HorizontalFlip_Button->setText("Horizontal Flip");
    VerticalFlip_Button->setText("Vertical Flip");
    DiagonalFlip_Button->setText("Diagonal Flip");

    LeftRotate_Button->setVisible(false);
    RightRotate_Button->setVisible(false);
    HorizontalFlip_Button->setVisible(false);
    VerticalFlip_Button->setVisible(false);
    DiagonalFlip_Button->setVisible(false);

    connect(LeftRotate_Button, SIGNAL(released()), this, SLOT(Tool_rotate()));
    connect(RightRotate_Button, SIGNAL(released()), this, SLOT(Tool_rotate()));
    connect(HorizontalFlip_Button, SIGNAL(released()), this, SLOT(Tool_rotate()));
    connect(VerticalFlip_Button, SIGNAL(released()), this, SLOT(Tool_rotate()));
    connect(DiagonalFlip_Button, SIGNAL(released()), this, SLOT(Tool_rotate()));

    //Color Filter
    ui->horizontalLayout->addWidget(cf_red);
    ui->horizontalLayout->addWidget(cf_orange);
    ui->horizontalLayout->addWidget(cf_yellow);
    ui->horizontalLayout->addWidget(cf_green);
    ui->horizontalLayout->addWidget(cf_blue);
    ui->horizontalLayout->addWidget(cf_purple);
    ui->horizontalLayout->addWidget(cf_pink);

    cf_red->setButtonPicture(red_Img);
    cf_red->setPressPicture(red_Img);
    cf_orange->setButtonPicture(orange_Img);
    cf_orange->setPressPicture(orange_Img);
    cf_yellow->setButtonPicture(yellow_Img);
    cf_yellow->setPressPicture(yellow_Img);
    cf_green->setButtonPicture(green_Img);
    cf_green->setPressPicture(green_Img);
    cf_blue->setButtonPicture(blue_Img);
    cf_blue->setPressPicture(blue_Img);
    cf_purple->setButtonPicture(purple_Img);
    cf_purple->setPressPicture(purple_Img);
    cf_pink->setButtonPicture(pink_Img);
    cf_pink->setPressPicture(pink_Img);

    cf_red->setButtonSize(40,40);
    cf_orange->setButtonSize(40,40);
    cf_yellow->setButtonSize(40,40);
    cf_green->setButtonSize(40,40);
    cf_blue->setButtonSize(40,40);
    cf_purple->setButtonSize(40,40);
    cf_pink->setButtonSize(40,40);

    cf_red->setVisible(false);
    cf_orange->setVisible(false);
    cf_yellow->setVisible(false);
    cf_green->setVisible(false);
    cf_blue->setVisible(false);
    cf_purple->setVisible(false);
    cf_pink->setVisible(false);

    connect(cf_red, SIGNAL(released()), this, SLOT(Tool_cf()));
    connect(cf_orange, SIGNAL(released()), this, SLOT(Tool_cf()));
    connect(cf_yellow, SIGNAL(released()), this, SLOT(Tool_cf()));
    connect(cf_green, SIGNAL(released()), this, SLOT(Tool_cf()));
    connect(cf_blue, SIGNAL(released()), this, SLOT(Tool_cf()));
    connect(cf_purple, SIGNAL(released()), this, SLOT(Tool_cf()));
    connect(cf_pink, SIGNAL(released()), this, SLOT(Tool_cf()));

    //Sticker
    ui->horizontalLayout->addWidget(spinBox_sticker);
    ui->horizontalLayout->addWidget(slider_sticker);
    spinBox_sticker->setRange(0,100);
    slider_sticker->setRange(0,100);
    connect(spinBox_sticker, SIGNAL(valueChanged(int)), slider_sticker, SLOT(setValue(int)));
    connect(slider_sticker, SIGNAL(valueChanged(int)), spinBox_sticker, SLOT(setValue(int)));
    spinBox_sticker->setVisible(false);
    slider_sticker->setVisible(false);

    connect(sticker1, SIGNAL(released()), this, SLOT(Sticker_Add()));
    connect(sticker2, SIGNAL(released()), this, SLOT(Sticker_Add()));
    connect(sticker3, SIGNAL(released()), this, SLOT(Sticker_Add()));
    connect(sticker4, SIGNAL(released()), this, SLOT(Sticker_Add()));
    connect(sticker5, SIGNAL(released()), this, SLOT(Sticker_Add()));
    connect(sticker6, SIGNAL(released()), this, SLOT(Sticker_Add()));
    connect(sticker7, SIGNAL(released()), this, SLOT(Sticker_Add()));

    //big eye
    ui->horizontalLayout->addWidget(spinBox_eye);
    ui->horizontalLayout->addWidget(slider_eye);
    spinBox_eye->setRange(0,15);
    slider_eye->setRange(0,15);
    connect(spinBox_eye, SIGNAL(valueChanged(int)), slider_eye, SLOT(setValue(int)));
    connect(slider_eye, SIGNAL(valueChanged(int)), spinBox_eye, SLOT(setValue(int)));
    spinBox_eye->setVisible(false);
    slider_eye->setVisible(false);

    //text
    ui->horizontalLayout->addWidget(textEdt);
    textEdt->setStyleSheet("color:black");//文本颜色
    textEdt->setStyleSheet("background-color:white");//背景色
    textEdt->setVisible(false);

    ui->horizontalLayout->addWidget(spinBoxText);
    spinBoxText->setRange(0,60);
    spinBoxText->setVisible(false);

    //collage
    ui->horizontalLayout->addWidget(collage_h);
    ui->horizontalLayout->addWidget(collage_v);
    collage_h->setVisible(false);
    collage_v->setVisible(false);
    connect(collage_h, SIGNAL(released()), this, SLOT(Collage()));
    connect(collage_v, SIGNAL(released()), this, SLOT(Collage()));
    collage_h->setButtonSize(120,30);
    collage_v->setButtonSize(120,30);
    collage_h->setButtonPicture(collageH_Img);
    collage_h->setPressPicture(collageH_Img);
    collage_v->setButtonPicture(collageV_Img);
    collage_v->setPressPicture(collageV_Img);

    //undoredo save
    connect(Undo_Button, SIGNAL(released()), this, SLOT(UndoAction()));
    connect(Redo_Button, SIGNAL(released()), this, SLOT(RedoAction()));
    connect(TempSave_Button, SIGNAL(released()), this, SLOT(DoAction()));
    connect(Download_Button, SIGNAL(released()), this, SLOT(DownloadAction()));
    connect(Delete_Button, SIGNAL(released()), this, SLOT(DeleteAction()));
}

/*
 * Implementation notes: changeWindowSize()
 * ------------------------------------------------
 * Allow Adjustment of the GUI interface size.
 */
void main_window::changeWindowSize()
{
    if(notChange){
        setWindowState(Qt::WindowMaximized );
        changeSize_Button->setButtonPicture(small_Img);
        changeSize_Button->setPressPicture(small_PressImg);
    }else {
        setWindowState(Qt::WindowNoState );
        changeSize_Button->setButtonPicture(large_Img);
        changeSize_Button->setPressPicture(large_PressImg);
    }
    notChange = !notChange;
}

void main_window::MainClose(){
    close();
}

/*
 * Implementation notes: setDicText()
 * ------------------------------------------------
 * Generate a random integer from 0 to 9, to set different dictums
 * on text editor.
 */
void main_window::setDicText(){
    srand(time(0));
    int seed = rand() % 11;
    ui->horizontalLayout_4->addWidget(dictum);
    QPalette p = dictum->palette();
    p.setBrush(QPalette::Base,QBrush(QColor(255,0,0,0)));
    dictum->setPalette(p);
    dictum->setTextColor(Qt::white);
    if (seed==0){
    dictum->setText("In order to be irreplaceable, one must always be different. -- Coco Chanel");
    }
    else if (seed==1){
    dictum->setText("Be the change that you wish to see in the world. -- Mahatma Gandhi");
    }
    else if (seed==2){
    dictum->setText("Spread love everywhere you go. -- Mother Teresa");
    }
    else if (seed==3){
    dictum->setText("If you look at what you have in life, you'll always have more. -- Oprah Winfrey");
    }
    else if (seed==4){
        dictum->setText("You are enough just as you are. -- Meghan Markle");
    }
    else if (seed==5){
        dictum->setText("My mission in life is not merely to survive, but to thrive. -- Maya Angelou");
    }
    else if (seed==6){
        dictum->setText("You must do the things you think you cannot do. -- Eleanor Roosevelt");
    }
    else if (seed==7){
        dictum->setText("Happiness is not by chance, but by choice. -- Jim Rohn");
    }
    else if (seed==8){
        dictum->setText("Some people look for a beautiful place. Others make a place beautiful. -- Hazrat Inayat Khan");
    }
    else{
        dictum->setText("Don’t let yesterday take up too much of today. -- Will Rogers");
    }

    dictum->setAlignment( Qt::AlignCenter );

}

/*
 * Implementation notes: ButtonHide()
 * ------------------------------------------------
 * Hide functional buttons.
 */
void main_window::ButtonHide(){
    Tool_Button->setVisible(false);
    Filter_Button->setVisible(false);
    Sticker_Button->setVisible(false);
    Text_Button->setVisible(false);
    Bigeye_Button->setVisible(false);
    Mosaic_Button->setVisible(false);
    Frame_Button->setVisible(false);
    Colorchange_Button->setVisible(false);
    Collage_Button->setVisible(false);

}

/*
 * Implementation notes: ButtonShow()
 * ----------------------------------
 * Show functional buttons.
 */
void main_window::ButtonShow(){
    Tool_Button->setVisible(true);
    Filter_Button->setVisible(true);
    Sticker_Button->setVisible(true);
    Text_Button->setVisible(true);
    Bigeye_Button->setVisible(true);
    Mosaic_Button->setVisible(true);
    Frame_Button->setVisible(true);
    Colorchange_Button->setVisible(true);
    Collage_Button->setVisible(true);
}


/*
 * when the load_button is clicked, it will ask the user to pick
 * an image and show it as a image button in the scroll area
 */
void main_window::add_image_button()
{
    int i = num;
    num++;

    QString filename(get_imagefile_name());
    std::cout<<filename.toStdString()<<std::endl;
    listButtons.push_back(new QToolButton());
    QImage* img = new QImage, * scaledimg = new QImage;

    if(! ( img->load(filename) ) )
    {
        QMessageBox::information(this,
                                 tr("error message"),
                                 tr("fail to load the image!"));
        delete img;
        return;
    }

    int Owidth = img->width(),Oheight = img->height();
    int Fwidth, Fheight;           //the new image size
    int Mul;

    if (Owidth >= Oheight) Mul = Owidth/55;
    else Mul = Oheight/55;

    Fwidth = Owidth/Mul;
    Fheight = Oheight/Mul;

    *scaledimg = img->scaled(Fwidth,Fheight,Qt::KeepAspectRatio);
    std::cout<<i<<std::endl;
    listButtons[i]->setFixedSize(QSize(55, 55));
    listButtons[i]->setIcon(QPixmap::fromImage(*img));
    listButtons[i]->setIconSize(QSize(Fwidth, Fheight));
    ui->top_layout->addWidget(listButtons[i],Qt::AlignCenter);
    tempcollagename = filename;

    connect(listButtons[i],SIGNAL(clicked()), buttonMapper, SLOT(map()));
    buttonMapper->setMapping(listButtons[i], filename);
    connect(buttonMapper, SIGNAL(mapped(QString)), this, SLOT(display_image(QString)));
}

void main_window::on_button_clicked(){
}

/*
 * when the load_button is clicked,
 * this function will get the name of the image
 */
QString main_window::get_imagefile_name()
{
    QFileDialog dialog(this);
    dialog.setNameFilter(tr("Images (*.png *.xpm *.jpg *.jpeg)"));
    dialog.setViewMode(QFileDialog::Detail);
    QString fileName = QFileDialog::getOpenFileName(this,
       tr("Open Images"), "/home/rpi/Desktop/Picture/Sample Pictures", tr("Image Files (*.png *.jpg *.jpeg *.bmp)"));
    if( fileName.isEmpty())
       {
       return ":/white.png";
       }
    else if (!fileName.isEmpty())
    {
        return fileName;
    }
}

/*
 * display the image on the canvas
 */
void main_window::display_image(QString filename)
{
    QImage* image = new QImage,* scaledimg = new QImage;
    if(! ( image->load(filename) ) )
            {
                QMessageBox::information(this,
                                         tr("error message"),
                                         tr("fail to load the image!"));
                delete image;
                return;
            }

    float Owidth = image->width(),Oheight = image->height();
    int Fwidth, Fheight;           //the new image size
    float Mul;

    if (Owidth >= Oheight) Mul = Owidth/500;
    else Mul = Oheight/500;

    Fwidth = floor(Owidth/Mul);
    Fheight = floor(Oheight/Mul);

    *scaledimg = image->scaled(500,500,Qt::KeepAspectRatio);
    *main_pic = *scaledimg;
    //disconnect
    initialization();
    display_screen();

}

void main_window::display_screen(){
    GraphScreen *pic = new GraphScreen;
    main_screen = pic;
    pic->display(main_pic);
    ui->graphicsView->setScene(pic);
    ui->graphicsView->fitInView(pic->itemsBoundingRect(),Qt::KeepAspectRatio);
    ui->graphicsView->show();
}

void main_window::display_graphscreen(){
    *main_pic = *(main_screen->ScreenPic);
    GraphScreen *pic = new GraphScreen;
    main_screen = pic;
    pic->display(main_pic);
    ui->graphicsView->setScene(pic);
    ui->graphicsView->fitInView(pic->itemsBoundingRect(),Qt::KeepAspectRatio);
    ui->graphicsView->show();
}

/* Undo, redo, do */
bool main_window::CanUndo(){
    return (undostack_count > 0);
}

void main_window::DeleteAction(){
    delete main_pic;
    main_pic = new QImage;
    display_screen();

}

void main_window::DownloadAction(){

    {
        QFileDialog fileDialog;
        QString str = fileDialog.getSaveFileName(this,"Open File","","Image File(*.jpg)");
        if(str == "")
        {
            return;
        }
        QFile filename(str);
        string path = str.toStdString();
        cout<<path;
        main_pic->save(&filename,"JPG");
        QMessageBox::information(this,"Ssve File","Save File Success",QMessageBox::Ok);
        filename.close();
    }

}

void main_window::UndoAction(){
    if (!undo_stack.empty()){
        redostack_count++;
        *main_pic = undo_stack.top();
        QImage image_copy = main_pic->copy();
        redo_stack.push(image_copy);
        undo_stack.pop();
        undostack_count--;
        display_screen();
    }
}

void main_window::DoAction(){
    QImage image_copy = main_pic->copy();
    undo_stack.push(image_copy);
}

void main_window::RedoAction(){
    if (!redo_stack.empty()){
    undostack_count++;
    *main_pic = redo_stack.top();
    QImage image_copy = main_pic->copy();
    undo_stack.push(image_copy);
    redo_stack.pop();
    redostack_count--;
    display_screen();
    }
}

//Tool function part
/*
 * Implementation notes: Set_Tool(),Hide_Tool(), Show_Tool()
 * ------------------------------------------------
 * Set properties of components of tool function. Allow hide or shown these components
 */
void main_window::Set_Tool(){
    ui->scrollArea_Tool->setFixedSize(QSize(120, 300));
    ui->scrollAreaWidgetContents_Tool->setLayout(Vlayout_Tool);

    Vlayout_Tool->addWidget(tool_button_CP,0,Qt::AlignCenter);
    Vlayout_Tool->addWidget(tool_button_RT,0,Qt::AlignCenter);
    Vlayout_Tool->addWidget(tool_button_BW,0,Qt::AlignCenter);
    Vlayout_Tool->addWidget(tool_button_BR,0,Qt::AlignCenter);
    Vlayout_Tool->addWidget(tool_button_CT,0,Qt::AlignCenter);
    Vlayout_Tool->addWidget(tool_button_FT,0,Qt::AlignCenter);
    Vlayout_Tool->addWidget(tool_button_ST,0,Qt::AlignCenter);
    Vlayout_Tool->addWidget(tool_button_BL,0,Qt::AlignCenter);

    tool_button_CP->setButtonSize(90,80);
    tool_button_RT->setButtonSize(90,80);
    tool_button_BW->setButtonSize(90,80);
    tool_button_BR->setButtonSize(90,80);
    tool_button_CT->setButtonSize(90,80);
    tool_button_FT->setButtonSize(90,80);
    tool_button_ST->setButtonSize(90,80);
    tool_button_BL->setButtonSize(90,80);
    tool_button_CP->setButtonPicture(Crop_Img);
    tool_button_CP->setPressPicture(Crop_PressImg);
    tool_button_RT->setButtonPicture(Rotation_Img);
    tool_button_RT->setPressPicture(Rotation_PressImg);
    tool_button_BW->setButtonPicture(BlackWhite_Img);
    tool_button_BW->setPressPicture(BlackWhite_PressImg);
    tool_button_BR->setButtonPicture(Brightness_Img);
    tool_button_BR->setPressPicture(Brightness_PressImg);
    tool_button_CT->setButtonPicture(Contrast_Img);
    tool_button_CT->setPressPicture(Contrast_PressImg);
    tool_button_FT->setButtonPicture(ColorFilter_Img);
    tool_button_FT->setPressPicture(ColorFilter_PressImg);
    tool_button_ST->setButtonPicture(Saturation_Img);
    tool_button_ST->setPressPicture(Saturation_PressImg);
    tool_button_BL->setButtonPicture(Blur_Img);
    tool_button_BL->setPressPicture(Blur_PressImg);

    ui->scrollArea_Tool->setVisible(false);
}

void main_window:: Hide_Tool(){
    ui->scrollArea_Tool->setVisible(false);
}

void main_window:: Show_Tool(){
    ui->scrollArea_Tool->setVisible(true);
}

/*
 * Hide or show sliders and spin boxs for tool functions including
 *  brightness, contrast, blur, saturation, crop, color filter, rotation
 */
void main_window:: Hide_Bright_Slider(){
    spinBox1->setVisible(false);
    slider1->setVisible(false);
}
void main_window:: Show_Bright_Slider(){
    spinBox1->setVisible(true);
    slider1->setVisible(true);
}

void main_window:: Hide_Contrast_Slider(){
    spinBox2->setVisible(false);
    slider2->setVisible(false);
}
void main_window:: Show_Contrast_Slider(){
    spinBox2->setVisible(true);
    slider2->setVisible(true);
}

void main_window:: Hide_Blur_Slider(){
    spinBox_blur->setVisible(false);
    slider_blur->setVisible(false);
}
void main_window:: Show_Blur_Slider(){
    spinBox_blur->setVisible(true);
    slider_blur->setVisible(true);
}

void main_window:: Hide_Saturation_Slider(){
    spinBox_saturation->setVisible(false);
    slider_saturation->setVisible(false);
}

void main_window:: Show_Saturation_Slider(){
    spinBox_saturation->setVisible(true);
    slider_saturation->setVisible(true);
}

void main_window:: Hide_crop(){
    crop_Button->setVisible(false);
}
void main_window:: Show_crop(){
    crop_Button->setVisible(true);
}

void main_window:: Hide_FilterColor_Button(){
    cf_red->setVisible(false);
    cf_orange->setVisible(false);
    cf_yellow->setVisible(false);
    cf_green->setVisible(false);
    cf_blue->setVisible(false);
    cf_purple->setVisible(false);
    cf_pink->setVisible(false);

}

void main_window:: Show_FilterColor_Button(){
    cf_red->setVisible(true);
    cf_orange->setVisible(true);
    cf_yellow->setVisible(true);
    cf_green->setVisible(true);
    cf_blue->setVisible(true);
    cf_purple->setVisible(true);
    cf_pink->setVisible(true);
}

void main_window:: Hide_Rotate_Button(){
    LeftRotate_Button->setVisible(false);
    RightRotate_Button->setVisible(false);
    HorizontalFlip_Button->setVisible(false);
    VerticalFlip_Button->setVisible(false);
    DiagonalFlip_Button->setVisible(false);
}

void main_window:: Show_Rotate_Button(){
    LeftRotate_Button->setVisible(true);
    RightRotate_Button->setVisible(true);
    HorizontalFlip_Button->setVisible(true);
    VerticalFlip_Button->setVisible(true);
    DiagonalFlip_Button->setVisible(true);
}

/*
 * Implementation notes:Tool_blackwhite()
 * --------------------------------------
 * Tool function: black & white.
 */
void main_window::Tool_blackwhite(){
    Mat img = QImage2cvMat(*main_pic);
    Mat bw_img = blackwhite(img);
    *main_pic = cvMat2QImage(bw_img);
    display_screen();
}

/*
 * Implementation notes:Tool_crop()
 * --------------------------------
 * Tool function: crop.
 */
void main_window:: Tool_crop(){
    connect(crop_Button, SIGNAL(clicked()), this, SLOT(display_graphscreen()));
    main_screen->set_m_crop(true);
}

/*
 * Implementation notes:temp_brightness()
 * ------------------------------------------------
 * If the value of spinBox 1 chnaged, this function
 * will be called to invoking brightness function and
 * adjuest the brightness of the picture
 */
void main_window::temp_brightness(){
    int bright_value = spinBox1->value();
    Mat br_img =brightness(Temp_main_pic, bright_value);
    *main_pic=cvMat2QImage(br_img);
    display_screen();
}

/*
 * Implementation notes:Tool_brightness()
 * ------------------------------------------------
 * save the current picture, initialize the spin box
 * value and connect signal and slot.
 */
void main_window::Tool_brightness(){
    spinBox1->disconnect(this);
    slider1->disconnect(this);
    Temp_main_pic = QImage2cvMat(*main_pic).clone();
    spinBox1->setValue(50);
    connect(spinBox1, SIGNAL(valueChanged(int)), this, SLOT(temp_brightness()));
}

/*
 * Implementation notes:temp_contrast()
 * ------------------------------------------------
 * If the value of spinBox 2 chnaged, this function
 * will be called to invoking contrast function and
 * adjuest the contrast degree of the picture.
 */
void main_window::temp_contrast(){
    int contrast_value = spinBox2->value()+10;
    Mat contrast_img = contrast(Temp_main_pic, contrast_value);
    *main_pic=cvMat2QImage(contrast_img);
    display_screen();
}

/*
 * Implementation notes:Tool_contrast()
 * ------------------------------------------------
 * save the current picture, initialize the spin box
 * value and connect signal and slot.
 */
void main_window::Tool_contrast(){
    spinBox2->disconnect(this);
    slider2->disconnect(this);
    Temp_main_pic = QImage2cvMat(*main_pic).clone();
    spinBox2->setValue(0);
    connect(spinBox2, SIGNAL(valueChanged(int)), this, SLOT(temp_contrast()));
}

/*
 * Implementation notes:temp_blur()
 * ------------------------------------------------
 * If the value of spinBox_blur chnaged, this function
 * will be called to invoking median_blur function and
 * adjuest the blur degree of the picture.
 */
void main_window::temp_blur(){
    int blur_value = spinBox_blur->value();
    Mat blur_img = median_blur(Temp_main_pic, blur_value);
    *main_pic=cvMat2QImage(blur_img);
    display_screen();
}

/*
 * Implementation notes:Tool_blur()
 * ------------------------------------------------
 * save the current picture, initialize the spin box
 * value and connect signal and slot.
 */
void main_window::Tool_blur(){
    spinBox_blur->disconnect(this);
    slider_blur->disconnect(this);
    Temp_main_pic = QImage2cvMat(*main_pic).clone();
    spinBox_blur->setValue(0);
    connect(spinBox_blur, SIGNAL(valueChanged(int)), this, SLOT(temp_blur()));
}

/*
 * Implementation notes:temp_saturation()
 * ------------------------------------------------
 * If the value of spinBox_saturation chnaged, this function
 * will be called to invoking saturation function and
 * adjuest the blur degree of the picture.
 */
void main_window::temp_saturation(){
    int saturation_value = spinBox_saturation->value();
    Mat saturation_img = saturation(Temp_main_pic, saturation_value);
    *main_pic=cvMat2QImage(saturation_img);
    display_screen();
}

/*
 * Implementation notes:Tool_saturation()
 * ------------------------------------------------
 * save the current picture, initialize the spin box
 * value and connect signal and slot.
 */
void main_window::Tool_saturation(){
    spinBox_saturation->disconnect(this);
    slider_saturation->disconnect(this);
    Temp_main_pic = QImage2cvMat(*main_pic).clone();
    spinBox_saturation->setValue(0);
    connect(spinBox_saturation, SIGNAL(valueChanged(int)), this, SLOT(temp_saturation()));
}

/*
 * Implementation notes:Tool_rotate()
 * ------------------------------------------------
 * According to the signal sender, set different mode of rotation.
 * Ivoking rotation function.
 */
void main_window::Tool_rotate(){
     Mat img = QImage2cvMat(*main_pic);
     int mode=-1;
     if (sender()==LeftRotate_Button){
         mode=1;
     }
     else if (sender()==RightRotate_Button){
         mode=2;
     }
     else if (sender()==HorizontalFlip_Button){
         mode=3;
     }
     else if (sender()==VerticalFlip_Button){
         mode=4;
     }
     else if (sender()==DiagonalFlip_Button){
         mode=5;
     }
     Mat rotate_img = rotate(img, mode);
     *main_pic = cvMat2QImage(rotate_img);
     display_screen();
}

/*
 * Implementation notes:Tool_rotate()
 * ------------------------------------------------
 * According to the signal sender, set different mode of color filter.
 * Ivoking color filter function.
 */
void main_window::Tool_cf(){
    Mat img = QImage2cvMat(*main_pic);
    int mode = 0;
    if (sender()==cf_red){
        mode=1;
    }
    else if (sender()==cf_orange){
        mode=2;
    }
    else if (sender()==cf_yellow){
        mode=3;
    }
    else if (sender()==cf_green){
        mode=4;
    }
    else if (sender()==cf_blue){
        mode=5;
    }
    else if (sender()==cf_purple){
        mode=6;
    }
    else if (sender()==cf_pink){
        mode=7;
    }
    Mat cf_img = filter_color(img, mode);
    *main_pic = cvMat2QImage(cf_img);
    display_screen();
}


//Sticker function part
/*
 * Implementation notes: Set_Sticker(),Hide_Sticker(), Show_Sticker()
 * ------------------------------------------------
 * Set properties of components of sticker function. Allow hide or shown these components
 */
void main_window::Set_Sticker(){
    ui->scrollArea_Sticker->setFixedSize(QSize(120, 300));
    ui->scrollAreaWidgetContents_Sticker->setLayout(Vlayout_Sticker);

    QPalette pa;
    pa.setColor(QPalette::Text,Qt::white);

    Vlayout_Sticker->addWidget(basic_sticker_label,Qt::AlignCenter);
    basic_sticker_label->setText("Basic");
    basic_sticker_label->setAlignment(Qt::AlignCenter);
    basic_sticker_label->setStyleSheet("background:transparent");
    basic_sticker_label->setFont(QFont("Timers", 18, QFont::Bold));
    basic_sticker_label->setPalette(pa);

    Vlayout_Sticker->addWidget(sticker1,Qt::AlignCenter);
    Vlayout_Sticker->addWidget(sticker2,Qt::AlignCenter);
    Vlayout_Sticker->addWidget(sticker3,Qt::AlignCenter);
    Vlayout_Sticker->addWidget(sticker4,Qt::AlignCenter);
    Vlayout_Sticker->addWidget(sticker5,Qt::AlignCenter);
    Vlayout_Sticker->addWidget(sticker6,Qt::AlignCenter);

    Vlayout_Sticker->addWidget(advanced_sticker_label,Qt::AlignCenter);
    advanced_sticker_label->setText("Advanced");
    advanced_sticker_label->setAlignment(Qt::AlignCenter);
    advanced_sticker_label->setStyleSheet("background:transparent");
    advanced_sticker_label->setFont(QFont("Timers", 18, QFont::Bold));
    advanced_sticker_label->setPalette(pa);
    Vlayout_Sticker->addWidget(sticker7,Qt::AlignCenter);

    sticker1->setButtonSize(90,90);
    sticker2->setButtonSize(90,90);
    sticker3->setButtonSize(90,90);
    sticker4->setButtonSize(90,90);
    sticker5->setButtonSize(90,90);
    sticker6->setButtonSize(90,90);
    sticker7->setButtonSize(90,90);

    sticker1->setButtonPicture(Sticker1_Img);
    sticker1->setPressPicture(Sticker1_Img);
    sticker2->setButtonPicture(Sticker2_Img);
    sticker2->setPressPicture(Sticker2_Img);
    sticker3->setButtonPicture(Sticker3_Img);
    sticker3->setPressPicture(Sticker3_Img);
    sticker4->setButtonPicture(Sticker4_Img);
    sticker4->setPressPicture(Sticker4_Img);
    sticker5->setButtonPicture(Sticker5_Img);
    sticker5->setPressPicture(Sticker5_Img);
    sticker6->setButtonPicture(Sticker6_Img);
    sticker6->setPressPicture(Sticker6_Img);
    sticker7->setButtonPicture(Sticker7_Img);
    sticker7->setPressPicture(Sticker7_Img);

    ui->scrollArea_Sticker->setVisible(false);
}

void main_window:: Hide_Sticker(){
    ui->scrollArea_Sticker->setVisible(false);
    spinBox_sticker->setVisible(false);
    slider_sticker->setVisible(false);
}

void main_window:: Show_Sticker(){
    ui->scrollArea_Sticker->setVisible(true);
    spinBox_sticker->setValue(15);    //贴纸大小初始值
    spinBox_sticker->setVisible(true);
    slider_sticker->setVisible(true);
}

/*
 * Implementation notes:Sticker_Add()
 * ------------------------------------------------
 * According to the signal senders, select different stickers.
 * Set set_m_addsticker flag.
 *  Connect signal and slot to allow adjustment of sticker size.
 */
void main_window::Sticker_Add(){

    if (sender()==sticker1){
        main_screen->select_sticker(1);
        main_screen->set_m_addsticker(true);
    }
    else if (sender()==sticker2){
        main_screen->select_sticker(2);
        main_screen->set_m_addsticker(true);
    }
    else if (sender()==sticker3){
        main_screen->select_sticker(3);
        main_screen->set_m_addsticker(true);
    }
    else if (sender()==sticker4){
        main_screen->select_sticker(4);
        main_screen->set_m_addsticker(true);
    }
    else if (sender()==sticker5){
        main_screen->select_sticker(5);
        main_screen->set_m_addsticker(true);
    }
    else if (sender()==sticker6){
        main_screen->select_sticker(6);
        main_screen->set_m_addsticker(true);
    }
    else if (sender()==sticker7){
        main_screen->select_sticker(7);
        main_screen->set_m_addsticker(true);
    }

    spinBox_sticker->disconnect(this);
    slider_sticker->disconnect(this);
    Temp_main_pic = QImage2cvMat(*main_pic); //暂存原始图片
    connect(spinBox_sticker, SIGNAL(valueChanged(int)), this, SLOT(temp_StickerAdd()));
}

/*
 * Implementation notes:temp_StickerAdd()
 * ------------------------------------------------
 * Set sticker size.
 */
void main_window::temp_StickerAdd(){
    int stickerSize_value = spinBox_sticker->value();
        main_screen->set_sticker_size(stickerSize_value);
}


//Big eye function part
/*
 * Implementation notes: Hide_eyeSlider(), Show_eyeSlider()
 * ------------------------------------------------
 * Allow hide or show of components for Big eye function.
 */
void main_window:: Show_eyeSlider(){
    spinBox_eye->setVisible(true);
    spinBox_eye->setValue(0);
    slider_eye->setVisible(true);
}
void main_window:: Hide_eyeSlider(){
    spinBox_eye->setVisible(false);
    slider_eye->setVisible(false);
    spinBox_eye->disconnect(this);
    slider_eye->disconnect(this);
}

/*
 * Implementation notes:temp_BigEye()
 * ------------------------------------------------
 * get sticker size and invoking eyesBigger function.
 */
void main_window::temp_BigEye(){
    float eyeSize_value = float(spinBox_eye->value())/100+1;
    Mat bigEye_img;
    bigEye_img = eyesBigger(Temp_main_pic, eyeSize_value);
    *main_pic = cvMat2QImage(bigEye_img);
    display_screen();
}


/*
 * Implementation notes:Big_eye()
 * ------------------------------------------------
 * save the current picture
 * connect signal and slot.
 */
void main_window::Big_eye(){
    spinBox_eye->disconnect(this);
    slider_eye->disconnect(this);
    Temp_main_pic = QImage2cvMat(*main_pic).clone();
    connect(spinBox_eye, SIGNAL(valueChanged(int)), this, SLOT(temp_BigEye()));
}



//Mosaic function part
/*
 * Implementation notes: Set_Mosaic(), Hide_Mosaic(), Show_Mosaic()
 * ------------------------------------------------
 * Set properties of components of Mosaic function. Allow hide or show
 * of components for mosaic function.
 */
void main_window:: Set_Mosaic(){
    ui->scrollArea_Mosaic->setFixedSize(QSize(120, 300));
    ui->scrollAreaWidgetContents_Mosaic->setLayout(Vlayout_Mosaic);
    Vlayout_Mosaic->addWidget(small_mosaic);
    Vlayout_Mosaic->addWidget(median_mosaic);
    Vlayout_Mosaic->addWidget(large_mosaic);
    small_mosaic->setButtonSize(90,80);
    median_mosaic->setButtonSize(90,80);
    large_mosaic->setButtonSize(90,80);
    small_mosaic->setButtonPicture(smallMosaic_Img);
    small_mosaic->setPressPicture(smallMosaic_Img);
    median_mosaic->setButtonPicture(medianMosaic_Img);
    median_mosaic->setPressPicture(medianMosaic_Img);
    large_mosaic->setButtonPicture(largeMosaic_Img);
    large_mosaic->setPressPicture(largeMosaic_Img);
    ui->scrollArea_Mosaic->setVisible(false);

    connect(small_mosaic, SIGNAL(released()), this, SLOT(Mosaic()));//mia
    connect(median_mosaic, SIGNAL(released()), this, SLOT(Mosaic()));//mia
    connect(large_mosaic, SIGNAL(released()), this, SLOT(Mosaic()));//mia
}

void main_window:: Hide_Mosaic(){
    ui->scrollArea_Mosaic->setVisible(false);
}

void main_window:: Show_Mosaic(){
    ui->scrollArea_Mosaic->setVisible(true);
}

/*
 * Implementation notes:Mosaic()
 * ------------------------------------------------
 * According to the signal sender, choose different
 * size of mosaic.
 * Set set_mosaic_size flag
 */
void main_window::Mosaic(){
    int size;
    main_screen->set_m_mosaic(true);
    if (sender()==small_mosaic){
        size = 3;
    }
    else if (sender()==median_mosaic){
        size = 10;
    }
    else{
        size = 20;
    }

    main_screen->set_mosaic_size(size);

}


//Frame function part
/*
 * Implementation notes: Set_Frame(), Hide_Frame(), Show_Frame()
 * ------------------------------------------------
 * Set properties of components of Frame function. Allow hide or show
 * of components for Frame function.
 */
void main_window:: Set_Frame(){
    ui->scrollArea_Frame->setFixedSize(QSize(120, 300));
    ui->scrollAreaWidgetContents_Frame->setLayout(Vlayout_Frame);
    Vlayout_Frame->addWidget(frame1);
    Vlayout_Frame->addWidget(frame2);
    Vlayout_Frame->addWidget(frame3);
    Vlayout_Frame->addWidget(frame4);
    Vlayout_Frame->addWidget(frame5);
    Vlayout_Frame->addWidget(frame6);
    Vlayout_Frame->addWidget(frame7);
    Vlayout_Frame->addWidget(frame8);
    frame1->setButtonSize(90,80);
    frame2->setButtonSize(90,80);
    frame3->setButtonSize(90,80);
    frame4->setButtonSize(90,80);
    frame5->setButtonSize(90,80);
    frame6->setButtonSize(90,80);
    frame7->setButtonSize(90,80);
    frame8->setButtonSize(90,80);
    frame1->setButtonPicture(fr_Black_Img);
    frame1->setPressPicture(fr_Black_Img);
    frame2->setButtonPicture(fr_White_Img);
    frame2->setPressPicture(fr_White_Img);
    frame3->setButtonPicture(fr_Cocoa_Img);
    frame3->setPressPicture(fr_Cocoa_Img);
    frame4->setButtonPicture(fr_Heart_Img);
    frame4->setPressPicture(fr_Heart_Img);
    frame5->setButtonPicture(fr_Vintage_Img);
    frame5->setPressPicture(fr_Vintage_Img);
    frame6->setButtonPicture(fr_Gaudy_Img);
    frame6->setPressPicture(fr_Gaudy_Img);
    frame7->setButtonPicture(fr_Dynamic_Img);
    frame7->setPressPicture(fr_Dynamic_Img);
    frame8->setButtonPicture(fr_Mirror_Img);
    frame8->setPressPicture(fr_Mirror_Img);
    ui->scrollArea_Frame->setVisible(false);
    connect(frame1, SIGNAL(released()), this, SLOT(Frame()));
    connect(frame2, SIGNAL(released()), this, SLOT(Frame()));
    connect(frame3, SIGNAL(released()), this, SLOT(Frame()));
    connect(frame4, SIGNAL(released()), this, SLOT(Frame()));
    connect(frame5, SIGNAL(released()), this, SLOT(Frame()));
    connect(frame6, SIGNAL(released()), this, SLOT(Frame()));
    connect(frame7, SIGNAL(released()), this, SLOT(Frame()));
    connect(frame8, SIGNAL(released()), this, SLOT(Frame()));
}

void main_window:: Hide_Frame(){
    ui->scrollArea_Frame->setVisible(false);
}

void main_window:: Show_Frame(){
    ui->scrollArea_Frame->setVisible(true);
}

/*
 * Implementation notes:Frame()
 * ------------------------------------------------
 * According to the signal sender, choose different
 * frame.
 * Ivoking add frame functions.
 */
void main_window::Frame(){
    Mat img = QImage2cvMat(*main_pic).clone();
    Mat FrameImg;
    if (sender()==frame1){
        FrameImg = addframe_cv(img,3);
    }
    else if (sender()==frame2){
        FrameImg =addframe_cv(img,4);
    }
    else if (sender()==frame3){
        FrameImg = addframe(img,3);
    }
    else if (sender()==frame4){
        FrameImg =addframe(img,1);
    }
    else if (sender()==frame5){
        FrameImg =addframe(img,4);
    }
    else if (sender()==frame6){
        FrameImg =addframe(img,2);
    }
    else if (sender()==frame7){
       FrameImg = addframe_cv(img,1);
    }
    else if (sender()==frame8){
        FrameImg = addframe_cv(img,2);
    }

    *main_pic = cvMat2QImage(FrameImg);
    display_screen();
}


//Frame function part
/*
 * Implementation notes: Set_Filter(), Hide_Filter(), Show_Filter()
 * ------------------------------------------------
 * Set properties of components of Filter function. Allow hide or show
 * of components for Filter function.
 */
void main_window:: Set_Filter(){
    ui->scrollArea_Filter->setFixedSize(QSize(120, 300));
    ui->scrollAreaWidgetContents_Filter->setLayout(Vlayout_Filter);

    QPalette pa;
    pa.setColor(QPalette::Text,Qt::white);

    Vlayout_Filter->addWidget(basic_filter_label,Qt::AlignCenter);
    basic_filter_label->setText("Basic");
    basic_filter_label->setAlignment(Qt::AlignCenter);
    basic_filter_label->setStyleSheet("background:transparent");
    basic_filter_label->setFont(QFont("Timers", 18, QFont::Bold));
    basic_filter_label->setPalette(pa);
    Vlayout_Filter->addWidget(filter_button_old,Qt::AlignCenter);
    Vlayout_Filter->addWidget(filter_button_comic,Qt::AlignCenter);
    Vlayout_Filter->addWidget(filter_button_pepper,Qt::AlignCenter);
    Vlayout_Filter->addWidget(filter_button_grain,Qt::AlignCenter);
    Vlayout_Filter->addWidget(filter_button_exposure,Qt::AlignCenter);
    Vlayout_Filter->addWidget(filter_button_magic,Qt::AlignCenter);
    Vlayout_Filter->addWidget(filter_button_silence,Qt::AlignCenter);

    filter_button_old->setButtonSize(90,80);
    filter_button_comic->setButtonSize(90,80);
    filter_button_pepper->setButtonSize(90,80);
    filter_button_grain->setButtonSize(90,80);
    filter_button_exposure->setButtonSize(90,80);
    filter_button_magic->setButtonSize(90,80);
    filter_button_silence->setButtonSize(90,80);

    filter_button_old->setButtonPicture(fOld_Img);
    filter_button_old->setPressPicture(fOld_Img);

    filter_button_comic->setButtonPicture(fComic_Img);
    filter_button_comic->setPressPicture(fComic_Img);

    filter_button_pepper->setButtonPicture(fPepper_Img);
    filter_button_pepper->setPressPicture(fPepper_Img);

    filter_button_grain->setButtonPicture(fGrain_Img);
    filter_button_grain->setPressPicture(fGrain_Img);

    filter_button_exposure->setButtonPicture(fExposure_Img);
    filter_button_exposure->setPressPicture(fExposure_Img);

    filter_button_magic->setButtonPicture(fMagic_Img);
    filter_button_magic->setPressPicture(fMagic_Img);

    filter_button_silence->setButtonPicture(fSilence_Img);
    filter_button_silence->setPressPicture(fSilence_Img);

    Vlayout_Filter->addWidget(advanced_filter_label,Qt::AlignCenter);
    advanced_filter_label->setText("Advanced");
    advanced_filter_label->setAlignment(Qt::AlignCenter);
    advanced_filter_label->setStyleSheet("background:transparent");
    advanced_filter_label->setFont(QFont("Timers", 18, QFont::Bold));
    advanced_filter_label->setPalette(pa);

    Vlayout_Filter->addWidget(filter_button_beauty,Qt::AlignCenter);
    Vlayout_Filter->addWidget(filter_button_highlight,Qt::AlignCenter);
    Vlayout_Filter->addWidget(filter_button_softlight,Qt::AlignCenter);
    Vlayout_Filter->addWidget(filter_button_diffuse,Qt::AlignCenter);
    Vlayout_Filter->addWidget(filter_button_expand,Qt::AlignCenter);
    Vlayout_Filter->addWidget(filter_button_shrink,Qt::AlignCenter);
    Vlayout_Filter->addWidget(filter_button_strike,Qt::AlignCenter);
    Vlayout_Filter->addWidget(filter_button_volution,Qt::AlignCenter);
    Vlayout_Filter->addWidget(filter_button_wave,Qt::AlignCenter);
    Vlayout_Filter->addWidget(filter_button_sketch,Qt::AlignCenter);
    Vlayout_Filter->addWidget(filter_button_neon,Qt::AlignCenter);
    Vlayout_Filter->addWidget(filter_button_carve,Qt::AlignCenter);
    Vlayout_Filter->addWidget(filter_button_embossment,Qt::AlignCenter);

    filter_button_beauty->setButtonSize(90,80);
    filter_button_highlight->setButtonSize(90,80);
    filter_button_softlight->setButtonSize(90,80);
    filter_button_diffuse->setButtonSize(90,80);
    filter_button_expand->setButtonSize(90,80);
    filter_button_shrink->setButtonSize(90,80);
    filter_button_strike->setButtonSize(90,80);
    filter_button_volution->setButtonSize(90,80);
    filter_button_wave->setButtonSize(90,80);
    filter_button_sketch->setButtonSize(90,80);
    filter_button_neon->setButtonSize(90,80);
    filter_button_carve->setButtonSize(90,80);
    filter_button_embossment->setButtonSize(90,80);

    filter_button_beauty->setButtonPicture(fBeauty_Img);
    filter_button_beauty->setPressPicture(fBeauty_Img);

    filter_button_highlight->setButtonPicture(fHighlight_Img);
    filter_button_highlight->setPressPicture(fHighlight_Img);

    filter_button_softlight->setButtonPicture(fSoftlight_Img);
    filter_button_softlight->setPressPicture(fSoftlight_Img);

    filter_button_diffuse->setButtonPicture(fDiffuse_Img);
    filter_button_diffuse->setPressPicture(fDiffuse_Img);

    filter_button_expand->setButtonPicture(fExpand_Img);
    filter_button_expand->setPressPicture(fExpand_Img);

    filter_button_shrink->setButtonPicture(fShrink_Img);
    filter_button_shrink->setPressPicture(fShrink_Img);

    filter_button_strike->setButtonPicture(fStrike_Img);
    filter_button_strike->setPressPicture(fStrike_Img);

    filter_button_volution->setButtonPicture(fVolution_Img);
    filter_button_volution->setPressPicture(fVolution_Img);

    filter_button_wave->setButtonPicture(fWave_Img);
    filter_button_wave->setPressPicture(fWave_Img);

    filter_button_sketch->setButtonPicture(fSketch_Img);
    filter_button_sketch->setPressPicture(fSketch_Img);

    filter_button_neon->setButtonPicture(fNeon_Img);
    filter_button_neon->setPressPicture(fNeon_Img);

    filter_button_carve->setButtonPicture(fCarve_Img);
    filter_button_carve->setPressPicture(fCarve_Img);

    filter_button_embossment->setButtonPicture(fEmbossment_Img);
    filter_button_embossment->setPressPicture(fEmbossment_Img);

    ui->scrollArea_Filter->setVisible(false);
    connect(filter_button_old, SIGNAL(released()), this, SLOT(Filter()));
    connect(filter_button_comic, SIGNAL(released()), this, SLOT(Filter()));
    connect(filter_button_exposure, SIGNAL(released()), this, SLOT(Filter()));
    connect(filter_button_magic, SIGNAL(released()), this, SLOT(Filter()));
    connect(filter_button_silence, SIGNAL(released()), this, SLOT(Filter()));
    connect(filter_button_beauty, SIGNAL(released()), this, SLOT(Filter()));
    connect(filter_button_highlight, SIGNAL(released()), this, SLOT(Filter()));
    connect(filter_button_softlight, SIGNAL(released()), this, SLOT(Filter()));
    connect(filter_button_diffuse, SIGNAL(released()), this, SLOT(Filter()));
    connect(filter_button_expand, SIGNAL(released()), this, SLOT(Filter()));
    connect(filter_button_shrink, SIGNAL(released()), this, SLOT(Filter()));
    connect(filter_button_strike, SIGNAL(released()), this, SLOT(Filter()));
    connect(filter_button_volution, SIGNAL(released()), this, SLOT(Filter()));
    connect(filter_button_wave, SIGNAL(released()), this, SLOT(Filter()));
    connect(filter_button_sketch, SIGNAL(released()), this, SLOT(Filter()));
    connect(filter_button_neon, SIGNAL(released()), this, SLOT(Filter()));
    connect(filter_button_carve, SIGNAL(released()), this, SLOT(Filter()));
    connect(filter_button_embossment, SIGNAL(released()), this, SLOT(Filter()));
    connect(filter_button_pepper, SIGNAL(released()), this, SLOT(Filter()));
    connect(filter_button_grain, SIGNAL(released()), this, SLOT(Filter()));

}

void main_window:: Hide_Filter(){
    ui->scrollArea_Filter->setVisible(false);
}

void main_window:: Show_Filter(){
    ui->scrollArea_Filter->setVisible(true);
}

/*
 * Implementation notes: Filter()
 * ------------------------------------------------
 * According to the signal sender, choose different
 * filter.
 * Ivoking add filter functions.
 */
void main_window:: Filter(){
     Mat img = QImage2cvMat(*main_pic).clone();
     Mat FilterImg;
    if (sender()==filter_button_old){
        FilterImg = old(img);
    }
    else if (sender()==filter_button_magic){
        FilterImg = magic(img);
    }
    else if (sender()==filter_button_pepper){
        FilterImg = noise(img,0);
    }
    else if (sender()==filter_button_grain){
        FilterImg = noise(img,1);
    }
    else if (sender()==filter_button_exposure){
        FilterImg = exposure(img);
    }
    else if (sender()==filter_button_comic){
        FilterImg = comic(img);
    }
    else if (sender()==filter_button_silence){
        FilterImg = silence(img);
    }
    else if (sender()==filter_button_beauty){
        FilterImg = beauty(img);
    }
    else if (sender()==filter_button_highlight){
        FilterImg = highLight(img);
    }
    else if (sender()==filter_button_softlight){
        FilterImg = softLight(img);
    }
    else if (sender()==filter_button_diffuse){
        FilterImg = diffuse(img);
    }
    else if (sender()==filter_button_expand){
        FilterImg = expand(img);
    }
    else if (sender()==filter_button_shrink){
        FilterImg = shrink(img);
    }
    else if (sender()==filter_button_strike){
        FilterImg = strike(img);
    }
    else if (sender()==filter_button_volution){
        FilterImg = volution(img);
    }
    else if (sender()==filter_button_wave){
        FilterImg = wave(img);
    }
    else if (sender()==filter_button_carve){
        FilterImg = carve(img);
    }
    else if (sender()==filter_button_sketch){
        FilterImg = sketch(img);
    }
    else if (sender()==filter_button_neon){
        FilterImg = neon(img);
    }
    else if (sender()==filter_button_embossment){
        FilterImg = embossment(img);
    }

    *main_pic = cvMat2QImage(FilterImg);
    display_screen();

}

//Background color change function part
/*
 * Implementation notes: Set_background(), Hide_background(), Show_background()
 * ------------------------------------------------
 * Set properties of components of Background color change function. Allow hide or show
 * of components for Background color change function.
 */
void main_window:: Set_background(){
    //background
    ui->scrollArea_Background->setFixedSize(QSize(120, 300));
    ui->scrollAreaWidgetContents_Background->setLayout(Vlayout_Background);

    Vlayout_Background->addWidget(red_back);
    Vlayout_Background->addWidget(blue_back);
    Vlayout_Background->addWidget(white_back);
    red_back->setButtonSize(90,80);
    blue_back->setButtonSize(90,80);
    white_back->setButtonSize(90,80);
    red_back->setButtonPicture(red_Img);
    red_back->setPressPicture(red_Img);
    blue_back->setButtonPicture(blue_Img);
    blue_back->setPressPicture(blue_Img);
    white_back->setButtonPicture(white_Img);
    white_back->setPressPicture(white_Img);
    ui->scrollArea_Background->setVisible(false);

    connect(red_back, SIGNAL(released()), this, SLOT(back_flag()));
    connect(white_back, SIGNAL(released()), this, SLOT(back_flag()));
    connect(blue_back, SIGNAL(released()), this, SLOT(back_flag()));
}


void main_window:: Hide_background(){

    ui->scrollArea_Background->setVisible(false);

}

void main_window:: Show_background(){

    ui->scrollArea_Background->setVisible(true);

}

/*
 * Implementation notes: back_flag()
 * ------------------------------------------------
 * According to the signal sender, choose different
 * background color.
 * Ivoking changeBackground functions.
 */
void main_window::back_flag(){
    Mat img = QImage2cvMat(*main_pic);
    int mode = 0;
    if (sender()==red_back){
        mode=1;
    }
    else if (sender()==white_back){
        mode=0;
    }
    else if (sender()==blue_back){
        mode=2;
    }
    Mat back_img = changeBackground(img, mode);
    *main_pic = cvMat2QImage(back_img);

    display_screen();
}


//Collage function part
/*
 * Implementation notes: Hide_collageButton(), Show_collageButton()
 * ------------------------------------------------
 * Set properties of components of collage function. Allow hide or show
 * of components for collage function.
 */
void main_window:: Show_collageButton(){
    collage_h->setVisible(true);
    collage_v->setVisible(true);
}
void main_window:: Hide_collageButton(){
    collage_h->setVisible(false);
    collage_v->setVisible(false);
}

/*
 * Implementation notes: Collage()
 * ------------------------------------------------
 * According to the signal sender, choose different
 * collage mode.
 * Ivoking functions that can combine pictures.
 */
void main_window::Collage(){
    Mat img = QImage2cvMat(*main_pic).clone();
    Mat CollageImg = img;
   if (sender()==collage_h){
       if(num > 0){
           laod_collage();
           CollageImg = combine_hor(img, QImage2cvMat(tempcollage));
       }
       else{
           add_image_button();
           main_pic->load(tempcollagename);
           float Owidth = main_pic->width(),Oheight = main_pic->height();
           int Fwidth, Fheight;           //the new image size
           float Mul;

           if (Owidth >= Oheight) Mul = Owidth/500;
           else Mul = Oheight/500;

           Fwidth = floor(Owidth/Mul);
           Fheight = floor(Oheight/Mul);

           *main_pic = main_pic->scaled(500,500,Qt::KeepAspectRatio);
            display_screen();
       }

   }
   else if (sender()==collage_v){
       if(num > 0){
           laod_collage();
           CollageImg = combine_ver(img, QImage2cvMat(tempcollage));
       }
       else{
           add_image_button();
           main_pic->load(tempcollagename);
           float Owidth = main_pic->width(),Oheight = main_pic->height();
           int Fwidth, Fheight;           //the new image size
           float Mul;

           if (Owidth >= Oheight) Mul = Owidth/500;
           else Mul = Oheight/500;

           Fwidth = floor(Owidth/Mul);
           Fheight = floor(Oheight/Mul);

           *main_pic = main_pic->scaled(500,500,Qt::KeepAspectRatio);
            display_screen();
       }
   }

   *main_pic = cvMat2QImage(CollageImg);
    display_screen();
}

void main_window::laod_collage(){
    QString filename(get_imagefile_name());
    std::cout<<filename.toStdString()<<std::endl;
    QImage* img = new QImage, * scaledimg = new QImage;

    if(! ( img->load(filename) ) )
    {
        QMessageBox::information(this,
                                 tr("error message"),
                                 tr("fail to load the image!"));
        delete img;
        return;
    }

    tempcollage = *img;
}

/*
 * Implementation notes:initialization()
 * ------------------------------------------------
 * Initiallize all the components.
 */
void main_window::initialization(){
    spinBox1->disconnect(this);
    slider1->disconnect(this);
    spinBox2->disconnect(this);
    slider2->disconnect(this);
    spinBox_blur->disconnect(this);
    slider_blur->disconnect(this);
    spinBox_saturation->disconnect(this);
    slider_saturation->disconnect(this);
    spinBox_sticker->disconnect(this);
    slider_sticker->disconnect(this);
    spinBox_eye->disconnect(this);
    slider_eye->disconnect(this);
    spinBox_eye->disconnect(this);
    slider_eye->disconnect(this);
    spinBox1->setValue(50);
    spinBox2->setValue(0);
    spinBox_blur->setValue(0);
    spinBox_saturation->setValue(0);
    spinBox_sticker->setValue(15);
    spinBox_eye->setValue(5);
    main_screen->set_m_text(false);
    main_screen->set_m_addsticker(false);
    main_screen->set_m_mosaic(false);
    spinBoxText->disconnect(this);
    textEdt->disconnect(this);
    crop_Button->disconnect(this);

}

//text function part
/*
 * Implementation notes: Hide_text(), Show_text()
 * ------------------------------------------------
 * Set properties of components of text function. Allow hide or show
 * of components for text function.
 */
void main_window:: Show_text(){
    textEdt->setVisible(true);
    spinBoxText->setVisible(true);
    spinBoxText->setValue(20);
}

void main_window:: Hide_text(){
    textEdt->setVisible(false);
    spinBoxText->setVisible(false);
}

/*
 * Implementation notes: text()
 * ------------------------------------------------
 * Connect signals and slots. TextEdit() is
 * called whrn a return signal emitted form stextEdt
 * and TextSizeEdit(int) is called after the value in the
 * spinBoxText is changed.
 */
void main_window::text(){
    spinBoxText->disconnect(this);
    textEdt->disconnect(this);
    main_screen->set_m_text(true);
    connect( spinBoxText, SIGNAL(valueChanged(int)), this, SLOT(TextSizeEdit(int)));
    connect( textEdt, SIGNAL(returnPressed()), this, SLOT( TextEdit()) );
}

void main_window::TextEdit(){
    main_screen->set_text_content( textEdt->text());
}

void main_window::TextSizeEdit(int size){
    int textSize_value = size;
    main_screen->set_text_size(textSize_value);
}



void main_window::mouseMoveEvent(QMouseEvent *event)
{
    if (m_bPressed)
        move(event->pos() - m_point + pos());
}

void main_window::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_bPressed = false;
}

void main_window::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_bPressed = true;
        m_point = event->pos();
    }
}


//format change between QImage & cvMat
Mat QImage2cvMat(QImage image) {
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

QImage cvMat2QImage(const cv::Mat& mat)
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
