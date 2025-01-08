#include "pixel.h"
#include "Convex.h"

int intersect(Point a, Point b, Point c, Point d)
{
    double val = (a.x - b.x) * (c.y - d.y) - (a.y - b.y) * (c.x - d.x);
    if (val == 0)
    {
        return 0;
    }
    else
    {
        double u = -((a.x - b.x) * (a.y - c.y) - (a.y - b.y) * (a.x - c.x)) / val;
        double t = ((a.x - c.x) * (c.y - d.y) - (a.y - c.y) * (c.x - d.x)) / val;
        if ((u >= 0 && u <= 1) && (t >= 0 && t <= 1))
        {
            return 1;
        }
    }
    return 0;
}

bool isIntersect(vector<Point> vertex)
{
    vector<Point> vertex_exam = vertex;
    vertex_exam.push_back(vertex[0]);
    for (int j = 2; j < vertex_exam.size() - 2; j++)
    {
        if (intersect(vertex_exam[1], vertex_exam[1], vertex_exam[j], vertex_exam[j + 1]) == 1)
        {
            cout << 1 << endl;
            cout << vertex_exam[0] << vertex_exam[1] << vertex_exam[j] << vertex_exam[j + 1] << endl;
            return true;
        }
    }
    for (int i = 1; i < vertex_exam.size() - 3; i++)
    {
        for (int j = i + 2; j < vertex_exam.size() - 1; j++)
        {
            if (intersect(vertex_exam[i], vertex_exam[i + 1], vertex_exam[j], vertex_exam[j + 1]) == 1)
            {
                cout << 1 << endl;
                cout << vertex_exam[i] << vertex_exam[i + 1] << vertex_exam[j] << vertex_exam[j + 1] << endl;
                return true;
            }
        }
    }
    return false;
}


double crossProduct(Point p1, Point p2, Point p3)
{
    return (p2.x - p1.x) * (p3.y - p2.y) - (p2.y - p1.y) * (p3.x - p2.x);
}

bool isConvex(vector<Point>& vertex)
{
    int n = vertex.size();
    if (vertex.size() < 3 || isIntersect(vertex) == true)
    {
        return false;
    }

    double prevCrossProduct = 0;
    bool isPositive = false;

    for (int i = 0; i < vertex.size(); i++)
    {
        Point p1 = vertex[i];
        Point p2 = vertex[(i + 1) % vertex.size()];
        Point p3 = vertex[(i + 2) % vertex.size()];

        double crossProductValue = crossProduct(p1, p2, p3);

        if (i == 0)
        {
            prevCrossProduct = crossProductValue;
        }
        else
        {
            if ((crossProductValue > 0 && prevCrossProduct < 0) || (crossProductValue < 0 && prevCrossProduct > 0))
            {
                return false;
            }
        }
    }

    return true;
}