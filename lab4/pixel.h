#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <opencv2/opencv.hpp> 
#include <iostream> 

using namespace cv;
using namespace std;

void hexToRgb(const string& color, int& r, int& g, int& b);

void outputPixel(Mat& img, int x, int y, string& color);