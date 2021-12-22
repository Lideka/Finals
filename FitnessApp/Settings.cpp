#include "Settings.h"

#include "Database.h"

Settings::Settings(QObject *parent) : QObject(parent)
{

}

void Settings::addElement(QString Name, QString Calories, QString Description)
{
   std::string Table;

   if(m_IsExerciseSelected)
      Table = "Exercises";
   else
      Table = "Dishes";

   QList<QVariantList> res = GlobalDatabase->ExecuteSelectQuerry(Table, "Id", "Name = " + Name.toStdString());

   //if(!res.empty())


}
