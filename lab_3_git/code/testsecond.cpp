#include "pixel.h"
#include "taskfirst.h"
#include "tasksecond.h"

int test2()
{
    Mat imgf(512, 512, CV_8UC3, Scalar(255, 255, 255));
    vector<Point> vertex1 = { Point(36, 36), Point(476, 36), Point(476, 476), Point(36, 476) };
    if (vertex1.size() == 0)
    {
        printf("\nVector is empty");
        return -1;
    }
    for (int i = 0; i < vertex1.size(); i++)
    {
        if (vertex1[i].x < 0 || vertex1[i].y < 0 || vertex1[i].x >= imgf.cols || vertex1[i].y >= imgf.rows)
        {
            printf("\nPixel number is outside the image boundaries");
            return -1;
        }
    }
    string color1 = "#FF00FF";

    vector<Point> vertex2 = { Point(72, 64), Point(400, 380) };
    if (vertex2.size() == 0)
    {
        printf("\nVector is empty");
        return -1;
    }
    for (int i = 0; i < vertex2.size(); i++)
    {
        if (vertex2[i].x < 0 || vertex2[i].y < 0 || vertex2[i].x >= imgf.cols || vertex2[i].y >= imgf.rows)
        {
            printf("\nPixel number is outside the image boundaries");
            return -1;
        }
    }
    string color2 = "#20B2AA";

    vector<Point> vertex3 = { Point(100, 300) };
    if (vertex3.size() == 0)
    {
        printf("\nVector is empty");
        return -1;
    }
    for (int i = 0; i < vertex3.size(); i++)
    {
        if (vertex3[i].x < 0 || vertex3[i].y < 0 || vertex3[i].x >= imgf.cols || vertex3[i].y >= imgf.rows)
        {
            printf("\nPixel number is outside the image boundaries");
            return -1;
        }
    }
    string color3 = "#000000";

    vector<Point> vertex4 = { Point(320, 80), Point(320, 150), Point(450, 80), Point(450, 150) };
    if (vertex4.size() == 0)
    {
        printf("\nVector is empty");
        return -1;
    }
    for (int i = 0; i < vertex4.size(); i++)
    {
        if (vertex4[i].x < 0 || vertex4[i].y < 0 || vertex4[i].x >= imgf.cols || vertex4[i].y >= imgf.rows)
        {
            printf("\nPixel number is outside the image boundaries");
            return -1;
        }
    }
    string color4 = "#D2691E";

    drawPolygon(imgf, vertex1, color1);
    drawPolygon(imgf, vertex2, color2);
    drawPolygon(imgf, vertex3, color3);
    drawPolygon(imgf, vertex4, color4);
    imwrite("task2example1.png", imgf);


    Mat imgsecond(512, 512, CV_8UC3, Scalar(255, 255, 255));
    double radiusf = 150;
    double radiuss = 75;
    int number = 10;
    vector<Point> vertex5 = calculateStarVertices(imgsecond, radiusf, radiuss, number);
    if (vertex5.size() == 0)
    {
        printf("\nVector is empty");
        return -1;
    }
    for (int i = 0; i < vertex5.size(); i++)
    {
        if (vertex5[i].x < 0 || vertex5[i].y < 0 || vertex5[i].x >= imgsecond.cols || vertex5[i].y >= imgsecond.rows)
        {
            printf("\nPixel number is outside the image boundaries");
            return -1;
        }
    }
    string color5 = "#FF00FF";
    drawPolygon(imgsecond, vertex5, color5);
    imwrite("task2example2.png", imgsecond);
    return 0;
}