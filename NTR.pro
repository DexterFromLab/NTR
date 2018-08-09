QT += core
QT -= gui

TARGET = NTR
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    rectangledetector.cpp

unix:!macx: LIBS += -L$$PWD/../opencv_install/lib/ -lopencv_bioinspired

INCLUDEPATH += $$PWD/../opencv_install/include
DEPENDPATH += $$PWD/../opencv_install/include

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += /home/bartek/Repositories/opencv_install/lib/pkgconfig/opencv.pc

HEADERS += \
rectangledetector.h
