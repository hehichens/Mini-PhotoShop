/*
 * File : big_eyes.hpp
 * -------------------
 * this program implement a pictur_club classs
 */
#ifndef BIG_EYE_H
#define BIG_EYE_H
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
* class: picture_club
* ------------------------------
* this class implement a picture club as the object
* to control enlarge eyes.
*/

class picture_club
{
    typedef  vector<Rect> RectVector;
public:
    /*
    * Constructor and detructor: Pictruce_club
    * ------------------------------
    * Initializes a new empty picture_culb object.
    */

    picture_club();
    ~picture_club();

    /*functiion: DetectFace, DetectEyes
     * usafe: pc.detecface()
     * -------------------------------------
     * These 2 functions detect the face and eyes in the image
     */

    RectVector DetectFace();
    RectVector DetectEyes(const Rect &);

    //放大指定区域
    /*functiion: EnlargeRects
     * usafe: EnlargeRects(& eyeRect)
     * -------------------------------------
     * This function enlarge the select rect and stick it back to the
     * original image
     */
    void EnlargeRects(const Rect &, double size);

    /*functiion:GrabImage
     * usafe: pc.grabimage()
     * -------------------------------------
     * These 2 functions grab a new input image and if no input Mat image
     * the function will open the camera to take image.
     */
    void GrabImage();
    void GrabImage(const Mat &image);

    /*functiion: cvtGray
     * usafe: pc.cvtGray()
     * -------------------------------------
     * This function generate the grayscale of the input image.
     */
    void cvtGray(){
        cvtColor(capture_image,grayscaled_capture, COLOR_BGR2GRAY);
    }

    /*functiion: showImage
     * usage: pc.showImage()
     * -------------------------------------
     * show the image
     */
    void ShowImage(const string windowname = "sample"){
        imshow(windowname,capture_image);
        waitKey(0);
    }
    Mat capture_image;
private:
    VideoCapture *capture_device;
    Mat_<uint8_t> grayscaled_capture;

    Size processing_size;


    CascadeClassifier face_c;
    CascadeClassifier eyes_c;

};

/*function: eyesBigger
 * ------------------------------------
 * usage: take a input image and with the help of the picture_club
 * enlarge the eye rect of the image.
 */
Mat eyesBigger(Mat input_image, double howBig = 1.1);

/*function: chanegBackground
 * ------------------------------------
 * Take a identification image as the input and change the background color
 * to the correspoding color the user choose
 */
Mat changeBackground(Mat image, int color_flag);
Mat addear(Mat image, Mat logo);

#endif // BIG_EYE_H
