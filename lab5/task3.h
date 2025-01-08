#pragma once

Point3d vectorCoordinates(Point3d v1, Point3d v2);
Point3d vectorCrossProduct(Point3d v1, Point3d v2);
double vectorDotProduct(Point3d v1, Point3d v2);
void drawFisibalLine(Mat& image, vector<Point3d>& vertex, string color);