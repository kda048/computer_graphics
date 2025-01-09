#include "pixel.h"
#include "draw_line.h"
#include "draw_polygon.h"

void drawPolygon(Mat& image, vector<Point> vertex, string color)
{
	if (vertex.size() > 0)
	{
		if (vertex.size() == 1)
		{
			drawLine(image, vertex[0], vertex[0], color);
		}
		if (vertex.size() == 2)
		{
			drawLine(image, vertex[0], vertex[1], color);
		}
		if (vertex.size() > 2)
		{
			for (int i = 0; i < vertex.size() - 1; i++)
			{
				drawLine(image, vertex[i], vertex[i + 1], color);
			}
			drawLine(image, vertex[0], vertex[vertex.size() - 1], color);
		}
	}
	else
	{
		printf("\nVector is empty");
	}
}

vector<Point> calculateStarVertices(Mat& image, double radiusf, double radiuss, int number)
{
	vector<Point> vertex;
	double step = M_PI / number;
	int centre_x = image.cols / 2 - 1;
	int centre_y = image.rows / 2 - 1;
	for (int i = 0; i < 2 * number; i++) {
		double angle = i * step;
		int x;
		int y;
		if (!(i & 1))
		{
			x = centre_x + floor(radiusf * cos(angle));
			y = centre_y + floor(radiusf * sin(angle));
		}
		else
		{
			x = centre_x + floor(radiuss * cos(angle));
			y = centre_y + floor(radiuss * sin(angle));
		}

		vertex.push_back(Point(x, y));
	}

	return vertex;
}