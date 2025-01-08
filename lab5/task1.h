#pragma once

vector<Point3d> ortografProjection(Mat& image, vector <Point3d>& vertex, string color);
vector<Point3d> axonometricProjection(Mat& image, vector <Point3d>& vertex, string color, double phi, double teta);
vector<Point3d> obliqueProjection(Mat& image, vector <Point3d>& vertex, string color, double h, double i);