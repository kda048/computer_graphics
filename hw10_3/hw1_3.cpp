#include <chrono>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <cmath>

using namespace std;
using namespace cv;


void RGBtoHSL(Vec3b& rgb, float& H, float& S, float& L) {
    float r = rgb[2] / 255.0f;
    float g = rgb[1] / 255.0f;
    float b = rgb[0] / 255.0f;

    float max_val = max({ r, g, b });
    float min_val = min({ r, g, b });

    float delta = max_val - min_val;

    if (delta == 0) {
        H = 0;
        S = 0;
        L = 0;
        return;
    }

    L = (max_val + min_val) / 2.0f;

    if (L < 0.5f) {
        if (max_val + min_val == 0) {
            S = 0;
        }
        else {
            S = delta / (max_val + min_val);
        }
    }
    else {
        if (2.0f - max_val - min_val == 0) {
            S = 0;
        }
        else {
            S = delta / (2.0f - max_val - min_val);
        }

    }


    if (max_val == r) {
        H = 60 * fmod((g - b) / delta, 6);
    }
    else if (max_val == g) {
        H = 60 * (((b - r) / delta) + 2);
    }
    else if (max_val == b) {
        H = 60 * (((r - g) / delta) + 4);
    }
    if (H < 0) H = H + 360;
}


static void calculateHistogram(Mat& image, vector<int>& h_hist,
    vector<int>& s_hist, vector<int>& l_hist, int bins) {
    if (image.empty()) return;
    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            Vec3b pixel = image.at<Vec3b>(i, j);
            float h, s, l;
            RGBtoHSL(pixel, h, s, l);

            int h_idx = static_cast<int>(round(h / 360.0f * bins));
            int s_idx = static_cast<int>(round(s * bins));
            int l_idx = static_cast<int>(round(l * bins));

            if (h_idx >= 0 && h_idx < bins) {
                h_hist[h_idx]++;
            }

            if (s_idx >= 0 && s_idx < bins) {
                s_hist[s_idx]++;
            }

            if (l_idx >= 0 && l_idx < bins) {
                l_hist[l_idx]++;
            }
        }
    }
}

Mat drawHistogram(vector<int>& hist, int width = 500, int height = 300,
    Scalar color = Scalar(255, 0, 0)) {
    int bins = hist.size();
    if (hist.empty()) {
        return Mat(height, width, CV_8UC3, Scalar(255, 255, 255));
    }
    int binWidth = cvRound((double)width / bins);

    auto max_it = max_element(hist.begin(), hist.end());
    if (max_it == hist.end()) {
        return Mat(height, width, CV_8UC3, Scalar(255, 255, 255));
    }
    int maxVal = *max_it;

    Mat image(height, width, CV_8UC3, Scalar(255, 255, 255));

    for (int i = 0; i < bins; i++) {
        int binHeight = cvRound((double)hist[i] / maxVal * height);
        rectangle(image, Point(i * binWidth, height - binHeight),
            Point((i + 1) * binWidth, height), color, FILLED);
    }

    return image;
}

int main() {
    Mat image = imread("D:\\hw10_3\\photo1.png");

    if (image.empty()) {
        cout << "Ошибка: Не удалось загрузить изображение." << endl;
        return 1;
    }

    int bins = 100;

    vector<int> h_hist(bins, 0);
    vector<int> s_hist(bins, 0);
    vector<int> l_hist(bins, 0);

    calculateHistogram(image, h_hist, s_hist, l_hist, bins);

    Mat h_image = drawHistogram(h_hist);
    Mat s_image = drawHistogram(s_hist);
    Mat l_image = drawHistogram(l_hist);

    imwrite("D:\\hw10_3\\h_1.png", h_image);
    imwrite("D:\\hw10_3\\s_1.png", s_image);
    imwrite("D:\\hw10_3\\l_1.png", l_image);

    return 0;
}
