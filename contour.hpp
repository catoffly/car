#ifndef CONTOUR_H
#define CONTOUR_H

#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/video/background_segm.hpp"
#include "iostream"
#include "stdio.h"
using namespace cv;
Mat find_contssss(Mat image);
void compare_arr(char arr1[20][20], char arr2[20][20],char arr3[20][20] ,Mat image);
void transf(char arr1[20][20], char arr2[20][20]);
extern char grid2[20][20];
#endif






