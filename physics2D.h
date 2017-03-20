#ifndef PHYSICS2D_H_INCLUDED
#define PHYSICS2D_H_INCLUDED

#include <stdlib.h>
#include <cmath>

struct TPoint {
    float x, y;
};

struct TSegment {
   TPoint a, b;
};

struct TRectangle {
    TPoint LeftTopCorner;
    float Width, Height;
};

struct TCircle {
    TPoint Center;
    float Radius;
};

bool Collision(TRectangle ARectangle1, TRectangle ARectangle2); // Collision between two rectangles.
bool Collision(TPoint APoint1, TPoint APoint2);                 // Collision between two points.
bool Collision(TCircle ACircle1, TCircle ACircle2);             // Collision between two circles.
bool Collision(TPoint APoint, TCircle ACircle);                 // Collision between point and circle.
bool Collision(TPoint APoint, TRectangle ARectangle);           // Collision between point and rectangle.
bool Collision(TCircle ACircle, TSegment ASegment);             // Collision between circle and segment.
bool Collision(TCircle ACircle, TRectangle ARectangle);         // Collision between circle and rectangle.

bool RectInRect(TRectangle ARectangle1, TRectangle ARectangle2); // Rectangle1 in rectangle2.

#endif // PHYSICS2D_H_INCLUDED
