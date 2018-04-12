QT += core
QT -= gui
QT += serialport

CONFIG += c++11

TARGET = QtSerial
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    crypto.cpp

HEADERS += \
    crypto.h
