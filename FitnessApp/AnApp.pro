QT += quick sql
#charts

CONFIG += c++11

android
{
   #DatabaseMBFiles.path = /assets/db/MB
   #DatabaseMBFiles.files += $$PWD/db/MB/*.db
   #INSTALLS += DatabaseMBFiles DatabaseMANFiles

   Database.path = $$_PRO_FILE_PWD_/Lib/Database/Database.db
   #Database.files += $$_PRO_FILE_PWD_/Lib/Database/Database.db
   INSTALLS += Database
}

message($$_PRO_FILE_PWD_/Lib/Database/Database.db)

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Callendar.cpp \
        DayInfo.cpp \
        Dishes.cpp \
        ElementInfo.cpp \
        Elements.cpp \
        Exercises.cpp \
        Fasting.cpp \
        GUI/GUIInterface.cpp \
        Home.cpp \
        Profile.cpp \
        Lib/Database/Database.cpp \
        Settings.cpp \
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

INCLUDEPATH += \
   Lib/Database \
   GUI

HEADERS += \
    Callendar.h \
    DayInfo.h \
    Dishes.h \
    ElementInfo.h \
    Elements.h \
    Exercises.h \
    Fasting.h \
    GUI/GUIInterface.h \
    Home.h \
    Profile.h \
    Lib/Database/Database.h \
    Settings.h

android: include(C:/Users/lidek/AppData/Local/Android/Sdk/android_openssl-master/openssl.pri)

DISTFILES += \
   android/AndroidManifest.xml \
   android/build.gradle \
   android/gradle/wrapper/gradle-wrapper.jar \
   android/gradle/wrapper/gradle-wrapper.properties \
   android/gradlew \
   android/gradlew.bat \
   android/res/values/libs.xml

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
