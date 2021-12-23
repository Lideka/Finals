#include "Settings.h"

#include "Database.h"
#include "GUIInterface.h"

Settings::Settings(QObject *parent) : QObject(parent)
{

}

void Settings::addElement(QString Name, QString Calories, QString Description)
{
   //Check if exercise with the same name already exists
   std::string Table;
   std::string Element;

   if(m_IsExerciseSelected)
   {
      Table = "Exercises";
      Element = "exercise";
   }
   else
   {
      Table = "Dishes";
      Element = "dish";
   }

   GlobalDatabase->Open();
   QList<QVariantList> res = GlobalDatabase->ExecuteSelectQuerry(Table, "Id", "Name = \"" + Name.toStdString() + "\"");

   if(!res.empty())
   {
      GlobalDatabase->Close();
      GlobalGUI->ShowErrorPopup("Exercise with this name already exists!");
      return;
   }

   assert(GlobalDatabase->ExecuteInsertQuerry(Table, "Name, Calories, Description", "\"" + Name.toStdString() + "\", \"" + Calories.toStdString() + "\", \"" + Description.toStdString() + "\""));
   GlobalDatabase->Close();

   GlobalGUI->ShowMessagePopup("Success!", "Selected " + Element + " added successfuly!");
}
