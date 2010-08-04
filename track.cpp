#include "track.h"
#include <QtConcurrentMap>

Track::Track()
{
}

QString Track::toJSON() const
{
    QStringList points_json = QtConcurrent::blockingMapped<QStringList>(points, &TrackPoint_toJSON);
    QString data("{name:'%1',date:'%2',points:%3}");
    return data.arg(
        name,
        date.toString(),
        QString("[%1]").arg(points_json.join(","))
    );
}

void Track::simplify(int count)
{
    if (this->points.length() <= count) {
        return;
    }

    // take every n-th point + the last one
    QList<TrackPoint> some_points;
    int step = points.length() / count;
    if (step < 1) {
        step = 1;
    }
    for(int i = 0; i < points.length() - 1; i+= step) {
        some_points.append(points[i]);
    }
    some_points.append(points.last());
    points = some_points;
}

BBox Track::getBBox() const
{
    if (!points.length()) {
        return BBox();
    }

    float left, top, bottom, right;
    left = right = points[0]._lon;
    top = bottom = points[0]._lat;

    QList<TrackPoint>::const_iterator i = points.begin();
    ++i;
    for (; i != points.end(); ++i) {
        float lat = (*i)._lat;
        float lon = (*i)._lon;

        if ( lon < left) {
            left = lon;
        } else if (lon > right) {
            right = lon;
        }

        if ( lat > top) {
            top = lat;
        } else if (lat < bottom) {
            bottom = lat;
        }
    }
    return BBox(left, top, right, bottom);
}

QList<Track> Track::autoSplit()
{
    // разделять по точкам оторванным более чем на пол-часа (конфиг!)
    // разделять по точкам оторванным более чем на 0.02 градуса (~2.2км, конфиг!)
    // отдельные точки трэком не считать
    // серию абс. одинаковых кроме времени точек == одной точке
    QList<Track> out;
    return out;
}
