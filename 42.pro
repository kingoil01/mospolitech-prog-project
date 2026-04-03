QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    authregform.cpp \
    buttonhandler.cpp \
    clientcontroller.cpp \
    main.cpp \
    mainform.cpp \
    managerform.cpp \
    mytcpclient.cpp \
    test.cpp

HEADERS += \
    authregform.h \
    buttonhandler.h \
    clientcontroller.h \
    mainform.h \
    managerform.h \
    mytcpclient.h \
    test.h

FORMS += \
    authregform.ui \
    mainform.ui \
    test.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
