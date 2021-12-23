#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "Database.h"

//classes connected to view qml files
#include "GUIInterface.h"
#include "Home.h"
#include "Fasting.h"
#include "Callendar.h"
#include "DayInfo.h"
#include "Settings.h"
#include "ElementInfo.h"

#include "Elements.h"
#include "Exercises.h"
#include "Dishes.h"

#include <chrono> //tests

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

   std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
   std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

   qDebug() << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]";//tests
   qDebug() << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]";//tests

   QString dbPath;

#ifdef WIN32
   dbPath = "I:/Projects/Finals/FitnessApp/Lib/Database/Database.db";

#elif ANDROID
   //Copy db file to android (not complete yet)
   QString source = "I:/Projects/Finals/FitnessApp/Lib/Database/Database.db";
   QString dest = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
   QString fullDest =  dest + "/Database.db";

   if(QFile::exists(fullDest))
   {
      //assert(QFile::remove(dest));
   }

   QDir DestDir(fullDest);
   qDebug() << QFile::copy(source, fullDest);

   qDebug() << "Naujas path: "  << fullDest << " exists: " << DestDir.exists();
   dbPath = fullDest;
#endif


   //Create and connect global main database
   Database db(dbPath.toStdString());
   GlobalDatabase = &db;

   //Check if the app is launched for the first time
   GlobalDatabase->Open();
   QList<QVariantList> Name = GlobalDatabase->ExecuteSelectQuerry("User", "Name");
   GlobalDatabase->Close();



   //Use this where needed
   bool isFirstLaunch = Name.empty();
   qDebug() << "Is first launch: " << isFirstLaunch;


   //Create global qml controllers
   Exercises* exercises = new Exercises();
   GlobalExercises = exercises;

   Dishes* dishes = new Dishes();
   GlobalDishes = dishes;

   GUIInterface guiInterface;
   qmlRegisterSingletonInstance("GUIInterface", 1, 0, "GUIInterface", &guiInterface);
   GlobalGUI = &guiInterface;

   Callendar callendar(isFirstLaunch);
   qmlRegisterSingletonInstance("Callendar", 1, 0, "Callendar", &callendar);
   GlobalCallendar = &callendar;

   Elements elements;
   qmlRegisterSingletonInstance("Elements", 1, 0, "Elements", &elements);

   DayInfo dayInfo;
   qmlRegisterSingletonInstance("DayInfo", 1, 0, "DayInfo", &dayInfo);

   Home home;
   qmlRegisterSingletonInstance("Home", 1, 0, "Home", &home);

   Fasting fasting;
   qmlRegisterSingletonInstance("Fasting", 1, 0, "Fasting", &fasting);

   Settings settings;
   qmlRegisterSingletonInstance("Settings", 1, 0, "Settings", &settings);

   ElementInfo elementInfo;
   qmlRegisterSingletonInstance("ElementInfo", 1, 0, "ElementInfo", &elementInfo);
   GlobalElementInfo = &elementInfo;

   //Create global qml controllers --end

   engine.load(url);

   return app.exec();
}
