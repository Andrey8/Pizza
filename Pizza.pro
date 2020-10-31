TEMPLATE = subdirs
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SUBDIRS += \
    Base \
    Launcher \
    InputHandler \
    Algorithms \
    Tests \
    OutputCreator
