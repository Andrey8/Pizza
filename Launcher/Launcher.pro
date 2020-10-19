TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

ROOT_DIR = ../
INCLUDEPATH += ROOT_DIR
SOURCES += $$ROOT_DIR/InputHandler/Utilities.cpp

SOURCES += main.cpp
