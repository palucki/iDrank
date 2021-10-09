include(../qmake-target-platform.pri)
include(../qmake-destination-path.pri)

DESTDIR = $$PWD/../binaries/$$DESTINATION_PATH
OBJECTS_DIR = $$PWD/build/$$DESTINATION_PATH/.obj
MOC_DIR = $$PWD/build/$$DESTINATION_PATH/.moc
RCC_DIR = $$PWD/build/$$DESTINATION_PATH/.qrc
UI_DIR = $$PWD/build/$$DESTINATION_PATH/.ui

QT += testlib
QT -= gui

TARGET=drinq-tests
TEMPLATE = app

CONFIG += c++14
CONFIG += console
CONFIG -= app_bundle

INCLUDEPATH += source \
    ../drinq-lib/source

LIBS += -L$$PWD/../binaries/$$DESTINATION_PATH -ldrinq-lib

SOURCES +=  source/models/tst_drinqtests.cpp \
    source/controllers/mastercontrollertests.cpp \
    source/data/datetimedecoratortests.cpp \
    source/data/enumeratordecoratortests.cpp \
    source/data/intdecoratortests.cpp \
    source/data/stringdecoratortests.cpp \
    source/main.cpp \
    source/models/clienttests.cpp \
    source/testsuite.cpp

HEADERS += \
    source/controllers/mastercontrollertests.h \
    source/data/datetimedecoratortests.h \
    source/data/enumeratordecoratortests.h \
    source/data/intdecoratortests.h \
    source/data/stringdecoratortests.h \
    source/models/clienttests.h \
    source/testsuite.h
