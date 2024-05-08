#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include "pch.h"
#include "Resource.h"
#include<math.h>
#include<time.h>

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include<opencv2/highgui/highgui_c.h>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\opencv.hpp>
using namespace std;
using namespace cv;


void Init(CWnd* pWnd1, CRect* rect);

Mat Rotate(Mat img, double angle);

void SaveImage(Mat img);

Mat ToGray(Mat img);

Mat ToRGB(Mat img_gray);

Mat LineTrans(Mat img_gray, float min, float max);

Mat PartTrans(Mat img, float a1, float b1, float a2, float b2);

Mat LogTrans(Mat img, float a, float b, float c);

void Show_Histogram(Mat img, String name);

Mat Histogram_Match(Mat img1, Mat img2);

Mat Add_Saltpepper(Mat img, int n);

Mat Add_Gaussian(Mat img, int a, int b);

Mat ILPF(Mat img);

Mat Add_Photo(Mat img1, Mat img2, int a);

Mat To_Line(Mat img);

Mat Add_Grain(Mat img, int rank);

Mat Inverted_Color(Mat img);

Mat Photo_Relief(Mat img);

Mat InWater(Mat img);

#endif 



