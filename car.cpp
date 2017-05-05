#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/video/background_segm.hpp"
#include "iostream"
#include "stdio.h"
#include "contour.hpp"
#include "car.hpp"
#include "gpio.hpp"

using namespace cv;// Don`t need use cv::,after use namespace.
using namespace std;


Mat performOpening(Mat inputImage, int morphologyElement, int morphologySize);
Mat frameDiff(Mat prevFrame, Mat curFrame, Mat nextFrame);
void REC (Mat image,Mat image2);
Rect grid_s(0,0,32,24);
char grid[20][20];
char grid1[20][20],grid3[20][20];
int  point_mun=0;
Mat roiimage;
int main(int argc, char **argv)
{
    	VideoCapture video(0); // open the default camera h480 w 640
    	if(!video.isOpened())  // check if we succeeded
        return -1;
	gpio_init();
	pwn_init();
	Mat frame1,frame2,frame3,frame4,frame5,frame6,frame7,frame8,frame9,frame10;
	Mat prevFrame, curFrame, nextFrame;
	Mat prevFrame1, curFrame1, nextFrame1;
	Size s;
		
	video >> frame1; // get a new frame from camVideoCaptureera
	cvtColor(frame1, frame2, CV_BGR2GRAY);
	medianBlur(frame2,frame2,9);//median filterwas
	threshold(frame2,frame3,10,255,THRESH_BINARY);
	frame4=performOpening(frame3,0,2);
	prevFrame = frame4;
       	curFrame = frame4;
        nextFrame = frame4;

	prevFrame1 = frame4;
       	curFrame1 = frame4;
        nextFrame1 = frame4;
	
	s = frame4.size();	
	printf("h %d",s.height);
	printf("w %d",s.width);
	
    	namedWindow("video",WINDOW_AUTOSIZE);
    	namedWindow("frame6",WINDOW_AUTOSIZE);
	//namedWindow("image",WINDOW_AUTOSIZE);
	//namedWindow("frame4",WINDOW_AUTOSIZE);
    	while(1)
    	{
		Mat frame;
		video >> frame1; // get a new frame from camVideoCaptureera
		cvtColor(frame1, frame2, CV_BGR2GRAY);
		medianBlur(frame2,frame2,9);//median filter
		//threshold(frame2,frame3,0,255,THRESH_OTSU);
		//GaussianBlur(frame2, frame2, Size(9,9), 1.5, 1.5);//gauss filter    
		
		threshold(frame2,frame3,0,255,THRESH_OTSU);
		frame4=find_contssss(frame3);
		frame5=performOpening(frame4,1,1);
		frame6 = frame5.clone();

		prevFrame = curFrame;
       		curFrame = nextFrame;
           	nextFrame = frame6;
		
		frame7=frameDiff( prevFrame,  curFrame,  nextFrame);
		medianBlur(frame7,frame7,9);		
		REC (frame1,frame7);
		imshow("frame6",frame7);
		imshow("video", frame1);
		
		
		
		if(waitKey(30) >= 0) break;
    	}
    	// the camera will be deinitialized automatically in VideoCapture destructor
	video.release();//close video
	destroyAllWindows();//close window
	pwm_uninit();
	gpio_uninit();//
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
   // erode(inputImage, tempImage, element);
    //dilate(tempImage, outputImage, element);
    dilate(inputImage, tempImage, element);
    erode(tempImage, outputImage, element);
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

void REC (Mat image,Mat image2)
{
	int i,j;
	int green=255,red=255;
	for(i=0;i<20;i++)//lie
	{	
		
		for(j=0;j<20;j++)//hang
		{	
			grid_s.x=j*32;
			grid_s.y=i*24;
			image2(grid_s).copyTo(roiimage);
			point_mun = countNonZero(roiimage);
			if(point_mun>1)
			{
				grid[j][i] = 1;
				red = 255;
				green = 0;
			}
			else
			{
				grid[j][i] = 0;
				red = 0;
				green = 255;
			}
			rectangle(image,
				Point(j*32,i*24),
				Point(j*32+31,i*24+23),
				Scalar(0,green,red),
				1,8);
			
		}
	}


}





