#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "Exercises.h"
#include "Dishes.h"

//classes connected to view qml files
#include "Callendar.h"
#include "Elements.h"
#include "DayInfo.h"
#include "Home.h"

/*#include <ctime>
#include <iostream>
#include <QDebug>*/

int main(int argc, char *argv[])
{
   QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

   QGuiApplication app(argc, argv);

   QQmlApplicationEngine engine;
   const QUrl url(QStringLiteral("qrc:/main.qml"));
   QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
   }, Qt::QueuedConnection);

   Exercises* exercises = new Exercises();
   GlobalExercises = exercises;

   Dishes* dishes = new Dishes();
   GlobalDishes = dishes;


   Callendar callendar;
   qmlRegisterSingletonInstance("Callendar", 1, 0, "Callendar", &callendar);
   GlobalCallendar = &callendar;

   Elements elements;
   qmlRegisterSingletonInstance("Elements", 1, 0, "Elements", &elements);

   DayInfo dayInfo;
   qmlRegisterSingletonInstance("DayInfo", 1, 0, "DayInfo", &dayInfo);

   Home home;
   qmlRegisterSingletonInstance("Home", 1, 0, "Home", &home);

   engine.load(url);

   //Get current date overall
   /*std::time_t t = std::time(nullptr);
   std::tm *const pTInfo = std::localtime(&t);

   qDebug() << "Current year: "     << 1900 + pTInfo->tm_year;
   qDebug() << "Current tm_mon: "   << pTInfo->tm_mon;
   qDebug() << "Current tm_mday: "  << pTInfo->tm_mday;
   qDebug() << "Current tm_wday: "  << pTInfo->tm_wday;
   qDebug() << "Current tm_yday: "  << pTInfo->tm_yday;
   qDebug() << "Current tm_hour: "  << pTInfo->tm_hour;
   qDebug() << "Current tm_min: "   << pTInfo->tm_min;
   qDebug() << "Current tm_sec: "   << pTInfo->tm_sec;
   qDebug() << "Current tm_isdst: " << pTInfo->tm_isdst;*/

    return app.exec();
}
