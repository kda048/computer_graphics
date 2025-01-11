#include "pixel.h"
#include "draw_line.h"
#include "task4.h"
#include "Bezier.h"

void rotationAroundVector(Mat& image, vector <Point3d>& vertex, string color, Point3d vec, double phi)
{
	double norma = sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
	Point3d normalVec(vec.x / norma, vec.y / norma, vec.z / norma);

	double data_around[] = { cos(phi) + pow(normalVec.x, 2) * (1 - cos(phi)), normalVec.x * normalVec.y * (1 - cos(phi)) + normalVec.z * sin(phi), normalVec.x * normalVec.z * (1 - cos(phi)) - normalVec.y * sin(phi), 0, normalVec.x * normalVec.y * (1 - cos(phi)) - normalVec.z * sin(phi), cos(phi) + pow(normalVec.y, 2) * (1 - cos(phi)), normalVec.y * normalVec.z * (1 - cos(phi)) + normalVec.x * sin(phi), 0, normalVec.x * normalVec.z * (1 - cos(phi)) + normalVec.y * sin(phi), normalVec.y * normalVec.z * (1 - cos(phi)) - normalVec.x * sin(phi), cos(phi) + pow(normalVec.z, 2) * (1 - cos(phi)), 0, 0, 0, 0, 1 };
	Mat T = Mat(4, 4, CV_64F, data_around);

	vector <Point2d> newVertex2;
	for (int i = 0; i < vertex.size(); i++)
	{
		double vert4[] = { vertex[i].x, vertex[i].y, vertex[i].z, 1 };
		Mat oldPoint = Mat(1, 4, CV_64F, vert4);
		Mat newPoint = oldPoint * T;
		Point2d point(newPoint.at<double>(0) / newPoint.at<double>(3), newPoint.at<double>(1) / newPoint.at<double>(3));
		newVertex2.push_back(point);
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
}

void rotationAroundVectorAndPerspective(Mat& image, vector <Point3d>& vertex, string color, Point3d vec, double phi, double p, double r)
{
	double norma = sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
	Point3d normalVec(vec.x / norma, vec.y / norma, vec.z / norma);

	double data_around[] = { cos(phi) + pow(normalVec.x, 2) * (1 - cos(phi)), normalVec.x * normalVec.y * (1 - cos(phi)) + normalVec.z * sin(phi), normalVec.x * normalVec.z * (1 - cos(phi)) - normalVec.y * sin(phi), 0, normalVec.x * normalVec.y * (1 - cos(phi)) - normalVec.z * sin(phi), cos(phi) + pow(normalVec.y, 2) * (1 - cos(phi)), normalVec.y * normalVec.z * (1 - cos(phi)) + normalVec.x * sin(phi), 0, normalVec.x * normalVec.z * (1 - cos(phi)) + normalVec.y * sin(phi), normalVec.y * normalVec.z * (1 - cos(phi)) - normalVec.x * sin(phi), cos(phi) + pow(normalVec.z, 2) * (1 - cos(phi)), 0, 0, 0, 0, 1 };
	Mat T = Mat(4, 4, CV_64F, data_around);

	double data_perspective[] = { 1, 0, 0, 1 / p, 0, 1, 0, 0, 0, 0, 0, 1 / r, 0, 0, 0, 1 };
	Mat perspective = Mat(4, 4, CV_64F, data_perspective);

	vector <Point2d> newVertex2;
	for (int i = 0; i < vertex.size(); i++)
	{
		double vert4[] = { vertex[i].x, vertex[i].y, vertex[i].z, 1 };
		Mat oldPoint = Mat(1, 4, CV_64F, vert4);
		Mat newPoint = oldPoint * T * perspective;
		Point2d point(newPoint.at<double>(0) / newPoint.at<double>(3), newPoint.at<double>(1) / newPoint.at<double>(3));
		newVertex2.push_back(point);
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
}

void videoWriter(vector <Point3d>& vertex, string color, Point3d vec)
{
	Mat img_task4(800, 800, CV_8UC3, Scalar(255, 255, 255));
	VideoWriter videoTorsion("task4.avi", VideoWriter::fourcc('D', 'I', 'V', 'X'), 30, Size(800, 800));
	double phi = 0;
	int count = 600;

	while (count > 0)
	{
		img_task4.setTo(Scalar(255, 255, 255));
		rotationAroundVector(img_task4, vertex, color, vec, phi);
		videoTorsion.write(img_task4);
		phi = phi + 0.02;
		count = count - 1;
	}
	videoTorsion.release();
}

void videoWriterAndPerspective(vector <Point3d>& vertex, string color, Point3d vec, double p, double r)
{
	Mat img_task4(800, 800, CV_8UC3, Scalar(255, 255, 255));
	VideoWriter videoTorsion("task4_perspective.avi", VideoWriter::fourcc('D', 'I', 'V', 'X'), 30, Size(800, 800));
	double phi = 0;
	int count = 600;

	while (count > 0)
	{
		img_task4.setTo(Scalar(255, 255, 255));
		rotationAroundVectorAndPerspective(img_task4, vertex, color, vec, phi, p, r);
		videoTorsion.write(img_task4);
		phi = phi + 0.02;
		count = count - 1;
	}
	videoTorsion.release();
}

void videoWriterBezier(vector <Point3d>& vertex, string color, Point3d p0, Point3d p1, Point3d p2, Point3d p3)
{
	vector<Point3d> pointBezier = Curve(p0, p1, p2, p3, color);
	Mat img_task4(800, 800, CV_8UC3, Scalar(255, 255, 255));
	VideoWriter videoTorsion("task4_Bezier.avi", VideoWriter::fourcc('D', 'I', 'V', 'X'), 30, Size(800, 800));
	double phi = 0;
	Point3d vec = pointBezier[0];
	int i = 0;
	int k = 1;
	while (i < pointBezier.size())
	{
		vec = pointBezier[i];
		img_task4.setTo(Scalar(255, 255, 255));
		rotationAroundVector(img_task4, vertex, color, vec, phi);
		videoTorsion.write(img_task4);
		phi = phi + 0.02;
		if (k % 10 == 0)
		{
			i = i + 1;
		}
		k = k + 1;
	}
	videoTorsion.release();
}