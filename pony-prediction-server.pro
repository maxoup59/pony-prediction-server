#-------------------------------------------------
#
# Project created by QtCreator 2015-04-30T16:36:15
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = pony-prediction-server
CONFIG   += console
CONFIG   -= app_bundle
CONFIG += c++11

TEMPLATE = app


SOURCES += main.cpp \
    core/server.cpp \
    core/socket-thread.cpp \
    core/util.cpp

HEADERS += \
    core/server.hpp \
    core/socket-thread.hpp \
    core/util.hpp

DISTFILES += \
    config.xml
