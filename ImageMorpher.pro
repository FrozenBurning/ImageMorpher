#-------------------------------------------------
#
# Project created by QtCreator 2019-10-22T18:15:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageMorpher
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
        src/main.cpp \
        src/mainwindow.cpp \
    src/morpher.cpp \
    src/TPS.cpp \
    src/interpolation.cpp \
    src/distortion.cpp \
    src/SelfCV.cpp

HEADERS += \
        include/mainwindow.h \
    include/TPS.h \
    include/morpher.h \
    include/distortion.h \
    include/interpolation.h \
    include/SelfCV.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    images.qrc

INCLUDEPATH += 3rdparty


QMAKE_LFLAGS += -no-pie

QMAKE_CXXFLAGS += -std=c++11

LIBS += -L$$PWD/3rdparty/lib -lopencv_core -lopencv_imgcodecs -lopencv_imgproc
