#pragma once

void rotationAroundVector(Mat& image, vector <Point3d>& vertex, string color, Point3d vec, double phi);
void rotationAroundVectorAndPerspective(Mat& image, vector <Point3d>& vertex, string color, Point3d vec, double phi, double p, double r);
void videoWriter(vector <Point3d>& vertex, string color, Point3d vec);
void videoWriterAndPerspective(vector <Point3d>& vertex, string color, Point3d vec, double p, double r);
void videoWriterBezier(vector <Point3d>& vertex, string color, Point3d p0, Point3d p1, Point3d p2, Point3d p3);