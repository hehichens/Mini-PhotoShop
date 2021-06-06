/*
 * File: main_window.h
 * --------------
 * This file exports the main_window class, which
 * implements a GUI interface of picture editing.
 */

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QWidget>
#include <QPixmap>
#include <QTextEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QFileDialog>
#include <QToolButton>
#include <QLabel>
#include <QLineEdit>
#include <QObject>
#include <QSignalMapper>
#include <QString>
#include "button.h"
#include "ui_main_window.h"
#include <QMouseEvent>
#include <QSpinBox>
#include <QSlider>
#include "blackwhite.h"
#include "brightness.h"
#include "contrast.h"
#include "fliter_color.h"
#include "saturation.h"
#include "rotate.h"
#include "basicfilter.h"
#include "advancedfilter.h"
#include "noise.h"
#include "graph_scene.h"
#include "blur.h"


/*Constant Value*/
extern int BLUR_OPT;
extern int BW_OPT;

namespace Ui
{
    class main_window;
}

Mat QImage2cvMat(QImage image);
QImage cvMat2QImage(const cv::Mat &mat);
class main_window : public QWidget
{
    Q_OBJECT

public:
    explicit main_window(QWidget *parent = nullptr);
    ~main_window();

    bool m_bPressed = true;
    QPoint m_point;
    QString tempcollagename;

    void display_screen();
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void laod_collage();

    bool CanUndo();
    bool CanRedo();

private:
    int num = 0;
    QImage *main_pic = new QImage;
    QImage tempcollage;
    GraphScreen *main_screen = new GraphScreen;
    Mat Temp_main_pic;
    QImage pre_pic;
    QList<QToolButton *> listButtons;
    Ui::main_window *ui;
    QPoint text_point;
    int text_x;
    int text_y;

    void setMainButtons();
    void setAddition();

    /*main button */
    QString get_imagefile_name();
    Button *Tool_Button = new Button();
    Button *Filter_Button = new Button();
    Button *Sticker_Button = new Button();
    Button *Text_Button = new Button();
    Button *Bigeye_Button = new Button();
    Button *Frame_Button = new Button();
    Button *Mosaic_Button = new Button();
    Button *Colorchange_Button = new Button();
    Button *Collage_Button = new Button();

    /*basic button */
    Button *changeSize_Button = new Button();
    Button *close_Button = new Button();
    Button *return_Button = new Button();
    Button *Download_Button = new Button();
    Button *Undo_Button = new Button();
    Button *Redo_Button = new Button();
    Button *TempSave_Button = new Button();
    Button *Delete_Button = new Button();
    QSignalMapper *buttonMapper = new QSignalMapper();

    /*basic button picture */
    QPixmap *small_Img = new QPixmap(":/images/small.png");
    QPixmap *small_PressImg = new QPixmap(":/images/small_press.png");
    QPixmap *large_Img = new QPixmap(":/images/large.png");
    QPixmap *large_PressImg = new QPixmap(":/images/large_press.png");
    QPixmap *return_Img = new QPixmap(":/images/back.png");
    QPixmap *return_PressImg = new QPixmap(":/images/back_press.png");
    QPixmap *close_Img = new QPixmap(":/images/close.png");
    QPixmap *close_PressImg = new QPixmap(":/images/close_press.png");
    QPixmap *download_Img = new QPixmap(":/images/download.png");
    QPixmap *download_PressImg = new QPixmap(":/images/download_press.png");
    QPixmap *undo_Img = new QPixmap(":/images/undo.png");
    QPixmap *undo_PressImg = new QPixmap(":/images/undo_press.png");
    QPixmap *redo_Img = new QPixmap(":/images/redo.png");
    QPixmap *redo_PressImg = new QPixmap(":/images/redo_press.png");
    QPixmap *tempsave_Img = new QPixmap(":/images/tempsave.png");
    QPixmap *tempsave_PressImg = new QPixmap(":/images/tempsave_press.png");
    QPixmap *delete_Img = new QPixmap(":/images/delete.png");
    QPixmap *delete_PressImg = new QPixmap(":/images/delete_press.png");

    /*main button picture */
    QPixmap *Tool_Img = new QPixmap(":/images/Tool_button.png");
    QPixmap *Tool_PressImg = new QPixmap(":/images/Tool_press.png");
    QPixmap *Frame_Img = new QPixmap(":/images/Frame_button.png");
    QPixmap *Frame_PressImg = new QPixmap(":/images/Frame_press.png");
    QPixmap *hidde_Img = new QPixmap(":/images/bear.png");
    QPixmap *BackColor_Img = new QPixmap(":/images/back_color.png");
    QPixmap *BackColor_PressImg = new QPixmap(":/images/backcolor_press.png");
    QPixmap *Mosaic_Img = new QPixmap(":/images/Mosaic_button.png");
    QPixmap *Mosaic_PressImg = new QPixmap(":/images/Mosaic_press.png");
    QPixmap *Filter_Img = new QPixmap(":/images/Filter_button.png");
    QPixmap *Filter_PressImg = new QPixmap(":/images/Filter_press.png");
    QPixmap *Text_Img = new QPixmap(":/images/Text_button.png");
    QPixmap *Text_PressImg = new QPixmap(":/images/Text_press.png");
    QPixmap *Sticker_Img = new QPixmap(":/images/Sticker_button.png");
    QPixmap *Sticker_PressImg = new QPixmap(":/images/Sticker_press.png");
    QPixmap *Bigeye_Img = new QPixmap(":/images/Bigeye_button.png");
    QPixmap *Bigeye_PressImg = new QPixmap(":/images/Bigeye_press.png");
    QPixmap *Collage_Img = new QPixmap(":/images/Collage_button.png");
    QPixmap *Collage_PressImg = new QPixmap(":/images/Collage_press.png");

    /*text */
    QTextEdit *dictum = new QTextEdit();
    QLineEdit *textEdt = new QLineEdit();
    QSpinBox *spinBoxText = new QSpinBox();

    /*tool */
    Button *tool_button_CP = new Button(); //crop
    Button *tool_button_RT = new Button(); //rotation
    Button *tool_button_BW = new Button(); //black white
    Button *tool_button_BR = new Button(); //brightness
    Button *tool_button_CT = new Button(); //contrast
    Button *tool_button_FT = new Button(); //filter color
    Button *tool_button_ST = new Button(); //saturation
    Button *tool_button_BL = new Button(); //blur
    QPixmap *BlackWhite_Img = new QPixmap(":/images/BlackWhite.png");
    QPixmap *BlackWhite_PressImg = new QPixmap(":/images/BlackWhite_press.png");
    QPixmap *Brightness_Img = new QPixmap(":/images/brightness.png");
    QPixmap *Brightness_PressImg = new QPixmap(":/images/brightness_press.png");
    QPixmap *Contrast_Img = new QPixmap(":/images/Contrast.png");
    QPixmap *Contrast_PressImg = new QPixmap(":/images/Contrast_press.png");
    QPixmap *ColorFilter_Img = new QPixmap(":/images/colorFilter.png");
    QPixmap *ColorFilter_PressImg = new QPixmap(":/images/colorFilter_press.png");
    QPixmap *Saturation_PressImg = new QPixmap(":/images/Saturation_press.png");
    QPixmap *Saturation_Img = new QPixmap(":/images/Saturation.png");
    QPixmap *Rotation_PressImg = new QPixmap(":/images/rotation_press.png");
    QPixmap *Rotation_Img = new QPixmap(":/images/rotation.png");
    QPixmap *Crop_PressImg = new QPixmap(":/images/crop_press.png");
    QPixmap *Crop_Img = new QPixmap(":/images/crop.png");
    QPixmap *Blur_PressImg = new QPixmap(":/images/Blur_press.png");
    QPixmap *Blur_Img = new QPixmap(":/images/Blur.png");

    /*filter */
    QLineEdit *basic_filter_label = new QLineEdit();
    QLineEdit *advanced_filter_label = new QLineEdit();
    Button *filter_button_old = new Button();
    Button *filter_button_comic = new Button();
    Button *filter_button_exposure = new Button();
    Button *filter_button_magic = new Button();
    Button *filter_button_silence = new Button();
    Button *filter_button_beauty = new Button();
    Button *filter_button_highlight = new Button();
    Button *filter_button_softlight = new Button();
    Button *filter_button_diffuse = new Button();
    Button *filter_button_expand = new Button();
    Button *filter_button_shrink = new Button();
    Button *filter_button_strike = new Button();
    Button *filter_button_volution = new Button();
    Button *filter_button_wave = new Button();
    Button *filter_button_sketch = new Button();
    Button *filter_button_neon = new Button();
    Button *filter_button_carve = new Button();
    Button *filter_button_embossment = new Button();
    QPixmap *fOld_Img = new QPixmap(":/images/f_old.png");
    QPixmap *fComic_Img = new QPixmap(":/images/f_comic.png");
    QPixmap *fExposure_Img = new QPixmap(":/images/f_exposure.png");
    QPixmap *fMagic_Img = new QPixmap(":/images/f_magic.png");
    QPixmap *fSilence_Img = new QPixmap(":/images/f_silence.png");
    QPixmap *fBeauty_Img = new QPixmap(":/images/f_beauty.png");
    QPixmap *fHighlight_Img = new QPixmap(":/images/f_highlight.png");
    QPixmap *fSoftlight_Img = new QPixmap(":/images/f_softlight.png");
    QPixmap *fDiffuse_Img = new QPixmap(":/images/f_diffuse.png");
    QPixmap *fExpand_Img = new QPixmap(":/images/f_expand.png");
    QPixmap *fShrink_Img = new QPixmap(":/images/f_shrink.png");
    QPixmap *fStrike_Img = new QPixmap(":/images/f_strike.png");
    QPixmap *fVolution_Img = new QPixmap(":/images/f_volution.png");
    QPixmap *fWave_Img = new QPixmap(":/images/f_wave.png");
    QPixmap *fSketch_Img = new QPixmap(":/images/f_sketch.png");
    QPixmap *fNeon_Img = new QPixmap(":/images/f_neon.png");
    QPixmap *fCarve_Img = new QPixmap(":/images/f_carve.png");
    QPixmap *fEmbossment_Img = new QPixmap(":/images/f_embossment.png");
    Button *filter_button_pepper = new Button();
    Button *filter_button_grain = new Button();
    QPixmap *fGrain_Img = new QPixmap(":/images/f_grain.png");
    QPixmap *fPepper_Img = new QPixmap(":/images/f_pepper.png");

    /*function layout */
    QVBoxLayout *Vlayout_Tool = new QVBoxLayout();
    QVBoxLayout *Vlayout_Filter = new QVBoxLayout();
    QVBoxLayout *Vlayout_Sticker = new QVBoxLayout();
    QVBoxLayout *Vlayout_Mosaic = new QVBoxLayout();
    QVBoxLayout *Vlayout_Background = new QVBoxLayout();
    QVBoxLayout *Vlayout_Frame = new QVBoxLayout();

    /*background color change button*/
    Button *red_back = new Button();
    Button *blue_back = new Button();
    Button *white_back = new Button();
    QPixmap *white_Img = new QPixmap(":/images/white.png");

    /*redo/undo/do*/
    bool notChange = true;
    bool show_hidden = false;
    std::stack<QImage> undo_stack;
    std::stack<QImage> redo_stack;
    int undostack_count = 0;
    int redostack_count = 0;

    /*inside Tool*/
    //crop
    QSpinBox *spinBox_crop = new QSpinBox();
    QSlider *slider_crop = new QSlider(Qt::Horizontal);

    //B&W
    QPushButton *binary_Button = new QPushButton();
    QPushButton *otsu_Button = new QPushButton();
    QSpinBox *spinBox_bw = new QSpinBox();
    QSlider *slider_bw = new QSlider(Qt::Horizontal);
    
    //brightness
    QSpinBox *spinBox1 = new QSpinBox();
    QSlider *slider1 = new QSlider(Qt::Horizontal);
    //contrast
    QSpinBox *spinBox2 = new QSpinBox();
    QSlider *slider2 = new QSlider(Qt::Horizontal);
    //saturation
    QSpinBox *spinBox_saturation = new QSpinBox();
    QSlider *slider_saturation = new QSlider(Qt::Horizontal);
    //color filter
    Button *cf_red = new Button();
    Button *cf_orange = new Button();
    Button *cf_yellow = new Button();
    Button *cf_green = new Button();
    Button *cf_blue = new Button();
    Button *cf_purple = new Button();
    Button *cf_pink = new Button();
    QPixmap *red_Img = new QPixmap(":/images/red.png");
    QPixmap *orange_Img = new QPixmap(":/images/orange.png");
    QPixmap *yellow_Img = new QPixmap(":/images/yellow.png");
    QPixmap *blue_Img = new QPixmap(":/images/blue.png");
    QPixmap *pink_Img = new QPixmap(":/images/pink.png");
    QPixmap *green_Img = new QPixmap(":/images/green.png");
    QPixmap *purple_Img = new QPixmap(":/images/purple.jpeg");
    //rotate
    QPushButton *LeftRotate_Button = new QPushButton();
    QPushButton *RightRotate_Button = new QPushButton();
    QPushButton *HorizontalFlip_Button = new QPushButton();
    QPushButton *VerticalFlip_Button = new QPushButton();
    QPushButton *DiagonalFlip_Button = new QPushButton();
    //blur
    QPushButton *gussian_blur_Button = new QPushButton();
    QPushButton *median_blur_Button = new QPushButton();
    QPushButton *mean_blur_Button = new QPushButton();
    QSpinBox *spinBox_blur = new QSpinBox();
    QSlider *slider_blur = new QSlider(Qt::Horizontal);
    //crop
    //Button *crop_Button = new Button();
    //QPixmap *confirm_Img = new QPixmap(":/images/crop_confirm.png");
    //QPixmap *confirm_PressImg = new QPixmap(":/images/crop_confirm_press.png");

    /*Sticker*/
    QLineEdit *basic_sticker_label = new QLineEdit();
    QLineEdit *advanced_sticker_label = new QLineEdit();
    QSpinBox *spinBox_sticker = new QSpinBox();
    QSlider *slider_sticker = new QSlider(Qt::Horizontal);
    Button *sticker1 = new Button();
    Button *sticker2 = new Button();
    Button *sticker3 = new Button();
    Button *sticker4 = new Button();
    Button *sticker5 = new Button();
    Button *sticker6 = new Button();
    Button *sticker7 = new Button();
    QPixmap *Sticker1_Img = new QPixmap(":/images/Sticker1.png");
    QPixmap *Sticker2_Img = new QPixmap(":/images/Sticker2.png");
    QPixmap *Sticker3_Img = new QPixmap(":/images/Sticker3.png");
    QPixmap *Sticker4_Img = new QPixmap(":/images/Sticker4.png");
    QPixmap *Sticker5_Img = new QPixmap(":/images/Sticker5.png");
    QPixmap *Sticker6_Img = new QPixmap(":/images/Sticker6.png");
    QPixmap *Sticker7_Img = new QPixmap(":/images/Sticker7.png");

    /*Big eye*/
    QSpinBox *spinBox_eye = new QSpinBox();
    QSlider *slider_eye = new QSlider(Qt::Horizontal);

    /*Mosaic */
    Button *small_mosaic = new Button();
    Button *median_mosaic = new Button();
    Button *large_mosaic = new Button();
    QPixmap *smallMosaic_Img = new QPixmap(":/images/small_mo.png");
    QPixmap *medianMosaic_Img = new QPixmap(":/images/median_mo.png");
    QPixmap *largeMosaic_Img = new QPixmap(":/images/large_mo.png");

    /*Frame*/
    Button *frame1 = new Button();
    Button *frame2 = new Button();
    Button *frame3 = new Button();
    Button *frame4 = new Button();
    Button *frame5 = new Button();
    Button *frame6 = new Button();
    Button *frame7 = new Button();
    Button *frame8 = new Button();
    QPixmap *fr_Heart_Img = new QPixmap(":/images/fr_Heart.png");
    QPixmap *fr_Vintage_Img = new QPixmap(":/images/fr_Vintage.png");
    QPixmap *fr_Cocoa_Img = new QPixmap(":/images/fr_Cocoa.png");
    QPixmap *fr_Gaudy_Img = new QPixmap(":/images/fr_Gaudy.png");
    QPixmap *fr_Dynamic_Img = new QPixmap(":/images/fr_Dynamic.png");
    QPixmap *fr_Mirror_Img = new QPixmap(":/images/fr_Mirror.png");
    QPixmap *fr_Black_Img = new QPixmap(":/images/fr_Black.png");
    QPixmap *fr_White_Img = new QPixmap(":/images/fr_White.png");

    /*Collage*/
    Button *collage_v = new Button();
    Button *collage_h = new Button();
    QPixmap *collageV_Img = new QPixmap(":/images/collage_v.png");
    QPixmap *collageH_Img = new QPixmap(":/images/collage_h.png");

    void add_sticker(int mx, int my);

private slots:
    void display_graphscreen();
    void MainClose();
    void changeWindowSize();
    void setDicText();
    void ButtonHide();
    void ButtonShow();

    void add_image_button();
    void on_button_clicked();
    void display_image(QString filename);

    /*Tool*/
    void Set_Tool();
    void Hide_Tool();
    void Show_Tool();

    void Hide_BW_Slider();
    void Show_BW_Slider();

    void Hide_Bright_Slider();
    void Show_Bright_Slider();

    void Hide_Contrast_Slider();
    void Show_Contrast_Slider();

    void Hide_FilterColor_Button();
    void Show_FilterColor_Button();

    void Hide_Rotate_Button();
    void Show_Rotate_Button();

    void Hide_Saturation_Slider();
    void Show_Saturation_Slider();

    void Hide_Blur_Slider();
    void Show_Blur_Slider();

    void Hide_crop();
    void Show_crop();

    void Tool_blackwhite();
    void temp_blackwhite();
    void Tool_brightness();
    void temp_brightness();
    void Tool_contrast();
    void temp_contrast();
    void Tool_cf();
    void temp_saturation();
    void Tool_saturation();
    void Tool_rotate();
    void Tool_crop();
    void temp_crop();
    void Tool_blur();
    void temp_blur();

    /*Filter*/
    void Set_Filter();
    void Hide_Filter();
    void Show_Filter();
    void Filter();

    /*Sticker*/
    void Set_Sticker();
    void Hide_Sticker();
    void Show_Sticker();
    void Sticker_Add();
    void temp_StickerAdd();

    /*background*/
    void Set_background();
    void Hide_background();
    void Show_background();
    void back_flag();

    /*big eye*/
    void Show_eyeSlider();
    void Hide_eyeSlider();
    void temp_BigEye();
    void Big_eye();

    /*mosaic*/
    void Set_Mosaic();
    void Hide_Mosaic();
    void Show_Mosaic();
    void Mosaic();

    /*frame*/
    void Set_Frame();
    void Hide_Frame();
    void Show_Frame();
    void Frame();

    /*collage*/
    void Show_collageButton();
    void Hide_collageButton();
    void Collage();

    /*redo/undo/do*/
    void UndoAction();
    void RedoAction();
    void DoAction();
    void DownloadAction();
    void DeleteAction();

    /*text*/
    void text();
    void Show_text();
    void Hide_text();
    void TextEdit();
    void TextSizeEdit(int size);
    void initialization();
};

#endif // MAIN_WINDOW_H
