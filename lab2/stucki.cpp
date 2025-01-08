#include "stucki.h"
#include "floyd.h"
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;


void stucki_dithering_grayscale(Mat& img, int n) {

    Mat out_img = Mat::zeros(img.size(), CV_8U);

    
    int matrix[3][5] = {
        {0, 0, 0, 8, 4},
        {2, 4, 8, 4, 2},
        {1, 2, 4, 2, 1}
    };

    
    for (int y = 0; y < img.rows; y++) {
        for (int x = 0; x < img.cols; x++) {
            
            uchar pixel = img.at<uchar>(y, x);
            
            uchar quantized_pixel = quantize_pixel(pixel, n);
            
            int error = pixel - quantized_pixel;
            
            for (int dy = -1; dy <= 1; dy++) {
                for (int dx = -2; dx <= 2; dx++) {
                    if (x + dx >= 0 && x + dx < img.cols && y + dy >= 0 && y + dy < img.rows) {
                        if (matrix[dy + 1][dx + 2] != 0) {
                            uchar& neighbor_pixel = img.at<uchar>(y + dy, x + dx);
                            neighbor_pixel = std::min(255, std::max(0, neighbor_pixel + error * matrix[dy + 1][dx + 2] / 42));
                        }
                    }
                }
            }

            out_img.at<uchar>(y, x) = quantized_pixel;
        }
    }

    img = out_img;
}


