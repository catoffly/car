#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/video/background_segm.hpp"
#include "iostream"
#include "stdio.h"
using namespace cv;// Don`t need use cv::,after use namespace.
using namespace std;


Mat performOpening(Mat inputImage, int morphologyElement, int morphologySize);
Mat frameDiff(Mat prevFrame, Mat curFrame, Mat nextFrame);
void REC (Mat image);
int main(int argc, char **argv)
{
    	VideoCapture video(0); // open the default camera h480 w 640
    	if(!video.isOpened())  // check if we succeeded
        return -1;

	Mat frame1,frame2,frame3,frame4,frame5;
	Mat prevFrame, curFrame, nextFrame;
	Size s;
	/*
	Ptr<BackgroundSubtractor> pMOG;
	Ptr<BackgroundSubtractor> pMOG2;
	pMOG=new BackgroundSubtractorMOG();
	pMOG2=new BackgroundSubtractorMOG2();
	*/
	video >> frame1; // get a new frame from camVideoCaptureera
	cvtColor(frame1, frame2, CV_BGR2GRAY);
	medianBlur(frame2,frame2,9);//median filterwas
	threshold(frame2,frame3,10,255,THRESH_BINARY);
	frame4=performOpening(frame3,0,2);
	prevFrame = frame4;
       	curFrame = frame4;
        nextFrame = frame4;
	
	s = frame4.size();	
	printf("h %d",s.height);
	printf("w %d",s.width);
	
    	namedWindow("video",WINDOW_AUTOSIZE);
    	namedWindow("frame5",WINDOW_AUTOSIZE);
	//namedWindow("frame4",WINDOW_AUTOSIZE);
    	while(1)
    	{
		Mat frame;
		video >> frame1; // get a new frame from camVideoCaptureera
		cvtColor(frame1, frame2, CV_BGR2GRAY);
		medianBlur(frame2,frame2,9);//median filter
		//threshold(frame2,frame3,0,255,THRESH_OTSU);
		//GaussianBlur(edges, edges, Size(9,9), 1.5, 1.5);//gauss filter    
		//Canny(edges, edges, 0, 30, 3);
		
		frame3=performOpening(frame2,0,2);
		frame4=frameDiff( prevFrame,  curFrame,  nextFrame);
		threshold(frame4,frame5,10,255,THRESH_BINARY);
		medianBlur(frame5,frame5,9);//median filter
		//pMOG->operator()(frame4,frame1);
		//pMOG2->operator()(frame4,frame2);
		prevFrame = curFrame;
       		curFrame = nextFrame;
           	nextFrame = frame3;
		
		REC (frame1);
		

		imshow("frame5",frame5);
		//imshow("frame4",frame4);
		imshow("video", frame1);
		if(waitKey(30) >= 0) break;
    	}
    	// the camera will be deinitialized automatically in VideoCapture destructor
	video.release();//close video
	destroyAllWindows();//close window
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
//two pictures will use "and" .
Mat frameDiff(Mat prevFrame, Mat curFrame, Mat nextFrame)
{
    Mat diffFrames1, diffFrames2, output;
    
    // Compute absolute difference between current frame and the next frame
    absdiff(nextFrame, curFrame, diffFrames1);
    
    // Compute absolute difference between current frame and the previous frame
    absdiff(curFrame, prevFrame, diffFrames2);
    
    // Bitwise "AND" operation between the above two diff images
    bitwise_and(diffFrames1, diffFrames2, output);
    
    return output;
}

void REC (Mat image)
{
	int i,j;
	int green=255,red=255;
	for(i=0;i<20;i++)
	{	
		
		for(j=0;j<20;j++)
		{
			rectangle(image,
				Point(i*32,j*24),
				Point(i*32+31,j*24+23),
				Scalar(0,green,0),
				1,8
					);
		}
	}

}

