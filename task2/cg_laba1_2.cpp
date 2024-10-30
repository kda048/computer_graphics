#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// Функция для преобразования изображения в полутоновое
Mat toGrayscale(const Mat& src) {
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    return gray;
}

int main() {

    Mat image1 = imread("D:\\lab1.2__photo2.png");
    Mat image2 = imread("D:\\lab1.2__photo1.png");
    Mat alphaChannel = imread("D:\\lab1.2__photo3.png");


    if (image1.empty()) {
        cerr << "Ошибка: Не удалось загрузить первое изображение." << endl;
        return -1;
    }
    if (image2.empty()) {
        cerr << "Ошибка: Не удалось загрузить второе изображение." << endl;
        return -1;
    } if (alphaChannel.empty()) {
        cerr << "Ошибка: Не удалось загрузить третье изображение." << endl;
        return -1;
    }

    // Проверка на одинаковый размер
    if (image1.size() != image2.size() || image1.size() != alphaChannel.size()) {
        cerr << "Изображения должны быть одинакового размера." << endl;
        return -1;
    }

    alphaChannel = toGrayscale(alphaChannel);

    Mat blendedImage(image1.size(), CV_8UC3);
    for (int y = 0; y < image1.rows; y++) {
        for (int x = 0; x < image1.cols; x++) {

            uchar alpha = alphaChannel.at<uchar>(y, x);

            blendedImage.at<Vec3b>(y, x)[0] = (alpha * image1.at<Vec3b>(y, x)[0] + (255 - alpha) * image2.at<Vec3b>(y, x)[0]) / 255;
            blendedImage.at<Vec3b>(y, x)[1] = (alpha * image1.at<Vec3b>(y, x)[1] + (255 - alpha) * image2.at<Vec3b>(y, x)[1]) / 255;
            blendedImage.at<Vec3b>(y, x)[2] = (alpha * image1.at<Vec3b>(y, x)[2] + (255 - alpha) * image2.at<Vec3b>(y, x)[2]) / 255;
        }
    }

    imwrite("D:\\bland_image.png", blendedImage);

    imshow("Смешанное изображение", blendedImage);
    waitKey(0);

    return 0;
}

