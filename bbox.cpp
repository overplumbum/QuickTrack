#include "bbox.h"

TrackPoint BBox::getCenter() const
{
    return TrackPoint((top+bottom) / 2.0, (left+right) / 2.0);
}
