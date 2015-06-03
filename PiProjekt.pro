TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    communication.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    communication.h

