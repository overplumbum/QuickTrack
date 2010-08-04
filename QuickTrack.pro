#-------------------------------------------------
#
# Project created by QtCreator 2010-07-29T17:14:24
#
#-------------------------------------------------

QT       += core gui webkit xml network

TARGET = QuickTrack
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    exception.cpp \
    gate.cpp \
    trackpoint.cpp \
    track.cpp \
    tracklist.cpp \
    bbox.cpp

HEADERS  += mainwindow.h \
    exception.h \
    gate.h \
    trackpoint.h \
    track.h \
    tracklist.h \
    bbox.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    htdocs/ymap.html \
    todos.txt \
    htdocs/map.html \
    QuickTrack.nsi \
    dist.cmd \
    FileAssociation.nsh

RESOURCES += \
    application.qrc
