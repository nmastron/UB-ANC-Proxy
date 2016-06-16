QT += core network
QT -= gui

CONFIG += c++11

TARGET = ub-anc-pxy
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    UBProxy.cpp \
    UBServer.cpp

HEADERS += \
    UBProxy.h \
    UBServer.h \
    config.h
