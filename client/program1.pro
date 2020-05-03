#-------------------------------------------------
#
# Project created by QtCreator 2018-08-29T15:33:19
#
#-------------------------------------------------

QT       += core gui sql
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = asd
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    wait.cpp \
    dialogzhuce.cpp \
    start.cpp \
    dialog.cpp \
    bill.cpp \
    mysend.cpp \
    myreceive.cpp \
    database.cpp \
    revise.cpp \
    myuser.cpp \
    searchshow.cpp \
    haoping.cpp

HEADERS += \
        mainwindow.h \
    wait.h \
    dialogzhuce.h \
    start.h \
    dialog.h \
    bill.h \
    mysend.h \
    myreceive.h \
    database.h \
    revise.h \
    myuser.h \
    searchshow.h \
    haoping.h

FORMS += \
        mainwindow.ui \
    wait.ui \
    dialogzhuce.ui \
    start.ui \
    dialog.ui \
    bill.ui \
    mysend.ui \
    myreceive.ui \
    revise.ui \
    searchshow.ui \
    haoping.ui

RESOURCES += \
    imag.qrc \
    asdsd.qrc
