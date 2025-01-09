#pragma once

void drawPolygon(Mat& image, vector<Point> vertex, string color);
vector<Point> calculateStarVertices(Mat& image, double radiusf, double radiuss, int number); 
