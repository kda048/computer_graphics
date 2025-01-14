#include "pixel.h"
#include "draw_line.h"
#include "task1.h"
#include "task2.h"
#include "task3.h"
#include "task4.h"

int main()
{
    vector<Point3d> vertex = { Point3d(348, 164, 348), Point3d(348, 348, 348), Point3d(348, 348, 164), Point3d(348, 164, 164), Point3d(164, 164, 348), Point3d(164, 348, 348), Point3d(164, 348, 164), Point3d(164, 164, 164) };
    string color = "#1E90FF";

    //task1   

    Mat img_task1_ort(800, 800, CV_8UC3, Scalar(255, 255, 255));
    vector<Point3d> newPoints_ort;
    newPoints_ort = ortografProjection(img_task1_ort, vertex, color);
    imwrite("task1_ortograf.png", img_task1_ort);

    Mat img_task1_izom(800, 800, CV_8UC3, Scalar(255, 255, 255));
    vector<Point3d> newPoints_izom;
    double phi_1 = M_PI / 4;
    double teta_1 = M_PI * 35.26 / 180;
    newPoints_izom = axonometricProjection(img_task1_izom, vertex, color, phi_1, teta_1);
    imwrite("task1_izometric.png", img_task1_izom);

    Mat img_task1_dia(800, 800, CV_8UC3, Scalar(255, 255, 255));
    vector<Point3d> newPoints_dia;
    double phi_2 = M_PI / 2;
    double teta_2 = M_PI / 4;
    newPoints_dia = axonometricProjection(img_task1_dia, vertex, color, phi_2, teta_2);
    imwrite("task1_diametric.png", img_task1_dia);

    Mat img_task1_obl(800, 800, CV_8UC3, Scalar(255, 255, 255));
    vector<Point3d> newPoints_obl;
    double h = cos(M_PI / 4);
    double i = cos(M_PI / 4);
    newPoints_obl = obliqueProjection(img_task1_obl, vertex, color, h, i);
    imwrite("task1_oblique.png", img_task1_obl);

    //task2

    Mat img_task2_perspective(800, 800, CV_8UC3, Scalar(255, 255, 255));
    double k = 500;
    vector<Point3d> newPoints_perspective;
    newPoints_perspective = singlePointPerspectiveProjection(img_task2_perspective, vertex, color, k);
    imwrite("task2_perspective.png", img_task2_perspective);

    //task3

    Mat img_task3_ort(800, 800, CV_8UC3, Scalar(255, 255, 255));
    drawFisibalLine(img_task3_ort, newPoints_ort, color);
    imwrite("task3_ortograf_visible.png", img_task3_ort);

    Mat img_task3_izom(800, 800, CV_8UC3, Scalar(255, 255, 255));
    drawFisibalLine(img_task3_izom, newPoints_izom, color);
    imwrite("task3_izometric_visible.png", img_task3_izom);

    Mat img_task3_dia(800, 800, CV_8UC3, Scalar(255, 255, 255));
    drawFisibalLine(img_task3_dia, newPoints_dia, color);
    imwrite("task3_diametric_visible.png", img_task3_dia);

    Mat img_task3_obl(800, 800, CV_8UC3, Scalar(255, 255, 255));
    drawFisibalLine(img_task3_obl, newPoints_obl, color);
    imwrite("task3_oblique_visible.png", img_task3_obl);

    Mat img_task3_perspective(800, 800, CV_8UC3, Scalar(255, 255, 255));
    drawFisibalLine(img_task3_perspective, newPoints_perspective, color);
    imwrite("task3_perspective_visible.png", img_task3_perspective);

    //task 4
    Point3d vec(1, 1, 1);
    videoWriter(vertex, color, vec);

    Point3d p0(145, 391, 256);
    Point3d p1(54, 125, 457);
    Point3d p2(450, 99, 44);
    Point3d p3(314, 391, 191);
    videoWriterBezier(vertex, color, p0, p1, p2, p3);

    

    return 0;
}
