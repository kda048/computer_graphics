#include "floyd.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
using namespace cv;
using namespace std;

uchar quantize_pixel(uchar pixel, int n) {
    int color_count = 1 << n;
    int step = 255 / (color_count - 1);
    uchar max_clr = static_cast<uchar>(floor(255 / step) * step);
    uchar res;
    if (round(static_cast<float>(pixel) / (float)step) * step >= max_clr) res = 255;
    else res = static_cast<uchar>(round(static_cast<float>(pixel) / (float)step) * step);
    return res;
}

void floyd_steinberg_dithering_grayscale(Mat& img, int n) {
    Mat out_img = Mat::zeros(img.size(), CV_8U);

    
    for (int y = 0; y < img.rows; y++) {
        for (int x = 0; x < img.cols; x++) {
            
            uchar pixel = img.at<uchar>(y, x);
            
            uchar quantized_pixel = quantize_pixel(pixel, n);
            int error = pixel - quantized_pixel;
            
            if (x < img.cols - 1) {
                
                img.at<uchar>(y, x + 1) = std::min(255, std::max(0, img.at<uchar>(y, x + 1) + error * 7 / 16));
            }
            if (y < img.rows - 1) {
                img.at<uchar>(y + 1, x) = std::min(255, std::max(0, img.at<uchar>(y + 1, x) + error * 5 / 16));
                if (x < img.cols - 1) {
                    img.at<uchar>(y + 1, x + 1) = std::min(255, std::max(0, img.at<uchar>(y + 1, x + 1) + error * 1 / 16));
                }
                if (x > 0) {
                    img.at<uchar>(y + 1, x - 1) = std::min(255, std::max(0, img.at<uchar>(y + 1, x - 1) + error * 3 / 16));
                }
            }

  
            out_img.at<uchar>(y, x) = quantized_pixel;
        }
    }

    img = out_img;
}



