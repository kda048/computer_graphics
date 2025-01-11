#pragma once

int N(Point3d p0, Point3d p1, Point3d p2, Point3d p3);
Point3d Bezier(Point3d p0, Point3d p1, Point3d p2, Point3d p3, double t);
vector<Point3d> Curve(Point3d p0, Point3d p1, Point3d p2, Point3d p3, string color);