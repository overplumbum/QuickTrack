#ifndef GATE_H
#define GATE_H

#include <QObject>
#include <QVariant>
#include <QDebug>

class Gate : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString tracks READ tracks)
    Q_PROPERTY(QString center READ center)
    Q_PROPERTY(QVariant zoom READ zoom)
public:
    explicit Gate(QObject *parent = 0);

    void setTracks(QString json) { _tracks = json; }
    QString tracks() { return _tracks; }

    void setCenter(QString json) { _center = json; }
    QString center() { return _center; }

    void setZoom(QVariant zoom) { _zoom = zoom; }
    QVariant zoom() { return _zoom; }

signals:

public slots:

private:
    QString _center;
    QString _tracks;
    QVariant _zoom;

};

#endif // GATE_H
