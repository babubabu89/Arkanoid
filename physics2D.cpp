#include "physics2D.h"

bool Collision(TRectangle ARectangle1, TRectangle ARectangle2) {
    if (ARectangle1.LeftTopCorner.x > ARectangle2.LeftTopCorner.x + ARectangle2.Width || ARectangle1.LeftTopCorner.x + ARectangle1.Width < ARectangle2.LeftTopCorner.x ||
        ARectangle1.LeftTopCorner.y > ARectangle2.LeftTopCorner.y + ARectangle2.Height || ARectangle1.LeftTopCorner.y + ARectangle1.Height < ARectangle2.LeftTopCorner.y) {
        return false;
    }
    else {
        return true;
    }
}

bool Collision(TPoint APoint1, TPoint APoint2) {
    if (APoint1.x == APoint2.x && APoint1.y == APoint2.y) {
        return true;
    }
    else {
        return false;
    }
}

bool Collision(TCircle ACircle1, TCircle ACircle2) {
    float d = sqrt(pow(ACircle1.Center.x - ACircle2.Center.x, 2) + pow(ACircle1.Center.y - ACircle2.Center.y, 2));

    if (!(d > ACircle1.Radius + ACircle2.Radius)) {
        return true;
    }
    else {
        return false;
    }
}

bool Collision(TPoint APoint, TCircle ACircle) {
    float d = sqrt(pow(ACircle.Center.x - APoint.x, 2) + pow(ACircle.Center.y - APoint.y, 2));

    if (d <= ACircle.Radius) {
        return true;
    }
    else {
        return false;
    }
}

bool Collision(TPoint APoint, TRectangle ARectangle) {
    if (APoint.x >= ARectangle.LeftTopCorner.x && APoint.x <= ARectangle.LeftTopCorner.x + ARectangle.Width && APoint.y >= ARectangle.LeftTopCorner.y && APoint.y <= ARectangle.LeftTopCorner.y + ARectangle.Height) {
        return true;
    }
    else {
        return false;
    }
}

bool Collision(TCircle ACircle, TSegment ASegment) {
    if (Collision(ASegment.a, ACircle) || Collision(ASegment.a, ACircle)) {
        return true;
    }
    // TODO: Analyze how it works.
    float c1x = ACircle.Center.x - ASegment.a.x;
    float c1y = ACircle.Center.y - ASegment.a.y;
    float e1x = ASegment.b.x - ASegment.a.x;
    float e1y = ASegment.b.y - ASegment.a.y;

    float k = c1x * e1x + c1y * e1y;

    if (k > 0) {
        float len = sqrt(e1x * e1x + e1y * e1y);
        k = k / len;

        if (k < len) {
            if (sqrt(c1x * c1x + c1y * c1y - k * k) <= ACircle.Radius) {
                return true;
            }
        }
    }
    return false;
}

bool Collision(TCircle ACircle, TRectangle ARectangle) {
    TSegment segment1, segment2;

    TPoint RectCenter;
    RectCenter.x = ARectangle.LeftTopCorner.x + ARectangle.Width / 2;
    RectCenter.y = ARectangle.LeftTopCorner.y + ARectangle.Height / 2;

    TPoint RectLeftUpCorner, RectRightUpCorner, RectRightDownCorner, RectLeftDownCorner;
    RectLeftUpCorner = ARectangle.LeftTopCorner;

    RectRightUpCorner.x = RectLeftUpCorner.x + ARectangle.Width;
    RectRightUpCorner.y = RectLeftUpCorner.y;

    RectRightDownCorner.x = RectLeftUpCorner.x + ARectangle.Width;
    RectRightDownCorner.y = RectLeftUpCorner.y + ARectangle.Height;

    RectLeftDownCorner.x = RectLeftUpCorner.x;
    RectLeftDownCorner.y = RectLeftUpCorner.y + ARectangle.Height;

    if (ACircle.Center.x > RectCenter.x) {
        segment1.a = RectRightUpCorner;
        segment1.b = RectRightDownCorner;
    }
    else {
        segment1.a = RectLeftUpCorner;
        segment1.b = RectLeftDownCorner;
    }

    if (ACircle.Center.y > RectCenter.y) {
        segment2.a = RectLeftDownCorner;
        segment2.b = RectRightDownCorner;
    }
    else {
        segment2.a = RectLeftUpCorner;
        segment2.b = RectRightUpCorner;
    }

    return (Collision(ACircle, segment1) || Collision(ACircle, segment2));
}

bool RectInRect(TRectangle ARectangle1, TRectangle ARectangle2) {
    if (ARectangle1.LeftTopCorner.x >= ARectangle2.LeftTopCorner.x && ARectangle1.LeftTopCorner.y >= ARectangle2.LeftTopCorner.y &&
        ARectangle1.LeftTopCorner.x + ARectangle1.Width <= ARectangle2.LeftTopCorner.x + ARectangle2.Width && ARectangle1.LeftTopCorner.y + ARectangle1.Height <= ARectangle2.LeftTopCorner.y + ARectangle2.Height) {
        return true;
    }
    else {
        return false;
    }
}
