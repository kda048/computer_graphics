#include "pixel.h"
#include "task1.h"

bool isPointOnSegment(Point p, Point a, Point b)
{
    return (min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x)) &&
        (min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y)) &&
        ((b.x - a.x) * (p.y - a.y) == (b.y - a.y) * (p.x - a.x));
}

bool intersect(Point a, Point b, Point c, Point d)
{
    double val = (a.x - b.x) * (c.y - d.y) - (a.y - b.y) * (c.x - d.x);
    if (val == 0)
    {
        return false;
    }
    else
    {
        double u = -((a.x - b.x) * (a.y - c.y) - (a.y - b.y) * (a.x - c.x)) / val;
        double t = ((a.x - c.x) * (c.y - d.y) - (a.y - c.y) * (c.x - d.x)) / val;
        if ((u > 0 && u < 1) && (t > 0 && t < 1))
        {
            return true;
        }
    }

    if (isPointOnSegment(a, c, d) || isPointOnSegment(b, c, d) ||
        isPointOnSegment(c, a, b) || isPointOnSegment(d, a, b))
    {
        return false;
    }

    if ((a.x == c.x && a.y == c.y) || (a.x == d.x && a.y == d.y) ||
        (b.x == c.x && b.y == c.y) || (b.x == d.x && b.y == d.y))
    {
        return false;
    }

    return false;
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
            if (intersect(vertex_exam[i], vertex_exam[i + 1], vertex_exam[j], vertex_exam[j + 1]))
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

Point getIntersection(Point a, Point b, Point c, Point d)
{
    double a1 = b.y - a.y;
    double b1 = a.x - b.x;
    double c1 = a1 * a.x + b1 * a.y;

    double a2 = d.y - c.y;
    double b2 = c.x - d.x;
    double c2 = a2 * c.x + b2 * c.y;

    double det = a1 * b2 - a2 * b1;
    Point p(static_cast<int>((c1 * b2 - c2 * b1) / det), static_cast<int>((a1 * c2 - a2 * c1) / det));
    return p;
}

double distanse(Point p1, Point p2)
{
    return  (pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

int changeNumbervoit(int numbervoit, int n)
{
    if (numbervoit == 0)
    {
        return (n - 1);
    }
    return (numbervoit - 1);
}

vector<Point> slice(vector<Point>& v, int m, int n)
{
    vector<Point> vec(n - m + 1);
    copy(v.begin() + m, v.begin() + n + 1, vec.begin());
    return vec;
}

vector <Point> WeilerAthertonModification(vector<Point> vertexS, vector<Point> vertexC)
{
    vector <Point> result;
    if (isConvex(vertexS) == false || isConvex(vertexC) == false)
    {
        cout << "The algorithm does not work because the rectangle is not convex" << endl;
        return result;
    }
    if (isClockwise(vertexS) == false)
    {
        reversePolygon(vertexS);
    }
    if (isClockwise(vertexC) == false)
    {
        reversePolygon(vertexC);
    }
    vector<int> positionS;
    vector<int> positionC;
    vector<Point> intersectPoint;
    int count = 0;
    for (int i = 0; i < vertexS.size(); i++)
    {
        for (int j = 0; j < vertexC.size(); j++)
        {
            if (intersect(vertexS[i % vertexS.size()], vertexS[(i + 1) % vertexS.size()], vertexC[j % vertexC.size()], vertexC[(j + 1) % vertexC.size()]))
            {
                positionS.push_back(i);
                positionC.push_back(j);
                Point p = getIntersection(vertexS[i % vertexS.size()], vertexS[(i + 1) % vertexS.size()], vertexC[j % vertexC.size()], vertexC[(j + 1) % vertexC.size()]);
                intersectPoint.push_back(p);
                count = count + 1;
            }
        }
    }
    if (count == 0)
    {
        cout << "Polygons have no intersection points." << endl;
        return result;
    }
    int startposition = 0;
    int s_c = 0;
    vector<Point> startspoints;
    if (positionS[1] == positionS[0])
    {
        if (distanse(intersectPoint[0], vertexS[positionS[0]]) < distanse(intersectPoint[1], vertexS[positionS[1]]))
        {
            result.push_back(intersectPoint[0]);
            startposition = 0;
        }
        else
        {
            result.push_back(intersectPoint[1]);
            startposition = 1;
        }
    }
    else
    {
        result.push_back(intersectPoint[0]);
        startposition = 0;
    }
    result.push_back(vertexS[positionS[startposition]]);
    int currentposition = -1;
    int numbervoit = positionS[startposition];
    numbervoit = changeNumbervoit(numbervoit, vertexS.size());

    while (currentposition != startposition)
    {
        if (s_c == 0)
        {
            int count = 0;
            vector <Point> intPoint;
            vector <int> positionIntPoint;
            for (int i = 0; i < positionS.size(); i++)
            {
                if (positionS[i] == numbervoit)
                {
                    count = count + 1;
                    intPoint.push_back(intersectPoint[i]);
                    positionIntPoint.push_back(i);
                }
            }
            if (count == 0)
            {
                result.push_back(vertexS[numbervoit]);
                numbervoit = changeNumbervoit(numbervoit, vertexS.size());
            }
            if (count == 1)
            {
                result.push_back(intPoint[0]);
                currentposition = positionIntPoint[0];
                numbervoit = positionC[positionIntPoint[0]];
                result.push_back(vertexC[numbervoit]);
                numbervoit = changeNumbervoit(numbervoit, vertexC.size());
                s_c = 1;
            }
            if (count == 2)
            {
                if (distanse(intPoint[0], vertexS[numbervoit]) > distanse(intPoint[1], vertexS[numbervoit]))
                {
                    result.push_back(intPoint[0]);
                    currentposition = positionIntPoint[0];
                    numbervoit = positionC[positionIntPoint[0]];
                    result.push_back(vertexC[numbervoit]);
                    numbervoit = changeNumbervoit(numbervoit, vertexC.size());
                    s_c = 1;
                }
                else
                {
                    result.push_back(intPoint[1]);
                    currentposition = positionIntPoint[1];
                    numbervoit = positionC[positionIntPoint[1]];
                    result.push_back(vertexC[numbervoit]);
                    numbervoit = changeNumbervoit(numbervoit, vertexC.size());
                    s_c = 1;
                }
            }
            intPoint.clear();
            positionIntPoint.clear();
        }
        else
        {
            int count = 0;
            vector <Point> intPoint;
            vector <int> positionIntPoint;
            for (int i = 0; i < positionC.size(); i++)
            {
                if (positionC[i] == numbervoit)
                {
                    count = count + 1;
                    intPoint.push_back(intersectPoint[i]);
                    positionIntPoint.push_back(i);
                }
            }
            if (count == 0)
            {
                result.push_back(vertexC[numbervoit]);
                numbervoit = changeNumbervoit(numbervoit, vertexC.size());
            }
            if (count == 1)
            {
                result.push_back(intPoint[0]);
                currentposition = positionIntPoint[0];
                numbervoit = positionS[positionIntPoint[0]];
                result.push_back(vertexS[numbervoit]);
                numbervoit = changeNumbervoit(numbervoit, vertexS.size());
                s_c = 0;
            }
            if (count == 2)
            {
                if (distanse(intPoint[0], vertexC[numbervoit]) > distanse(intPoint[1], vertexC[numbervoit]))
                {
                    result.push_back(intPoint[0]);
                    currentposition = positionIntPoint[0];
                    numbervoit = positionS[positionIntPoint[0]];
                    result.push_back(vertexS[numbervoit]);
                    numbervoit = changeNumbervoit(numbervoit, vertexS.size());
                    s_c = 0;
                }
                else
                {
                    result.push_back(intPoint[1]);
                    currentposition = positionIntPoint[1];
                    numbervoit = positionS[positionIntPoint[1]];
                    result.push_back(vertexS[numbervoit]);
                    numbervoit = changeNumbervoit(numbervoit, vertexS.size());
                    s_c = 0;
                }
            }
            intPoint.clear();
            positionIntPoint.clear();
        }
    }
    return slice(result, 0, result.size() - 3);
}