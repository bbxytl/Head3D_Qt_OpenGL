#-------------------------------------------------
#
# Project created by QtCreator 2014-08-22T06:51:49
#
#-------------------------------------------------
DEPENDPATH +=
LIBS += -lglut 
# -lGLU
QT          += opengl widgets

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = head3D
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    nehewidget.cpp \
    chead.cpp \
    dialog.cpp

HEADERS  += widget.h \
    nehewidget.h \
    chead.h \
    dialog.h

FORMS    += widget.ui \
    dialog.ui
