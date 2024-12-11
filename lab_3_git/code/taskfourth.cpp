#include "pixel.h"
#include "taskfirst.h"
#include "tasksecond.h"
#include "taskthird.h"
#include "taskfourth.h"

using namespace std;


bool isEvenOdd(vector<Point> vertex, Point point)
{
    int crossings = 0;
    for (int i = 0; i < vertex.size(); i++)
    {
        if ((vertex[i].y > point.y) != (vertex[(i + 1) % vertex.size()].y > point.y))
        {
            if (point.x < (double)(vertex[(i + 1) % vertex.size()].x - vertex[i].x) * (point.y - vertex[i].y) /
                (vertex[(i + 1) % vertex.size()].y - vertex[i].y) + vertex[i].x)
            {
                crossings = crossings + 1;
            }
        }
    }
    if (crossings & 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool isNonZeroWinding(vector<Point> vertex, Point point)
{
    int windingNumber = 0;
    for (int i = 0; i < vertex.size(); ++i)
    {
        if (vertex[i].y <= point.y && vertex[(i + 1) % vertex.size()].y > point.y && (vertex[(i + 1) % vertex.size()].x - vertex[i].x) * (point.y - vertex[i].y) - (vertex[(i + 1) % vertex.size()].y - vertex[i].y) * (point.x - vertex[i].x) > 0)
        {
            windingNumber = windingNumber + 1;
        }
        if (vertex[i].y > point.y && vertex[(i + 1) % vertex.size()].y <= point.y && (vertex[(i + 1) % vertex.size()].x - vertex[i].x) * (point.y - vertex[i].y) - (vertex[(i + 1) % vertex.size()].y - vertex[i].y) * (point.x - vertex[i].x) < 0)
        {
            windingNumber = windingNumber - 1;
        }
    }
    if (windingNumber != 0 == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void EvenOdd(Mat& image, vector<Point> vertex, string color)
{
    if (vertex.size() > 0)
    {
        if (vertex.size() == 1)
        {
            drawLine(image, vertex[0], vertex[0], color);
        }
        if (vertex.size() == 2)
        {
            drawLine(image, vertex[0], vertex[1], color);
        }
        if (vertex.size() > 2)
        {
            drawPolygon(image, vertex, color);
            for (int y = 0; y < image.rows; y++)
            {
                for (int x = 0; x < image.cols; x++)
                {
                    Point p = Point{ x, y };
                    if (isEvenOdd(vertex, p) == true)
                    {
                        outputPixel(image, x, y, color);
                    }
                }
            }
        }
    }
    else
    {
        printf("\nVector is empty");
    }
}

void NonZeroWinding(Mat& image, vector<Point> vertex, string color)
{
    if (vertex.size() > 0)
    {
        if (vertex.size() == 1)
        {
            drawLine(image, vertex[0], vertex[0], color);
        }
        if (vertex.size() == 2)
        {
            drawLine(image, vertex[0], vertex[1], color);
        }
        if (vertex.size() > 2)
        {
            drawPolygon(image, vertex, color);
            for (int y = 0; y < image.rows; y++)
            {
                for (int x = 0; x < image.cols; x++)
                {
                    Point p = Point{ x, y };
                    if (isNonZeroWinding(vertex, p) == true)
                    {
                        outputPixel(image, x, y, color);
                    }
                }
            }
        }
    }
    else
    {
        printf("\nVector is empty");
    }
}