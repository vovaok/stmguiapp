QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
DEFINES += EMULATOR
DESTDIR = $$PWD/stmguiapp


# specify path to the STM32 project
APP = ../../../iar/test/361_ocill
#APP = ../../../iar/test/352Pult
# ---------------------------------

SFS_FILE = $$PWD/$$APP/sfs.bin

DEFINES += APP_PATH="$$APP"
DEFINES += SFS_FILE="$$SFS_FILE"

STM32 = ../../../iar/components/stm32++/src
INCLUDEPATH += $$PWD/app
INCLUDEPATH += $$STM32
INCLUDEPATH += $$STM32/gfx
INCLUDEPATH += $$STM32/gfx/gui
INCLUDEPATH += $$APP

#COMPONENTS = ../../components5
#include($$COMPONENTS/megaWidgets/megaWidgets.pri)

win32: {
    CONFIG(release,debug|release) {
        QMAKE_POST_LINK += windeployqt --no-translations $$DESTDIR
        _SRC = $$SFS_FILE
        _DST = $$DESTDIR/sfs.bin
        # replace slashes in path for Windows
        _SRC ~= s,/,\\,g
        _DST ~= s,/,\\,g
        QMAKE_POST_LINK += && $$QMAKE_COPY $$shell_quote($$_SRC) $$shell_quote($$_DST) $$escape_expand(\\n\\t)
    }
}

SOURCES += \
    ethernet/sfs.cpp \
    ethernet/tcpsocket.cpp \
    main.cpp \
    application.cpp \
    button.cpp \
    displaywidget.cpp \
    gpio.cpp \
    lcddisplay.cpp \
    led.cpp \
    mainwindow.cpp \
    rotaryencoder.cpp \
    timer.cpp \
    $$STM32/gfx/display.cpp \
    $$STM32/gfx/font.cpp \
    $$STM32/gfx/fontdatabase.cpp \
    $$STM32/gfx/image.cpp \
    $$STM32/gfx/touchscreen.cpp \
    $$STM32/gfx/framebuffer.cpp \
    $$STM32/core/advmath.cpp

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
    precisetimer.h \
    rotaryencoder.h \
    timer.h

SOURCES += $$files("$$STM32/gfx/gui/*.cpp")
HEADERS += $$files("$$STM32/gfx/gui/*.h")

APP_SOURCES = $$files("$$APP/*.cpp", true)
APP_SOURCES -= "$$APP/main.cpp"
SOURCES += $$APP_SOURCES
HEADERS += $$files("$$APP/*.h", true)

EMU_FILE = $$PWD/$$APP/emulatorwidget.h
exists($$EMU_FILE) {
    HEADERS += $$EMU_FILE
    DEFINES += EMULATOR_WIDGET
}

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
