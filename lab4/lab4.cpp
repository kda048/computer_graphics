#include "pixel.h"
#include "draw_line.h"
#include "draw_polygon.h"
#include "Bezier.h"
#include "Convex.h"
#include "Cyrus_Beck.h"
int main()
{

    //task1
    Mat img_task1_first(512, 512, CV_8UC3, Scalar(255, 255, 255));
    Mat img_task1_second(512, 512, CV_8UC3, Scalar(255, 255, 255));
    Mat img_task1_third(512, 512, CV_8UC3, Scalar(255, 255, 255));
    Point p0(145, 391);
    Point p1(54, 125);
    Point p2(450, 99);
    Point p3(314, 391);
    string color = "#1E90FF";


    Curve(img_task1_first, p0, p1, p2, p3, color);
    imwrite("task1_bezier_first.png", img_task1_first);

    Curve(img_task1_second, p3, p1, p2, p0, color);
    imwrite("task1_bezier_second.png", img_task1_second);

    Curve(img_task1_third, p0, p1, p3, p2, color);
    imwrite("task1_bezier_third.png", img_task1_third);


    //task2

    Mat img_task2(512, 512, CV_8UC3, Scalar(255, 255, 255));
    vector<Point> vertex = { Point(133, 420), Point(40, 371), Point(84, 115), Point(310, 220), Point(440, 304), Point(440, 383) };
    Point P1(50, 400);
    Point P2(400, 50);

    Point P3(150, 300);
    Point P4(320, 280);

    Point P5(270, 40);
    Point P6(420, 80);

    Point P7(440, 383);
    Point P8(440, 304);

    Point P9(50, 135);
    Point P10(200, 50);

    CuttingOff(img_task2, P1, P2, vertex, color);
    CuttingOff(img_task2, P3, P4, vertex, color);
    CuttingOff(img_task2, P5, P6, vertex, color);
    CuttingOff(img_task2, P7, P8, vertex, color);
    CuttingOff(img_task2, P9, P10, vertex, color);

    imwrite("task2.png", img_task2);


    

    return 0;
}