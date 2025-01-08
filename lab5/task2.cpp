#include "pixel.h"
#include "draw_line.h"
#include "task2.h"

vector<Point3d> singlePointPerspectiveProjection(Mat& image, vector <Point3d>& vertex, string color, double k)
{
	double data_perspective[] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 / k, 0, 0, 0, 1 };
	Mat perspective = Mat(4, 4, CV_64F, data_perspective);
	vector <Point2d> newVertex2;
	vector <Point3d> newVertex3;
	for (int i = 0; i < vertex.size(); i++)
	{
		double vert4[] = { vertex[i].x, vertex[i].y, vertex[i].z, 1 };
		Mat oldPoint = Mat(1, 4, CV_64F, vert4);
		Mat newPoint = oldPoint * perspective;
		Point2d point(newPoint.at<double>(0) / newPoint.at<double>(3), newPoint.at<double>(1) / newPoint.at<double>(3));
		Point3d point3D(newPoint.at<double>(0) / newPoint.at<double>(3), newPoint.at<double>(1) / newPoint.at<double>(3), newPoint.at<double>(2) / newPoint.at<double>(3));
		newVertex2.push_back(point);
		newVertex3.push_back(point3D);
	}
	for (int i = 0; i < 4; i++)
	{
		drawLine(image, newVertex2[i % 4], newVertex2[(i + 1) % 4], color);
	}
	for (int i = 4; i < newVertex2.size() - 1; i++)
	{
		drawLine(image, newVertex2[i], newVertex2[i + 1], color);
	}
	drawLine(image, newVertex2[4], newVertex2[7], color);
	drawLine(image, newVertex2[0], newVertex2[4], color);
	drawLine(image, newVertex2[1], newVertex2[5], color);
	drawLine(image, newVertex2[2], newVertex2[6], color);
	drawLine(image, newVertex2[3], newVertex2[7], color);
	return newVertex3;
}