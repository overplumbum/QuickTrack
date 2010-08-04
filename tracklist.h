#ifndef TRACKLIST_H
#define TRACKLIST_H

#include <QList>
#include <QFile>
#include "track.h"
#include "bbox.h"

class TrackList
{
public:
    TrackList();
    TrackList(QFile &gpx);

    QList<Track> tracks;

    QString toJSON() const;
    BBox getBBox() const;
};

#endif // TRACKLIST_H
