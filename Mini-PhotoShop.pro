#-------------------------------------------------
#
# Project created by QtCreator 2019-04-10T18:45:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Mini-PhotoShop
TEMPLATE = app

QT_CONFIG -= no-pkg-config
CONFIG += link_pkgconfig
PKGCONFIG += opencv4

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
    main_window.cpp \
    button.cpp \
    blackwhite.cpp \
    brightness.cpp \
    contrast.cpp \
    fliter_color.cpp \
    saturation.cpp \
    rotate.cpp \
    advancedfilter.cpp \
    basicfilter.cpp \
    noise.cpp \
    crop.cpp \
    blur.cpp \
    graph_scene.cpp \
    add_sticker.cpp \
    mosaic.cpp \
    big_eye.cpp \
    change_background.cpp \
    add_frame.cpp \
    text.cpp\
    collage.cpp

HEADERS += \
    main_window.h \
    button.h \
    blackwhite.h \
    brightness.h \
    contrast.h \
    fliter_color.h \
    saturation.h \
    rotate.h \
    advancedfilter.h \
    basicfilter.h \
    noise.h \
    blur.h \
    graph_scene.h \
    big_eye.h \
    add_frame.h\
    collage.h

RESOURCES += \
    images.qrc

DISTFILES +=

FORMS += \
    main_window.ui
