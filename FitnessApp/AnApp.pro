QT += quick sql
#charts

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Callendar.cpp \
        DayInfo.cpp \
        Dishes.cpp \
        Elements.cpp \
        Exercises.cpp \
        Profile.cpp \
        Lib/Database/Database.cpp
        main.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

ANDROID_ABIS = armeabi-v7a arm64-v8a

INCLUDEPATH += Lib/Database

HEADERS += \
    Callendar.h \
    DayInfo.h \
    Dishes.h \
    Elements.h \
    Exercises.h \
    Profile.h \
    Lib/Database/Database.h

android: include(C:/Users/lidek/AppData/Local/Android/Sdk/android_openssl-master/openssl.pri)
