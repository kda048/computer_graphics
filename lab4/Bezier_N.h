#pragma once

int N_(vector <Point> vertex, int N_Bezier);
int factorial(int m);
Point Bezier_(vector <Point> vertex, double t, int N_Bezier);
void Curve_N(Mat& image, vector <Point> vertex, int N_Bezier, string color);