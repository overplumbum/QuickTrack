#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "exception.h"
#include <QWebFrame>
#include <QtNetwork/QNetworkDiskCache>
#include "trackpoint.h"
#include <QFileDialog>
#include <QSettings>
#include <QMessageBox>
#include "tracklist.h"
#include "math.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QCoreApplication::setApplicationName("QuickTrack");
    QCoreApplication::setOrganizationName("Overplumbum");
    QCoreApplication::setOrganizationDomain("overplumbum.moikrug.ru");
    settings = new QSettings();

    ui->setupUi(this);

    QString path;
    if (QApplication::argc() > 1) {
        path = QApplication::arguments().at(1);
    } else {
        path =  QFileDialog::getOpenFileName(
            0,
            "Open Track",
            settings->value("last_open_directory", QString("")).toString(),
            "GPX (*.gpx)"
        );
        if (path.isNull()) {
            exit(1);
            return;
        }
    }

    QFileInfo f(path);
    if (f.absoluteDir().exists()) {
        settings->setValue("last_open_directory", f.absoluteDir().absolutePath());
    }

    load(path);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int zoomLevel(int window_width_px, float distance_degrees)
{
    int tiles_count = ceil(window_width_px / 256.0);
    return floor(log(360.0 * (1.0 * tiles_count / distance_degrees)) / log(2));
}

void MainWindow::load(const QString source)
{
    QFile input(source);
    TrackList ts = TrackList(input);

    if (!ts.tracks.length()) {
        QMessageBox msgBox;
        msgBox.setText(QString("No track points found in <%1>").arg(source));
        msgBox.exec();
        exit(0);
    }

    BBox bb = ts.getBBox();
    TrackPoint center = bb.getCenter();
    gate.setCenter(center.toJSON());

    int zoom_w, zoom_h;
    zoom_w = zoom_h = 13;
    if (bb.width()) {
        zoom_w = zoomLevel(width(), bb.width());
    }
    if (bb.height()) {
        zoom_h = zoomLevel(height(), bb.height()) - 1;
    }
    gate.setZoom(zoom_w < zoom_h? zoom_w : zoom_h);

    for (QList<Track>::iterator i = ts.tracks.begin(); i != ts.tracks.end(); ++i) {
        (*i).simplify(settings->value("max_points", 1000).toInt());
    }

    gate.setTracks(ts.toJSON());

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    if (settings->value("http_use_disk_cache", true).toBool()) {
        QNetworkDiskCache *diskCache = new QNetworkDiskCache(this);

        QString cachedir("cache");
        QString appdata(getenv("APPDATA"));
        if (appdata.length() > 0) {
            cachedir = appdata.append("\\QuickTrack\\webcache");
        }

        diskCache->setCacheDirectory(cachedir);
        diskCache->setMaximumCacheSize(
            settings->value("http_disk_cache_size_mb", 200).toUInt() * 1024 * 1024
        );

        manager->setCache(diskCache);
    }

    QWebPage *page = new QWebPage(this);
    page->setNetworkAccessManager(manager);
    ui->webView->setPage(page);

    QFile content(":/htdocs/map.html");
    content.open(QFile::ReadOnly);
    ui->webView->setContent(content.readAll(), QString("text/html"));
    content.close();
}

void MainWindow::on_webView_loadFinished(bool ok)
{
    if (!ok) {
        ui->statusBar->setWindowTitle("Page load failed");
        return;
    }

    QWebFrame *frame = ui->webView->page()->mainFrame();
    custom_on_webView_javaScriptWindowObjectCleared();
    connect(
        frame,
        SIGNAL(javaScriptWindowObjectCleared()),
        SLOT(custom_on_webView_javaScriptWindowObjectCleared())
    );
    frame->evaluateJavaScript("load();");
}

void MainWindow::custom_on_webView_javaScriptWindowObjectCleared()
{
    ui->webView->page()->mainFrame()->addToJavaScriptWindowObject(QString("gate"), &gate);
}
