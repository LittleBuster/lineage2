QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = healer
TEMPLATE = app

LIBS += -lgdi32

CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        widget.cpp \
    app.cpp

HEADERS  += widget.h \
    app.h

FORMS    += widget.ui
