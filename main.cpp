#include <QtGui/QApplication>
#include "mainwindow.h"

#include <QMessageBox>
#include "exception.h"

int main(int argc, char *argv[])
{
    try {
        QApplication a(argc, argv);
        MainWindow w;
        w.show();

        return a.exec();
    } catch (Exception e) {
        QMessageBox msgBox;
        msgBox.setText(e.message());
        msgBox.exec();
        exit(2);
    }
}
