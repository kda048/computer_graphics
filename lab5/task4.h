#pragma once

void rotationAroundVector(Mat& image, vector <Point3d>& vertex, string color, Point3d vec, double phi);
void rotationAroundVectorAndPerspective(Mat& image, vector <Point3d>& vertex, string color, Point3d vec, double phi, double p, double r);
void videoWriter(vector <Point3d>& vertex, string color, Point3d vec);
void videoWriterAndPerspective(vector <Point3d>& vertex, string color, Point3d vec, double p, double r);
