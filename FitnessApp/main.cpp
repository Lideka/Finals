#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "Exercises.h"
#include "Dishes.h"

//classes connected to view qml files
#include "Callendar.h"
#include "Elements.h"
#include "DayInfo.h"

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

    engine.load(url);

    return app.exec();
}
