TEMPLATE = lib
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

ROOTDIR = ../
INCLUDEPATH += ROOTDIR
SOURCES += $$ROOTDIR/Algorithms/TableAlgorithms.cpp \
    Utils.cpp

SOURCES +=

HEADERS += \
    Utils.h
