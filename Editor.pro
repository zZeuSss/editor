#-------------------------------------------------
#
# Project created by QtCreator 2018-05-07T09:55:42
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Editor
TEMPLATE = app


SOURCES += main.cpp\
        editor.cpp \
    textedit.cpp \
    sqlcontroller.cpp \
    lineframe.cpp \
    inputdialog.cpp \
    treewidget.cpp

HEADERS  += editor.h \
    textedit.h \
    sqlcontroller.h \
    lineframe.h \
    inputdialog.h \
    treewidget.h
