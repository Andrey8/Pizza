QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

ROOTDIR = ../../
INCLUDEPATH += ROOTDIR
SOURCES += $$ROOTDIR/Algorithms/TableAlgorithms.cpp

SOURCES +=  tst_tablealgorithmstester.cpp
