QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RobotGui
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
    Robot.cc \
    map.cc \
    gui.cpp

HEADERS  += \
    Robot.hh \
    map.hh \
    gui.h

FORMS    += robotgui.ui
