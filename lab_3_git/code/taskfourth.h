#pragma once

bool isNonZeroWinding(vector<Point> vertex, Point point);
bool isEvenOdd(vector<Point> vertex, Point point);
void EvenOdd(Mat& image, vector<Point> vertex, string color);
void NonZeroWinding(Mat& image, vector<Point> vertex, string color);