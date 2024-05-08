#ifndef _SLIDERSET_H_
#define _SLIDERSET_H_

#include "pch.h"
#include "Resource.h"
#include<math.h>

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include<opencv2/highgui/highgui_c.h>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\opencv.hpp>
using namespace std;
using namespace cv;

Mat Zoom(Mat img, double size);

Mat Bright_Contrast(Mat img, int B, float C);

Mat Saturation(Mat img, float saturation);

Mat View(Mat img, float weight);

Mat HighLight_shadow(Mat img, int highlight, int tip);

Mat Color(Mat img, int color, int tip);

#endif 
