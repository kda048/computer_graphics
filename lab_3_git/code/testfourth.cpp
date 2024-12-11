#include "pixel.h"
#include "taskfirst.h"
#include "tasksecond.h"
#include "taskthird.h"
#include "taskfourth.h"

int test4()
{
    Mat img4f(512, 512, CV_8UC3, Scalar(255, 255, 255));
    vector<Point> vertex = { Point(220, 80), Point(490, 80), Point(100, 490), Point(480, 490), Point(100, 120), Point(300, 120), Point(200, 350), Point(460, 350) };
    if (vertex.size() == 0)
    {
        printf("\nVector is empty");
        return -1;
    }
    for (int i = 0; i < vertex.size(); i++)
    {
        if (vertex[i].x < 0 || vertex[i].y < 0 || vertex[i].x >= img4f.cols || vertex[i].y >= img4f.rows)
        {
            printf("\nPixel number is outside the image boundaries");
            return -1;
        }
    }
    string color = "#FF00FF";
    EvenOdd(img4f, vertex, color);
    imwrite("task4_EO.png", img4f);


    Mat img4s(512, 512, CV_8UC3, Scalar(255, 255, 255));
    if (vertex.size() == 0)
    {
        printf("\nVector is empty");
        return -1;
    }
    for (int i = 0; i < vertex.size(); i++)
    {
        if (vertex[i].x < 0 || vertex[i].y < 0 || vertex[i].x >= img4s.cols || vertex[i].y >= img4s.rows)
        {
            printf("\nPixel number is outside the image boundaries");
            return -1;
        }
    }
    NonZeroWinding(img4s, vertex, color);
    imwrite("task4_NZW.png", img4s);

    return 0;
}