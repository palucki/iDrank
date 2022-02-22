include(../qmake-target-platform.pri)
include(../qmake-destination-path.pri)

DESTDIR = $$PWD/../binaries/$$DESTINATION_PATH
OBJECTS_DIR = $$PWD/build/$$DESTINATION_PATH/.obj
MOC_DIR = $$PWD/build/$$DESTINATION_PATH/.moc
RCC_DIR = $$PWD/build/$$DESTINATION_PATH/.qrc
UI_DIR = $$PWD/build/$$DESTINATION_PATH/.ui

QT += qml quick quickcontrols2

#greaterThan(QT_MAJOR_VERSION, 4) QT += widgets printsupport

TEMPLATE = app

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += source \
    ../drinq-lib/source

android: LIBS += -L$$PWD/../binaries/$$DESTINATION_PATH -ldrinq-lib_$${QT_ARCH}
else: LIBS += -L$$PWD/../binaries/$$DESTINATION_PATH -ldrinq-lib
#android: ANDROID_EXTRA_LIBS += $$PWD/../binaries/$$DESTINATION_PATH/libdrinq-lib_$${QT_ARCH}.so
#android: message(abi + "EXTRA LIBS " + $${ANDROID_EXTRA_LIBS})

#android: for (abi, ANDROID_ABIS): message(ABI: + $${abi})

message(LIBS + $${LIBS})
#message(EXTRA_LIBS + $${ANDROID_EXTRA_LIBS})



#android: ANDROID_EXTRA_LIBS += $$PWD/../binaries/$$DESTINATION_PATH/libdrinq-lib_$${QT_ARCH}.so
# e.g. libdrinq-lib_arm64-v8a.so
SOURCES += \
    components/customchart.cpp \
    main.cpp

HEADERS += components/customchart.h

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH += $$PWD

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle.properties \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

ANDROID_EXTRA_LIBS = /home/piotr/workspace/iDrank/drinq-ui-simple/../binaries/linux/mobile/armeabi-v7a/release/libdrinq-lib_armeabi-v7a.so /home/piotr/workspace/iDrank/drinq-ui-simple/../binaries/linux/mobile/x86_64/release/libdrinq-lib_x86_64.so /home/piotr/workspace/iDrank/drinq-ui-simple/../binaries/linux/mobile/x86/release/libdrinq-lib_x86.so /home/piotr/workspace/iDrank/drinq-ui-simple/../binaries/linux/mobile/arm64-v8a/release/libdrinq-lib_arm64-v8a.so /home/piotr/workspace/iDrank/drinq-ui-simple/../../../Qt/5.15.2/android/lib/libQt5Sql_x86_64.so /home/piotr/workspace/iDrank/drinq-ui-simple/../../../Qt/5.15.2/android/lib/libQt5Sql_x86.so /home/piotr/workspace/iDrank/drinq-ui-simple/../../../Qt/5.15.2/android/lib/libQt5Sql_armeabi-v7a.so /home/piotr/workspace/iDrank/drinq-ui-simple/../../../Qt/5.15.2/android/lib/libQt5Sql_arm64-v8a.so $$PWD/../../../Qt/5.15.2/android/plugins/sqldrivers/libplugins_sqldrivers_qsqlite_x86_64.so $$PWD/../../../Qt/5.15.2/android/plugins/sqldrivers/libplugins_sqldrivers_qsqlite_x86.so $$PWD/../../../Qt/5.15.2/android/plugins/sqldrivers/libplugins_sqldrivers_qsqlite_armeabi-v7a.so $$PWD/../../../Qt/5.15.2/android/plugins/sqldrivers/libplugins_sqldrivers_qsqlite_arm64-v8a.so

