#include "Settings.h"

#include "Database.h"
#include "GUIInterface.h"
#include "ElementInfo.h"

#include "Exercises.h"
#include "Dishes.h"

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


QStringList Settings::GetRemoveGlobalElementModelData()
{
   GlobalExercises->UpdateExercisesList();
   GlobalDishes->UpdateDishesList();

   QStringList retval = {};

   if(m_IsExerciseSelected)
   {
      std::vector<Exercises::Exercise> AllExercises = GlobalExercises->GetExercisesList();

      for(const Exercises::Exercise &exercise : AllExercises)
         retval.push_back(exercise.Name);
   }
   else
   {
      std::vector<Dishes::Dish> AllDishes = GlobalDishes->GetDishesList();

      for(const Dishes::Dish &dish : AllDishes)
         retval.push_back(dish.Name);
   }

   return retval;
}

void Settings::setShowInfoElement(int index)
{
   GlobalElementInfo->SetElement(m_IsExerciseSelected, GetRemoveGlobalElementModelData().at(index).toStdString());
}
