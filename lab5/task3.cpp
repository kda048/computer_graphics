#include "pixel.h"
#include "draw_line.h"
#include "task3.h"


Point3d vectorCoordinates(Point3d v1, Point3d v2)
{
    Point3d result(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
    return result;
}

Point3d vectorCrossProduct(Point3d v1, Point3d v2)
{
    Point3d result(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
    return result;
}

double vectorDotProduct(Point3d v1, Point3d v2)
{
    double result = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    return result;
}

void drawFisibalLine(Mat& image, vector<Point3d>& vertex, string color)
{
    vector<vector<int>> faces = {
            {0, 1, 2, 3},
            {4, 7, 6, 5},
            {4, 0, 3, 7},
            {1, 5, 6, 2},
            {4, 5, 1, 0},
            {3, 2, 6, 7},
    };
    for (int i = 0; i < 6; i++)
    {
        Point3d coordinatesFirst = vectorCoordinates(vertex[faces[i][1]], vertex[faces[i][0]]);
        Point3d coordinatesSecond = vectorCoordinates(vertex[faces[i][2]], vertex[faces[i][0]]);
        Point3d coordinatesVector = vectorCrossProduct(coordinatesFirst, coordinatesSecond);
        if (coordinatesVector.z > 0)
        {
            for (int j = 0; j < 4; j++)
            {
                Point2d pointdraw1(vertex[faces[i][j % 4]].x, vertex[faces[i][j % 4]].y);
                Point2d pointdraw2(vertex[faces[i][(j + 1) % 4]].x, vertex[faces[i][(j + 1) % 4]].y);
                drawLine(image, pointdraw1, pointdraw2, color);
            }
        }
    }
}