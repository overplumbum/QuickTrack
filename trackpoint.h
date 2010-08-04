#ifndef TRACKPOINT_H
#define TRACKPOINT_H

#include <QDateTime>

class TrackPoint;

QString TrackPoint_toJSON(const TrackPoint &p);

class TrackPoint
{
public:
    TrackPoint(float lat, float lon, QDateTime time): _lat(lat), _lon(lon), _time(time) {}
    TrackPoint(float lat, float lon): _lat(lat), _lon(lon) {}
    TrackPoint(const TrackPoint& copy): _lat(copy._lat), _lon(copy._lon), _time(copy._time)  {}

    float _lat;
    float _lon;
    QDateTime _time;

    bool operator<(const TrackPoint& other) const;

    inline float distance(const TrackPoint& other) const;
    inline QString toJSON() const { return TrackPoint_toJSON(*this); }
};

#endif // TRACKPOINT_H
