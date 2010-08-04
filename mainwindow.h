#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include "gate.h"
#include <QSettings>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void load(const QString source);

    Gate gate;
    QSettings *settings;
private slots:
    void on_webView_loadFinished(bool );
    void custom_on_webView_javaScriptWindowObjectCleared();
};

#endif // MAINWINDOW_H
