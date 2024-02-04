QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
DEFINES += EMULATOR


# specify path to the STM32 project
APP = ../../../iar/test/361_ocill
#APP = ../../../iar/test/352Pult
# ---------------------------------


STM32 = ../../../iar/components/stm32++/src
INCLUDEPATH += $$PWD/app
INCLUDEPATH += $$STM32
INCLUDEPATH += $$STM32/gfx
INCLUDEPATH += $$STM32/gfx/gui

#COMPONENTS = ../../components5
#include($$COMPONENTS/megaWidgets/megaWidgets.pri)

SOURCES += \
    main.cpp \
    application.cpp \
    button.cpp \
    displaywidget.cpp \
    gpio.cpp \
    lcddisplay.cpp \
    led.cpp \
    mainwindow.cpp \
    timer.cpp \
    $$STM32/gfx/display.cpp \
    $$STM32/gfx/font.cpp \
    $$STM32/gfx/fontdatabase.cpp \
    $$STM32/gfx/image.cpp \
    $$STM32/gfx/touchscreen.cpp \
    $$STM32/gfx/framebuffer.cpp

HEADERS += \
    application.h \
    button.h \
    displaywidget.h \
    ethernet/tcpserver.h \
    ethernet/tcpsocket.h \
    gpio.h \
    lcddisplay.h \
    led.h \
    mainwindow.h \
    timer.h

SOURCES += $$files("$$STM32/gfx/gui/*.cpp")

APP_SOURCES = $$files("$$APP/*.cpp", true)
APP_SOURCES -= "$$APP/main.cpp"
SOURCES += $$APP_SOURCES
#HEADERS += $$files("$$APP/*.h", true)

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
