#include "pixel.h"
#include "taskfirst.h"

int test1()
{
    Mat img(512, 512, CV_8UC3, Scalar(255, 255, 255));
    Point start1(50, 50);
    Point end1(450, 450);
    if (start1.x < 0 || start1.x >= img.cols || start1.y < 0 || start1.y >= img.rows || end1.x < 0 || end1.x >= img.cols || end1.y < 0 || end1.y >= img.rows)
    {
        printf("\nPixel number is outside the image boundaries");
        return -1;
    }
    string color1 = "#FF00FF";
    Point start2(450, 50);
    Point end2(50, 450);
    if (start2.x < 0 || start2.x >= img.cols || start2.y < 0 || start2.x >= img.rows || end2.x < 0 || end2.x >= img.cols || end2.y < 0 || end2.y >= img.rows)
    {
        printf("\nPixel number is outside the image boundaries");
        return -1;
    }
    string color2 = "#00FF00";
    drawLine(img, start1, end1, color1);
    drawLine(img, start2, end2, color2);
    imwrite("task1.png", img);
    return 0;
}