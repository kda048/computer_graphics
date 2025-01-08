#include "pixel.h"
#include "Cyrus_Beck.h"
#include "Convex.h"
#include "draw_line.h"
#include "draw_polygon.h"

CLPointType Classify(Point& p1, Point& p2, Point& p)
{
	Point a = p2 - p1;
	Point b = p - p1;
	double s = a.x * b.y - b.x * a.y;
	if (s > 0)
	{
		return LEFT;
	}
	if (s < 0)
	{
		return RIGHT;
	}
	if ((a.x * b.x < 0) || (a.y * b.y < 0))
	{
		return BEHIND;
	}
	if ((a.x * a.x + a.y * a.y) < (b.x * b.x + b.y * b.y))
	{
		return BEHIND;
	}
	if (p1.x == p.x && p1.y == p.y)
	{
		return ORIGIN;
	}
	if (p2.x == p.x && p2.y == p.y)
	{
		return DESTINATION;
	}
	return BETWEEN;
}

bool isClockwise(vector<Point>& vertex)
{
	double areaAll = 0;
	for (int i = 0; i < vertex.size(); i++)
	{
		int j = (i + 1) % vertex.size(); 
		areaAll += (vertex[j].x - vertex[i].x) * (vertex[j].y + vertex[i].y);
	}
	return (areaAll > 0) ? true : (areaAll < 0) ? false : true;
}

void reversePolygon(vector<Point>& polygon)
{
	reverse(polygon.begin(), polygon.end());
}

vector <Point> CyrusBeckClipLine(Point& p1, Point& p2, vector <Point>& vertex)
{
	vector <Point> point_new;
	if (isConvex(vertex) == false)
	{
		cout << "The algorithm does not work because the rectangle is not convex." << endl;
		Point point_ = { 0, 0 };
		point_new.push_back(point_);
		return point_new;
	}
	if (isClockwise(vertex) == false)
	{
		reversePolygon(vertex);
	}
	double t1 = 0, t2 = 1, t;
	Point s = p2 - p1;
	double nx, ny, denom, num;
	Point p1_new, p2_new;
	for (int i = 0; i < vertex.size(); i++)
	{
		nx = vertex[(i + 1) % vertex.size()].y - vertex[i].y;
		ny = vertex[i].x - vertex[(i + 1) % vertex.size()].x;
		denom = nx * s.x + ny * s.y;
		num = nx * (p1.x - vertex[i].x) + ny * (p1.y - vertex[i].y);

		if (denom != 0)
		{
			t = -num / denom;
			if (denom > 0)
			{
				if (t > t1)
				{
					t1 = t;
				}
			}
			else
			{
				if (t < t2)
				{
					t2 = t;
				}
			}

		}
		else
		{
			if (Classify(vertex[i], vertex[(i + 1) % vertex.size()], p1) == LEFT)
			{
				return point_new;
			}
		} 
	}
	if (t1 <= t2)
	{ 
		p1_new = p1 + t1 * (p2 - p1);
		p2_new = p1 + t2 * (p2 - p1);
		point_new.push_back(p1_new);
		point_new.push_back(p2_new);
		p1 = p1_new;
		p2 = p2_new;
		return point_new;
	}
	return point_new;
}

void CuttingOff(Mat& image, Point& p1, Point& p2, vector <Point>& vertex, string color)
{
	drawPolygon(image, vertex, color);
	drawLine(image, p1, p2, color);
	vector <Point> point_new;
	point_new = CyrusBeckClipLine(p1, p2, vertex);
	if (point_new.size() == 0)
	{
		cout << "Segment outside the polygon" << endl;
	}
	else
	{
		if (point_new.size() == 1)
		{
			cout << "The polygon is not convex" << endl;
		}
		else
		{
			drawLine(image, point_new[0], point_new[1], "#000000");
		}
	}

}