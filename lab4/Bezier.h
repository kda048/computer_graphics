#pragma once

int N(Point p0, Point p1, Point p2, Point p3);
Point Bezier(Point p0, Point p1, Point p2, Point p3, double t);
void Curve(Mat& image, Point p0, Point p1, Point p2, Point p3, string color);