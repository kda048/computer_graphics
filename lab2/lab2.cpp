#include "floyd.h"
#include "stucki.h"
#include <opencv2/opencv.hpp>
#include <iostream>



int main() {

    cv::Mat img = cv::imread("D:\\lab2\\photo\\flowerss.png", cv::IMREAD_GRAYSCALE);
 

    if (img.empty()) {
        std::cerr << "Error: Could not open or find the image!" << std::endl;
        return -1;
    }

    int n = 1; 

    floyd_steinberg_dithering_grayscale(img, n);

  
    std::string outputFileName =  "flowers_gray" + std::to_string(n) + ".png";
    
    cv::imwrite(outputFileName, img);

    return 0;
}
