#include "contour.hpp"
using namespace cv;// Don`t need use cv::,after use namespace.
using namespace std;
void find_contssss (Mat image )	
{
	//获取轮廓
	std::vector<std::vector<Point> > contours;
	std::vector<std::vector<Point> > contours1;
	//获取轮廓：
	findContours(image,	//图像
		contours,	//轮廓点
				//包含图像拓扑结构的息（可选参数，这里没选）
		CV_RETR_EXTERNAL,			//获取轮廓的方法（这里获取外围轮廓）
		CV_CHAIN_APPROX_NONE);		//轮廓近似的方法（这里不近似，获取全部轮廓）
	//打印轮廓信息
	std::cout<<"共有外围轮廓："<<contours.size()<<"条"<<std::endl;
	std::vector<std::vector<Point> >::const_iterator itContours = contours.begin();
	for(;itContours != contours.end();++itContours)
	{
		std::cout<<"每个轮廓的长度: "<<itContours->size()<<std::endl;
	}
	
	//除去太长或者太短的轮廓
	/*
	int cmin = 100;
	int cmax = 1000;
	std::vector<std::vector<Point> >::const_iterator itc = contours.begin();
	std::vector<std::vector<Point> >::const_iterator itc1 = contours1.begin();
	while(itc != contours.end())
	{
		if(itc->size() < cmin || itc->size() > cmax)
		itc1->size() = itc->size();
		else
		{	++itc;
			++itc1;
		}
	}
	*/
	Mat image1(image.size(),CV_8U,Scalar(0));
	drawContours(image1,contours,-1,Scalar(255),-1);
	imshow("image",image1);
}
