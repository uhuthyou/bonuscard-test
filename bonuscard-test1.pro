TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp \
    system.cpp \
    client.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    system.h \
    client.h \
    transaction.h \
    bonuscard.h

