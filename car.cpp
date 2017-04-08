#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/video/background_segm.hpp"

using namespace cv;// Don`t need use cv::,after use namespace.
using namespace std;
Mat back (Mat pic);

int main(int argc, char **argv)
{
    	VideoCapture video(0); // open the default camera
    	if(!video.isOpened())  // check if we succeeded
        return -1;

    	Mat edges;
	Mat frame1,frame2;
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
		//medianBlur(edges,edges,9);//median filter
		//GaussianBlur(edges, edges, Size(9,9), 1.5, 1.5);//gauss filter    
		//Canny(edges, edges, 0, 30, 3);
		pMOG->operator()(edges,frame1);
		pMOG2->operator()(edges,frame2);
		imshow("frame1",frame1);
		imshow("frame2",frame2);
		//back (edges);
		imshow("video", edges);
		if(waitKey(30) >= 0) break;
    	}
    	// the camera will be deinitialized automatically in VideoCapture destructor
    	return 0;
}
Mat back (Mat pic)
{
	

	
	
	
	
}
