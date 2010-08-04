#ifndef BBOX_H
#define BBOX_H

#include "trackpoint.h"

class BBox
{
public:
    BBox(): null(true) {}
    BBox(float left, float top, float right, float bottom):
            left(left), top(top), right(right), bottom(bottom), null(false) {}

    float left, top, right, bottom;
    bool null;

    TrackPoint getCenter() const;
    inline float width() const { return right - left; }
    inline float height() const { return top - bottom; }
};

#endif // BBOX_H
