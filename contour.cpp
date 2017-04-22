#include "contour.hpp"
#include "car.hpp"
using namespace cv;// Don`t need use cv::,after use namespace.
using namespace std;
char grid2[20][20];
Mat find_contssss (Mat image )	
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
	/*//打印轮廓信息
	std::cout<<"共有外围轮廓："<<contours.size()<<"条"<<std::endl;
	std::vector<std::vector<Point> >::const_iterator itContours = contours.begin();
	for(;itContours != contours.end();++itContours)
	{
		std::cout<<"每个轮廓的长度: "<<itContours->size()<<std::endl;
	}
*/
	
	
	Mat image1(image.size(),CV_8U,Scalar(0));
	drawContours(image1,contours,-1,Scalar(255),-1);
	imshow("image",image1);
	
	return image1;
}
void transf(char arr1[20][20], char arr2[20][20])//copy arr
{
	int i,j;
	
	for(j=0;j<20;j++)
	{
		for(i=0;i<20;i++)
		{		
			arr2[j][i]=arr1[j][i];
		}
	}
}
void compare_arr(char arr1[20][20], char arr2[20][20],char arr3[20][20] ,Mat image)//get finaly data
{
	int i,j;
	
	for(j=0;j<20;j++)
	{
		for(i=0;i<20;i++)
		{		
			if(arr2[j][i]==1&&arr1[j][i]==1)
				{
					arr3[j][i]=1;
					rectangle(image,
					Point(j*32,i*24),
					Point(j*32+31,i*24+23),
					Scalar(0,0,225),
					1,8);
				}
		}
		
	}
}
