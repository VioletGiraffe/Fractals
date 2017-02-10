#-------------------------------------------------
#
# Project created by QtCreator 2017-02-10T00:32:27
#
#-------------------------------------------------

QT += core gui widgets

TARGET = FractalViewer
TEMPLATE = app

mac* | linux*{
	CONFIG(release, debug|release):CONFIG += Release
	CONFIG(debug, debug|release):CONFIG += Debug
}

Release:OUTPUT_DIR=release
Debug:OUTPUT_DIR=debug

DESTDIR  = ../bin/$${OUTPUT_DIR}/
OBJECTS_DIR = ../build/$${OUTPUT_DIR}/$${TARGET}/
MOC_DIR     = ../build/$${OUTPUT_DIR}/$${TARGET}/
UI_DIR      = ../build/$${OUTPUT_DIR}/$${TARGET}/
RCC_DIR     = ../build/$${OUTPUT_DIR}/$${TARGET}/

CONFIG += c++14

win32*:!*msvc2012:*msvc* {
	QMAKE_CXXFLAGS += /FS
}

win*{
	QMAKE_CXXFLAGS += /MP
	DEFINES += WIN32_LEAN_AND_MEAN NOMINMAX
	QMAKE_CXXFLAGS_WARN_ON = /W4
}

linux*|mac*{
	QMAKE_CXXFLAGS += -pedantic-errors
	QMAKE_CFLAGS += -pedantic-errors
	QMAKE_CXXFLAGS_WARN_ON = -Wall -Wno-c++11-extensions -Wno-local-type-template-args -Wno-deprecated-register

	Release:DEFINES += NDEBUG=1
	Debug:DEFINES += _DEBUG
}


SOURCES += main.cpp\
	mainwindow.cpp \
	cfractalwidget.cpp

HEADERS  += mainwindow.h \
	cfractalwidget.h

FORMS    += mainwindow.ui

INCLUDEPATH += \
	../math \
	../cpputils \
	../fractals \
	../cpp-template-utils

LIBS += -L$${DESTDIR}
LIBS += -lcpputils -lfractals
