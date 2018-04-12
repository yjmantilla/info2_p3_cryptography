QT += core
QT -= gui
QT += serialport

CONFIG += c++11

TARGET = QtSerial
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    crypto.cpp

HEADERS += \
    crypto.h
