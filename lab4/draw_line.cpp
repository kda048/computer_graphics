#include "pixel.h"
#include "draw_line.h"

void drawLine(Mat& image, Point start, Point end, string color)
{
    int x = start.x;
    int y = start.y;
    int dx = end.x - start.x;
    int dy = end.y - start.y;
    int ix, iy;
    int e;
    int i;


    if (dx > 0)
    {
        ix = 1;
    }
    else
    {
        if (dx < 0)
        {
            ix = -1;
            dx = -dx;
        }
        else
        {
            ix = 0;
        }
    }

    if (dy > 0)
    {
        iy = 1;
    }
    else
    {
        if (dy < 0)
        {
            iy = -1;
            dy = -dy;
        }
        else
        {
            iy = 0;
        }
    }

    if (dx >= dy)
    {
        e = 2 * dy - dx; 
        if (iy >= 0)
        {
            for (i = 0; i <= dx; i++)
            {
                outputPixel(image, x, y, color);
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
                outputPixel(image, x, y, color);
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
                outputPixel(image, x, y, color);
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
                outputPixel(image, x, y, color);
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