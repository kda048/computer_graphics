#include "pixel.h"

void hexToRgb(const string& color, int& r, int& g, int& b)
{

    string hex = color;
    if (hex[0] == '#')
    {
        hex = hex.substr(1);
    }
    r = std::stoi(hex.substr(0, 2), nullptr, 16);
    g = std::stoi(hex.substr(2, 2), nullptr, 16);
    b = std::stoi(hex.substr(4, 2), nullptr, 16);
}

void outputPixel(Mat& img, int x, int y, string& color)
{
    int r, g, b;
    hexToRgb(color, r, g, b);
    if (x >= 0 && y >= 0 && x < img.cols && y < img.rows)
    {
        img.at<Vec3b>(y, x) = Vec3b(r, g, b);
    }

}