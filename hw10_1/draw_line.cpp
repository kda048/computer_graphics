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
        e = 2 * dy - dx; //èíèöèàëèçàöèÿ îøèáêè ñ ïîïðàâêîé íà ïîëîâèíó ïèêñåëà
        if (iy >= 0)
        { //óâåëè÷èâàåì èëè íå èçìåíÿåì y
            //îñíîâíîé öèêë
            for (i = 0; i <= dx; i++)
            {
                outputPixel(image, x, y, color);
                if (e >= 0)
                { //îøèáêà ñòàëà íåîòðèöàòåëüíîé
                    y += iy; //èçìåíÿåì y
                    e -= 2 * dx; //óìåíüøàåì îøèáêó
                }
                x += ix; //âñåãäà èçìåíÿåì x
                e += dy * 2; //è óâåëè÷èâàåì îøèáêó
            }
        }
        else
        { //y óìåíüøàåòñÿ
            for (i = 0; i <= dx; i++)
            {
                outputPixel(image, x, y, color);
                if (e > 0)
                { // îøèáêà ñòàëà ïîëîæèòåëüíîé. Óñëîâèå èçìåíèëîñü ñ >= íà >
                    y += iy;
                    e -= 2 * dx;
                }
                x += ix;
                e += dy * 2;
            }
        }
    }
    else //dy>dx
    {
        e = 2 * dx - dy; //èíèöèàëèçàöèÿ îøèáêè ñ ïîïðàâêîé íà ïîëîâèíó ïèêñåëà
        if (ix >= 0)
        { //óâåëè÷èâàåì èëè íå èçìåíÿåì y
            //îñíîâíîé öèêë
            for (i = 0; i <= dy; i++)
            {
                outputPixel(image, x, y, color);
                if (e >= 0)
                { //îøèáêà ñòàëà íåîòðèöàòåëüíîé
                    x += ix; //èçìåíÿåì y
                    e -= 2 * dy; //óìåíüøàåì îøèáêó
                }
                y += iy; //âñåãäà èçìåíÿåì x
                e += dx * 2; //è óâåëè÷èâàåì îøèáêó
            }
        }
        else
        { //y óìåíüøàåòñÿ
            for (i = 0; i <= dy; i++)
            {
                outputPixel(image, x, y, color);
                if (e > 0)
                { // îøèáêà ñòàëà ïîëîæèòåëüíîé. Óñëîâèå èçìåíèëîñü ñ >= íà >
                    x += ix;
                    e -= 2 * dy;
                }
                y += iy;
                e += dx * 2;
            }
        }

    }
}