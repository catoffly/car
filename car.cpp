#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/video/background_segm.hpp"
#include "iostream"
using namespace cv;// Don`t need use cv::,after use namespace.
using namespace std;
Mat back (Mat pic);
Mat performOpening(Mat inputImage, int morphologyElement, int morphologySize);
int main(int argc, char **argv)
{
    	VideoCapture video(0); // open the default camera
    	if(!video.isOpened())  // check if we succeeded
        return -1;

    	Mat edges;
	Mat frame1,frame2,frame3,frame4;
	Ptr<BackgroundSubtractor> pMOG;
	Ptr<BackgroundSubtractor> pMOG2;
	pMOG=new BackgroundSubtractorMOG();
	pMOG2=new BackgroundSubtractorMOG2();
    	namedWindow("video",WINDOW_AUTOSIZE);
    	namedWindow("frame1",WINDOW_AUTOSIZE);
	namedWindow("frame2",WINDOW_AUTOSIZE);
    	while(1)
    	{
		Mat frame;
		video >> frame; // get a new frame from camVideoCaptureera
		cvtColor(frame, edges, CV_BGR2GRAY);
		medianBlur(edges,edges,9);//median filter
		threshold(edges,frame3,0,255,THRESH_OTSU);
		//GaussianBlur(edges, edges, Size(9,9), 1.5, 1.5);//gauss filter    
		//Canny(edges, edges, 0, 30, 3);
		//frame4=performOpening(frame3,0,2);
		pMOG->operator()(frame3,frame1);
		pMOG2->operator()(frame3,frame2);
		imshow("frame1",frame1);
		imshow("frame2",frame2);
		//back (edges);
		imshow("video", frame3);
		if(waitKey(30) >= 0) break;
    	}
    	// the camera will be deinitialized automatically in VideoCapture destructor
    	return 0;
}

//erosion and dilation
Mat performOpening(Mat inputImage, int morphologyElement, int morphologySize)
{
    Mat outputImage, tempImage;
    int morphologyType;
    
    if(morphologyElement == 0)
        morphologyType = MORPH_RECT;
    
    else if(morphologyElement == 1)
        morphologyType = MORPH_CROSS;
    
    else if(morphologyElement == 2)
        morphologyType = MORPH_ELLIPSE;
    
    // Create the structuring element for erosion
    Mat element = getStructuringElement(morphologyType, Size(2*morphologySize + 1, 2*morphologySize + 1), Point(morphologySize, morphologySize));
    
    // Apply morphological opening to the image using the structuring element
    erode(inputImage, tempImage, element);
    dilate(tempImage, outputImage, element);
    
    // Return the output image
    return outputImage;
}
