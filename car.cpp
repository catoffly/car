#include "opencv2/opencv.hpp"
using namespace cv;// Don`t need use cv::,after use namespace.

int main(int argc, char **argv)
{
    VideoCapture video(0); // open the default camera
    if(!video.isOpened())  // check if we succeeded
        return -1;
 
    Mat edges;
    namedWindow("lilinjun",1);
    for(;;)
    {
        Mat frame;
        video >> frame; // get a new frame from camVideoCaptureera
        cvtColor(frame, edges, CV_BGR2GRAY);
        GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
        Canny(edges, edges, 0, 30, 3);
        imshow("lilinjun", edges);
        if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
