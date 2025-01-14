#include <opencv4/opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace cv;
using namespace std;


void SetPixel(int x, int y, cv::Scalar color, cv::Mat &img)
{
    img.at<cv::Vec3b>(y, x) = cv::Vec3b(color[2], color[1], color[0]);
}

void Line(int x1, int y1, int x2, int y2, cv::Scalar color, cv::Mat &img)
{
    int x = x1, y = y1;
    int dx = x2 - x1, dy = y2 - y1;
    int ix, iy;
    int e;
    int i;
    if (dx > 0)
        ix = 1;
    else if (dx < 0)
    {
        ix = -1;
        dx = -dx;
    }
    else
        ix = 0;
    if (dy > 0)
        iy = 1;
    else if (dy < 0)
    {
        iy = -1;
        dy = -dy;
    }
    else
        iy = 0;
    if (dx >= dy)
    {
        e = 2 * dy - dx;
        if (iy >= 0)
        {
            for (i = 0; i <= dx; i++)
            {
                SetPixel(x, y, color, img);
                if (e >= 0)
                {
                    y += iy;
                    e -= 2 * dx;
                }
                x += ix;
                e += dy * 2;
            }
        }
        else
        {
            for (i = 0; i <= dx; i++)
            {
                SetPixel(x, y, color, img);
                if (e > 0)
                {
                    y += iy;
                    e -= 2 * dx;
                }
                x += ix;
                e += dy * 2;
            }
        }
    }
    else
    {
        e = 2 * dx - dy;
        if (ix >= 0)
        {
            for (i = 0; i <= dy; i++)
            {
                SetPixel(x, y, color, img);
                if (e >= 0)
                {
                    x += ix;
                    e -= 2 * dy;
                }
                y += iy;
                e += dx * 2;
            }
        }
        else
        {
            for (i = 0; i <= dy; i++)
            {
                SetPixel(x, y, color, img);
                if (e > 0)
                {
                    x += ix;
                    e -= 2 * dy;
                }
                y += iy;
                e += dx * 2;
            }
        }
    }
}

enum ClPointType
{
    LEFT,
    RIGHT,
    BEYOND,
    BEHIND,
    BETWEEN,
    ORIGIN,
    DESTINATION
};

ClPointType Classify(double x1, double y1, double x2, double y2, double x, double y)
{
    double ax = x2 - x1;
    double ay = y2 - y1;
    double bx = x - x1;
    double by = y - y1;
    double s = ax * by - bx * ay;
    if (s > 0)
        return LEFT;
    if (s < 0)
        return RIGHT;
    if ((ax * bx < 0) || (ay * by < 0))
        return BEHIND;
    if ((ax * ax + ay * ay) < (bx * bx + by * by))
        return BEHIND;
    if (x1 == x && y1 == y)
        return ORIGIN;
    if (x2 == x && y2 == y)
        return DESTINATION;
    return BETWEEN;
}

enum IntersectType
{
    SAME,
    PARALLEL,
    SKEW,
    SKEW_CROSS,
    SKEW_NO_CROSS
};

IntersectType Intersect(double ax, double ay, double bx, double by, double cx, double cy,
                        double dx, double dy, double *t)
{
    double nx = dy - cy;
    double ny = cx - dx;
    ClPointType type;
    double denom = nx * (bx - ax) + ny * (by - ay);
    if (denom == 0)
    {
        type = Classify(cx, cy, dx, dy, ax, ay);
        if (type == LEFT || type == RIGHT)
            return PARALLEL;
        else
            return SAME;
    }
    double num = nx * (ax - cx) + ny * (ay - cy);
    *t = -num / denom;
    return SKEW;
}

void Create(std::vector<int> points_x, std::vector<int> points_y, cv::Mat &img)
{
    int N = 1000;
    double dt = 1.0 / (N - 1);
    for (int i = 0; i < N; i++)
    {
        double t = i * dt;
        double t_next = (i + 1) * dt;
        double B0 = (1 - t) * (1 - t) * (1 - t);
        double B1 = 3 * t * (1 - t) * (1 - t);
        double B2 = 3 * t * t * (1 - t);
        double B3 = t * t * t;
        double point1_x = B0 * points_x[0] + B1 * points_x[1] + B2 * points_x[2] + B3 * points_x[3];
        double point1_y = B0 * points_y[0] + B1 * points_y[1] + B2 * points_y[2] + B3 * points_y[3];

        B0 = (1 - t_next) * (1 - t_next) * (1 - t_next);
        B1 = 3 * t_next * (1 - t_next) * (1 - t_next);
        B2 = 3 * t_next * t_next * (1 - t_next);
        B3 = t_next * t_next * t_next;
        double point2_x = B0 * points_x[0] + B1 * points_x[1] + B2 * points_x[2] + B3 * points_x[3];
        double point2_y = B0 * points_y[0] + B1 * points_y[1] + B2 * points_y[2] + B3 * points_y[3];

        Line(point1_x, point1_y, point2_x, point2_y, cv::Scalar(255, 255, 255), img);
    }
    for (int i = 0; i < points_x.size() - 1; i++)
    {
        Line(points_x[i], points_y[i], points_x[i + 1], points_y[i + 1], cv::Scalar(0, 0, 255), img);
    }
}

void ComplexBezier(std::vector<int> points_x, std::vector<int> points_y, cv::Mat &img, int n)
{
    double t = 0;
    if (Intersect(points_x[2], points_y[2], points_x[3], points_y[3],  points_x[3], points_y[3], points_x[4], points_y[4], &t) != SAME)
    {
        std::cout << "Кривая не гладкая" << std::endl;
    }
    else
    {
        std::cout << "Кривая гладкая" << std::endl;
    }
    std::vector<int> buf_x;
    std::vector<int> buf_y;
    for(int i = 0; i < 4; i++)
    {
        buf_x.push_back(points_x[i]);
        buf_y.push_back(points_y[i]);
    }
    Create(buf_x, buf_y, img);
    buf_x.clear();
    buf_y.clear();
    for(int i = 3; i < n; i++){
        buf_x.push_back(points_x[i]);
        buf_y.push_back(points_y[i]);
    }
    Create(buf_x, buf_y, img);
}

int main()
{
    cv::Mat img(1000, 1000, CV_8UC3, cv::Scalar(0, 0, 0));
    int n;
    std::cin >> n;
    
    std::vector<int> points_x;
    std::vector<int> points_y;

    for(int i = 0; i < n; i++)
    {
        int x, y;
        std::cin >> x >> y;
        points_x.push_back(x);
        points_y.push_back(y);
    }

    ComplexBezier(points_x, points_y, img, n);
    cv::imshow("img", img);
    cv::imwrite("../output.png", img);

    cv::waitKey(0);
    return 0;
}
