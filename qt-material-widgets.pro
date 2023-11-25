greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt-material-widgets
TEMPLATE = subdirs
SUBDIRS = components demo
CONFIG += ordered
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000
