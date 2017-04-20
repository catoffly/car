#ifndef CAR_H
#define CAR_H

#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/video/background_segm.hpp"
#include "iostream"
#include "stdio.h"
using namespace cv;
using namespace std;

Mat performOpening(Mat inputImage, int morphologyElement, int morphologySize);
Mat frameDiff(Mat prevFrame, Mat curFrame, Mat nextFrame);
void REC (Mat image,Mat image2);

extern Rect grid_s;
extern char grid[20][20];
extern char grid1[20][20],grid3[20][20];
extern int  point_mun;
extern Mat roiimage;
#endif
