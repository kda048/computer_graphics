#include "pixel.h"
#include "draw_line.h"
#include "Bezier.h"

int N(Point p0, Point p1, Point p2, Point p3)
{
	double dist1 = abs(p0.x - 2 * p1.x + p2.x) + abs(p0.y - 2 * p1.y + p2.y);
	double dist2 = abs(p1.x - 2 * p2.x + p3.x) + abs(p1.y - 2 * p2.y + p3.y);
	double H = max(dist1, dist2);
	int n = 1 + static_cast<int>(ceil(sqrt(3 * H)));
	return n;
}

Point Bezier(Point p0, Point p1, Point p2, Point p3, double t)
{
	Point p = pow(1 - t, 3) * p0 + 3 * pow(1 - t, 2) * t * p1 + 3 * pow(t, 2) * (1 - t) * p2 + pow(t, 3) * p3;
	return p;
}

void Curve(Mat& image, Point p0, Point p1, Point p2, Point p3, string color)
{
	int n = N(p0, p1, p2, p3);

	string color_point = "#C0C0C0";
	drawLine(image, p0, p1, color_point);
	drawLine(image, p1, p2, color_point);
	drawLine(image, p2, p3, color_point);

	for (int i = 1; i <= n; i++)
	{
		drawLine(image, Bezier(p0, p1, p2, p3, static_cast<double>(i - 1) / n), Bezier(p0, p1, p2, p3, static_cast<double>(i) / n), color);
	}
}