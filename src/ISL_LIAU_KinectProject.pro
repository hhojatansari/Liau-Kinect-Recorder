#-------------------------------------------------
#
# Project created by QtCreator 2018-01-24T09:48:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ISL_LIAU_KinectProject
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    camerathread.cpp \
    timethread.cpp \
    writethread.cpp \
    structbody.cpp \
    createproject.cpp

HEADERS  += mainwindow.h \
    camerathread.h \
    timethread.h \
    util.h \
    writethread.h \
    structbody.h \
    createproject.h

FORMS    += mainwindow.ui \
    createproject.ui

RESOURCES += \
    resources.qrc

LIBS += "C:/Program Files/Microsoft SDKs/Kinect/v2.0_1409/Lib/x64/Kinect20.lib"

INCLUDEPATH += "C:/Program Files/Microsoft SDKs/Kinect/v2.0_1409/inc"

DEPENDPATH += "C:/Program Files/Microsoft SDKs/Kinect/v2.0_1409/inc"

DEPENDPATH +=C:/opencv/release/install/include

INCLUDEPATH +=C:/opencv/release/install/include
LIBS += -LC:/opencv/release/install/x64/vc14/lib \
    -lopencv_core310 \
    -lopencv_calib3d310 \
    -lopencv_features2d310 \
    -lopencv_flann310 \
    -lopencv_highgui310 \
    -lopencv_imgcodecs310 \
    -lopencv_imgproc310 \
    -lopencv_ml310 \
    -lopencv_objdetect310 \
    -lopencv_photo310 \
    -lopencv_shape310 \
    -lopencv_stitching310 \
    -lopencv_superres310 \
    -lopencv_ts310 \
    -lopencv_video310 \
    -lopencv_videoio310 \
    -lopencv_videostab310 \
