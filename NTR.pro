QT += core
QT -= gui

TARGET = NTR
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    rectangledetector.cpp \
    textrecognation.cpp

unix:!macx: LIBS += -L$$PWD/../install/lib/ -lopencv_bioinspired

INCLUDEPATH += $$PWD/../install/include
DEPENDPATH += $$PWD/../install/includede

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += /home/bartosz/Dokumenty/Repositories/text_detector/install/lib/pkgconfig/opencv.pc

HEADERS += \
rectangledetector.h \
    textrecognation.h
