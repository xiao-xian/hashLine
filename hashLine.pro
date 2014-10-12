#-------------------------------------------------
#
# Project created by QtCreator 2014-10-11T19:26:28
#
#-------------------------------------------------

QT       += core

QT       += widgets

TARGET = hashLine
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += c++11

QMAKE_CXXFLAGS += -std=c++0x

TEMPLATE = app


SOURCES += main.cpp \
    graphicWidget.cpp \
    node.cpp \
    mainWindow.cpp

HEADERS += \
    graphicWidget.h \
    node.h \
    mainWindow.h \
    hashLine.h \
    helpers.h
