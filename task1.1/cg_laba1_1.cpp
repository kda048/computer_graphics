#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

int main() {
    Mat inputImage = imread("D:\\загрузкия_D\\flowers.png", IMREAD_GRAYSCALE);

    if (inputImage.empty()) {
        cout << "Ошибка: Не удалось загрузить изображение." << endl;
        return 1;
    }

    Mat outputImage = Mat::zeros(inputImage.size(), CV_8UC1);

    int centerX = inputImage.cols / 2;
    int centerY = inputImage.rows / 2;


    int maxRadius = min(centerX, centerY);


    for (int y = 0; y < inputImage.rows; y++) {
        for (int x = 0; x < inputImage.cols; x++) {
            double distance = sqrt(pow(x - centerX, 2) + pow(y - centerY, 2));

            if (distance <= maxRadius) {
                outputImage.at<uchar>(y, x) = inputImage.at<uchar>(y, x);
            }
            else {
                outputImage.at<uchar>(y, x) = 0;
            }
        }
    }

    imwrite("D:\\загрузкия_D\\lab_1.1_end.png", outputImage);

    imshow("Круглое полутоновое изображение", outputImage);

    waitKey(0);
    return 0;
}

