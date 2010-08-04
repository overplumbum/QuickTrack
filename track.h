#ifndef TRACK_H
#define TRACK_H

#include <QString>
#include <QDate>
#include <QList>
#include "trackpoint.h"
#include "bbox.h"

class Track
{
public:
    Track();
    Track(const Track &t): name(t.name), date(t.date), points(t.points) {}

    QString name;
    QDate date;
    QList<TrackPoint> points;

    QString toJSON() const;
    void simplify(int count = 500);
    BBox getBBox() const;

    QList<Track> autoSplit();
};

inline QString Track_toJSON(const Track& track)
{
    return track.toJSON();
}

#endif // TRACK_H
