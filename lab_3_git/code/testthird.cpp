#include "pixel.h"
#include "taskfirst.h"
#include "tasksecond.h"
#include "taskthird.h"

int test3()
{
    vector<Point> vertex6 = { Point(320, 80), Point(320, 150), Point(450, 80), Point(450, 150) };
    cout << "Bow - " << (isIntersect(vertex6) ? "Difficult" : "Simple") << endl;
    vector<Point> vertex7 = { Point(36, 36), Point(70, 36), Point(476, 36), Point(476, 476), Point(36, 476) };
    cout << "Square - " << (isIntersect(vertex7) ? "Difficult" : "Simple") << endl;
    vector<Point> vertex8 = { Point(1, 2), Point(3, 4), Point(1, 6), Point(4, 6), Point(5, 8), Point(6, 6), Point(6, 4) };
    cout << "Polygon - " << (isConvex(vertex8) ? "Convex" : "Not convex") << endl;
    return 0;
}