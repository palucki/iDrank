include(../qmake-target-platform.pri)
include(../qmake-destination-path.pri)

message ("TEST" + $$DESTINATION_PATH)

DESTDIR = $$PWD/../binaries/$$DESTINATION_PATH
OBJECTS_DIR = $$PWD/build/$$DESTINATION_PATH/.obj
MOC_DIR = $$PWD/build/$$DESTINATION_PATH/.moc
RCC_DIR = $$PWD/build/$$DESTINATION_PATH/.qrc
UI_DIR = $$PWD/build/$$DESTINATION_PATH/.ui

QT -= gui
QT += core sql charts


TARGET = drinq-lib
TEMPLATE = lib
CONFIG += c++17

DEFINES += DRINQLIB_LIBRARY

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    source/controllers/commandcontroller.cpp \
    source/controllers/databasecontroller.cpp \
    source/controllers/drinkcontroller.cpp \
    source/controllers/mastercontroller.cpp \
    source/controllers/mastercontroller2.cpp \
    source/controllers/partycontroller.cpp \
    source/data/datadecorator.cpp \
    source/data/dropdown.cpp \
    source/data/dropdownvalue.cpp \
    source/data/entity.cpp \
    source/data/enumeratordecorator.cpp \
    source/data/intdecorator.cpp \
    source/data/stringdecorator.cpp \
    source/data/datetimedecorator.cpp \
    source/framework/command.cpp \
    source/framework/partyplotter.cpp \
    source/framework/toast.cpp \
    source/framework/databasetoastprovider.cpp \
    source/framework/objectfactory.cpp \
    source/framework/drinkprovider.cpp \
    source/models/address.cpp \
    source/models/appointment.cpp \
    source/models/clientsearch.cpp \
    source/models/contact.cpp \
    source/models/drink.cpp \
    source/models/recentactivity.cpp

HEADERS += \
    source/controllers/commandcontroller.h \
    source/controllers/commandcontrollerinterface.h \
    source/controllers/databasecontroller.h \
    source/controllers/databasecontrollerinterface.h \
    source/controllers/drinkcontroller.h \
    source/controllers/mastercontroller.h \
    source/controllers/mastercontroller2.h \
    source/controllers/navigationcontroller.h \
    source/controllers/navigationcontrollerinterface.h \
    source/controllers/partycontroller.h \
    source/data/datadecorator.h \
    source/data/dropdown.h \
    source/data/dropdownvalue.h \
    source/data/entity.h \
    source/data/entitycollection.h \
    source/data/enumeratordecorator.h \
    source/data/intdecorator.h \
    source/data/stringdecorator.h \
    source/data/datetimedecorator.h \
    source/drinq-lib_global.h \
    source/framework/command.h \
    source/framework/partyplotter.h \
    source/framework/toast.h \
    source/framework/toastproviderinterface.h \
    source/framework/databasetoastprovider.h \
    source/framework/objectfactory.h \
    source/framework/objectfactoryinterface.h \
    source/framework/drinkprovider.h \
    source/models/address.h \
    source/models/appointment.h \
    source/models/clientsearch.h \
    source/models/contact.h \
    source/models/drink.h \
    source/models/recentactivity.h

INCLUDEPATH += source

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
