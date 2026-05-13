QT += testlib sql network
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    tst_database_test.cpp \
    ../database.cpp \
    ../parsing.cpp

HEADERS += \
    ../database.h \
    ../parsing.h