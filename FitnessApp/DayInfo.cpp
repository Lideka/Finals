#include "DayInfo.h"
#include "Callendar.h"

#include "Exercises.h"
#include "Dishes.h"

#include "Database.h"


DayInfo::DayInfo(QObject *parent) : QObject(parent)
{
}

void DayInfo::setCurrentDate(int Year, int Month, int Day)
{
   m_SelectedYear = Year;
   m_SelectedMonth = Month;
   m_SelectedDay = Day;
}

void DayInfo::updateValues()
{
   //Tables and row names will differ for exercises and dishes
   std::string TableName;
   std::string Table2Name;
   std::string Table2RowName;

   std::vector<Element> *CurrentList;

   //Find selected day exercises and dishes
   for(int i = 0; i < 2; i++)
   {
      if(i == 0) //Exercises first, then dishes
      {
         TableName = "Exercises";
         Table2Name = "ExercisesInDays";
         Table2RowName = "ExerciseId";

         CurrentList = &m_ExercisesList;
      }
      else
      {
         TableName = "Dishes";
         Table2Name = "DishesInDays";
         Table2RowName = "DishId";

         CurrentList = &m_DishesList;
      }

      std::string Querry = "SELECT " + TableName + ".Name, " + TableName + ".Description, " + TableName + ".Calories ";
      Querry += "FROM " + TableName + " ";
      Querry += "INNER JOIN Days ON (Days.Year = " + std::to_string(m_SelectedYear) + ") & (Days.Month = " + std::to_string(m_SelectedMonth) + ") & (Days.Day = " + std::to_string(m_SelectedDay) + ") ";
      Querry += "INNER JOIN " + Table2Name + " ON " + Table2Name + ".DayId = Days.Id ";
      Querry += "WHERE " + TableName + ".Id = " + Table2Name + "." + Table2RowName;

      QList<QVariantList> res;

      GlobalDatabase->Open();
      GlobalDatabase->ExecuteCustomQuerry(Querry, &res, 3);
      GlobalDatabase->Close();


      //Fill the appropriate list
      CurrentList->clear();

      for(const QVariantList &line : qAsConst(res)) //Some stuff just to avoid warnings
      {
         assert(line.size() == 3); //Must match ammount of rows, that we've extracted

         CurrentList->push_back({ line.at(0).toString(), line.at(1).toString(), line.at(2).toInt() });
      }


      //Initialize model list with exercises
      m_ModelData.clear();

      for(const Element &element : m_ExercisesList)
         m_ModelData.push_back(element.Name);

      emit ModelDataChanged();
   }

   GlobalExercises->UpdateExercisesList();
   GlobalDishes->UpdateDishesList();

   emit PopupModelDataChanged();
}


//AddPopup Q_PROPERTY variables and methods

void DayInfo::addToAdditionList(QString name)
{
   m_ElementsAdditionList.push_back(name);
}

void DayInfo::removeFromAdditionList(QString name)
{
   m_ElementsAdditionList.removeAll(name); //We can use removeAll, since dish/exerc names are unique
}

void DayInfo::addSelectedElements()
{
   //Tables and row names will differ for exercises and dishes
   std::string InsertTableName;
   std::string InsertTableColumnName;
   std::string ElementsTableName;

   if(GetIsExercisesSelected())
   {
      InsertTableName = "ExercisesInDays";
      InsertTableColumnName = "ExerciseId";
      ElementsTableName = "Exercises";
   }
   else
   {
      InsertTableName = "DishesInDays";
      InsertTableColumnName = "DishId";
      ElementsTableName = "Dishes";
   }

   std::string Querry;

   GlobalDatabase->Open();

   QList<QVariantList> res = GlobalDatabase->ExecuteSelectQuerry("Days", "Id", "(Year = " + std::to_string(m_SelectedYear) + ") & (Month = " + std::to_string(m_SelectedMonth) + ") & (Day = " + std::to_string(m_SelectedDay) + ")");

   //Check if the day exists in the database. Add it if it doesnt.
   if(res.empty())
   {
      GlobalDatabase->ExecuteInsertQuerry("Days", "Year, Month, Day", std::to_string(m_SelectedYear) + ", " + std::to_string(m_SelectedMonth) + ", " + std::to_string(m_SelectedDay));
   }
   else
   {
      assert(res.size() == 1 && res.at(0).size() == 1);
   }

   for(const QString &name : qAsConst(m_ElementsAdditionList))
   {
      Querry = "INSERT INTO " + InsertTableName + " (DayId, " + InsertTableColumnName + ") ";
      Querry += "SELECT Days.Id, " + ElementsTableName + ".Id FROM Days ";
      Querry += "INNER JOIN " + ElementsTableName + " ON " + ElementsTableName + ".Name = \"" + name.toStdString() + "\" ";
      Querry += "WHERE (Days.Year = " + std::to_string(m_SelectedYear) + ") & (Days.Month = " + std::to_string(m_SelectedMonth) + ") & (Days.Day = " + std::to_string(m_SelectedDay) + ")";

      GlobalDatabase->ExecuteCustomQuerry(Querry);
   }

   GlobalDatabase->Close();
   m_ElementsAdditionList.clear();
}


/*void DayInfo::addToRemovalList(QString name)
{
   m_ElementsRemovalList.push_back(name);
}

void DayInfo::removeFromRemovalList(QString name)
{
   m_ElementsRemovalList.removeAll(name); //We can use removeAll, since dish/exerc names are unique
}*/

void DayInfo::removeSelectedElements()
{

}


//AddPopup Q_PROPERTY variables and methods --end


//Q_PROPERTY variables and methods

QStringList DayInfo::GetModelData()
{
   return m_ModelData;
}

bool DayInfo::GetIsExercisesSelected()
{
   return m_IsExercisesSelected;
}

void DayInfo::SetIsExercisesSelected(bool value)
{
   if(value != m_IsExercisesSelected)
   {
      m_IsExercisesSelected = value;

      emit IsExercisesSelectedChanged();

      //Update model list accordingly
      std::vector<Element> *SelectedList;

      if(m_IsExercisesSelected)
         SelectedList = &m_ExercisesList;
      else
         SelectedList = &m_DishesList;

      m_ModelData.clear();

      for(const Element &element : *SelectedList)
         m_ModelData.push_back(element.Name);

      emit ModelDataChanged();


      //Update popup model accordingly
      emit PopupModelDataChanged();
   }
}


QStringList DayInfo::GetPopupModelData()
{
   QStringList retval = {};

   if(m_IsExercisesSelected)
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

//Q_PROPERTY variables and methods --end
