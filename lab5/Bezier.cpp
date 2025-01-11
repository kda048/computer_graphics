#include "pixel.h"
#include "draw_line.h"
#include "Bezier.h"

int N(Point3d p0, Point3d p1, Point3d p2, Point3d p3)
{
	double dist1 = abs(p0.x - 2 * p1.x + p2.x) + abs(p0.y - 2 * p1.y + p2.y) + abs(p0.z - 2 * p1.z + p2.z);
	double dist2 = abs(p1.x - 2 * p2.x + p3.x) + abs(p1.y - 2 * p2.y + p3.y) + abs(p1.z - 2 * p2.z + p3.z);
	double H = max(dist1, dist2);
	int n = 1 + static_cast<int>(ceil(sqrt(3 * H)));
	return n;
}

Point3d Bezier(Point3d p0, Point3d p1, Point3d p2, Point3d p3, double t)
{
	Point3d p = pow(1 - t, 3) * p0 + 3 * pow(1 - t, 2) * t * p1 + 3 * pow(t, 2) * (1 - t) * p2 + pow(t, 3) * p3;
	return p;
}

vector<Point3d> Curve(Point3d p0, Point3d p1, Point3d p2, Point3d p3, string color)
{
	vector<Point3d> pointBezier;
	int n = N(p0, p1, p2, p3);

	string color_point = "#C0C0C0";

	for (int i = 0; i <= n; i++)
	{
		Point3d newPoint = Bezier(p0, p1, p2, p3, static_cast<double>(i - 1) / n);
		pointBezier.push_back(newPoint);
	}
	return pointBezier;
}