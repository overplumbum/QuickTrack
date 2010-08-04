#include "tracklist.h"
#include "exception.h"
#include <QtConcurrentMap>
#include <QtAlgorithms>
#include <QtXml>

TrackList::TrackList()
{
}

TrackList::TrackList(QFile &input)
{
    if (!input.exists()) {
        throw new Exception(QString("File not found: <%1>").arg(input.fileName()));
    }

    QDomDocument d;
    d.setContent(&input);

    QDomElement root = d.documentElement();
    QDomElement pointNode, segmentNode, trackNode;

    Track t;

    // <gpx
    // <trk><name>АВГ-30-09 14:15:47</name>
    // <trkseg>
    // <trkpt lat="54.11111" lon="37.11111"><ele>112.13</ele><time>2009-08-29T15:36:42Z</time></trkpt>

    tracks.clear();
    trackNode = root.firstChildElement("trk");
    for (; !trackNode.isNull(); trackNode = trackNode.nextSiblingElement("trk")) {
        t.name = trackNode.firstChildElement("name").text();

        segmentNode = trackNode.firstChildElement("trkseg");
        for (; !segmentNode.isNull(); segmentNode = segmentNode.nextSiblingElement("trkseg")) {
            t.points.clear();

            pointNode = segmentNode.firstChildElement("trkpt");
            for (; !pointNode.isNull(); pointNode = pointNode.nextSiblingElement("trkpt")) {
                t.points.append(TrackPoint(
                    pointNode.attribute("lat").toFloat(),
                    pointNode.attribute("lon").toFloat(),
                    QDateTime::fromString(pointNode.firstChildElement("time").text(), Qt::ISODate)
                ));
            }

            qSort(t.points);

            if (t.points.length()) {
                tracks.append(t);
            }
        }
    }
}


QString TrackList::toJSON() const
{
    QStringList jsons = QtConcurrent::blockingMapped<QStringList>(tracks, &Track_toJSON);
    return QString("[%1]").arg(jsons.join(","));
}

BBox TrackList::getBBox() const
{
    if (!tracks.length()) {
        return BBox();
    }
    BBox cur, max;

    Track t = tracks.first();
    max = t.getBBox();

    QList<Track>::const_iterator i = tracks.begin();
    ++i;
    for (; i != tracks.end(); ++i) {
        cur = (*i).getBBox();
        if (cur.left < max.left) {
            max.left = cur.left;
        }
        if (cur.top < max.top) {
            max.top = cur.top;
        }
        if (cur.right > max.right) {
            max.right = cur.right;
        }
        if (cur.bottom > max.bottom) {
            max.bottom = cur.bottom;
        }
    }

    return max;
}
