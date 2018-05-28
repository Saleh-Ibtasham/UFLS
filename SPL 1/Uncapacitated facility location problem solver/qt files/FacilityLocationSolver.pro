#-------------------------------------------------
#
# Project created by QtCreator 2018-05-29T07:00:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FacilityLocationSolver
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    clusteringapproach.cpp \
    iterative.cpp \
    setcover.cpp \
    outputdialogue.cpp

HEADERS  += mainwindow.h \
    clusteringapproach.h \
    iterative.h \
    setcover.h \
    outputdialogue.h

FORMS    += mainwindow.ui \
    clusteringapproach.ui \
    iterative.ui \
    setcover.ui \
    outputdialogue.ui
