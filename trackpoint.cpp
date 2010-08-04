#include "trackpoint.h"
#include "math.h"

bool TrackPoint::operator<(const TrackPoint& other) const
{
    return _time < other._time;
}

QString TrackPoint_toJSON(const TrackPoint &p)
{
    QString out;
    out.sprintf("[%f,%f,%d]", p._lat, p._lon, p._time.toTime_t());
    return out;
}

/**
  * Approximate distance in meters
  *
  */
inline float TrackPoint::distance(const TrackPoint& other) const
{
    return (40000000.0 / 360.0) * sqrt( pow(other._lat - _lat, 2) + pow(other._lon - _lon, 2) );
}
