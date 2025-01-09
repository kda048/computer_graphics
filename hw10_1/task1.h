#pragma once

bool isPointOnSegment(Point p, Point a, Point b);
bool intersect(Point a, Point b, Point c, Point d);
bool isIntersect(vector<Point> vertex);
double crossProduct(Point p1, Point p2, Point p3);
bool isConvex(vector<Point>& vertex);
bool isClockwise(vector<Point>& vertex);
void reversePolygon(vector<Point>& polygon);
Point getIntersection(Point a, Point b, Point c, Point d);
double distanse(Point p1, Point p2);
int changeNumbervoit(int numbervoit, int n);
vector<Point> slice(vector<Point>& v, int m, int n);
vector <Point> WeilerAthertonModification(vector<Point> vertexS, vector<Point> vertexC);