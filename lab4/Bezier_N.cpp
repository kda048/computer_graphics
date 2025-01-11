#include "pixel.h"
#include "draw_line.h"
#include "Bezier_N.h"

int N_(vector <Point> vertex, int N_Bezier)
{
	double dist1 = abs(vertex[0].x - 2 * vertex[1].x + vertex[2].x) + abs(vertex[0].y - 2 * vertex[1].y + vertex[3].y);
	for (int i = 1; i < vertex.size() - 2; i++)
	{
		double dist2 = abs(vertex[i].x - 2 * vertex[i + 1].x + vertex[i + 2].x) + abs(vertex[i].y - 2 * vertex[i + 1].y + vertex[i + 2].y);
		dist1 = max(dist1, dist2);
	}
	double H = dist1;
	int n = 1 + static_cast<int>(ceil(sqrt(N_Bezier * H)));
	return n;
}

int factorial(int m)
{
	int res = 1;
	for (int j = 1; j <= m; j++)
	{
		res = res * j;
	}
	return res;
}

Point Bezier_(vector <Point> vertex, double t, int N_Bezier)
{
	Point p = { 0, 0 };
	for (int i = 0; i <= N_Bezier; i++)
	{
		p = p + vertex[i] * factorial(N_Bezier) * pow(t, i) * pow(1 - t, N_Bezier - i) / (factorial(i) * factorial(N_Bezier - i));
	}
	return p;
}

void Curve_N(Mat& image, vector <Point> vertex, int N_Bezier, string color)
{
	int n = N_(vertex, N_Bezier);

	string color_point = "#C0C0C0";
	for (int i = 0; i < vertex.size() - 1; i++)
	{
		drawLine(image, vertex[i], vertex[i + 1], color_point);
	}

	for (int i = 1; i <= n; i++)
	{
		drawLine(image, Bezier_(vertex, static_cast<double>(i - 1) / n, N_Bezier), Bezier_(vertex, static_cast<double>(i) / n, N_Bezier), color);
	}
}