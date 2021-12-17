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

      std::string Querry = "SELECT " + TableName + ".Name, " + TableName + ".Description, " + TableName + ".Calories, " + Table2Name + ".Count ";
      Querry += "FROM " + TableName + " ";
      Querry += "INNER JOIN Days ON (Days.Year = " + std::to_string(m_SelectedYear) + ") & (Days.Month = " + std::to_string(m_SelectedMonth) + ") & (Days.Day = " + std::to_string(m_SelectedDay) + ") ";
      Querry += "INNER JOIN " + Table2Name + " ON " + Table2Name + ".DayId = Days.Id ";
      Querry += "WHERE " + TableName + ".Id = " + Table2Name + "." + Table2RowName;

      QList<QVariantList> res;

      GlobalDatabase->Open();
      GlobalDatabase->ExecuteCustomQuerry(Querry, &res, 4);
      GlobalDatabase->Close();


      //Fill the appropriate list
      CurrentList->clear();

      for(const QVariantList &line : qAsConst(res)) //Some stuff just to avoid warnings
      {
         assert(line.size() == 4); //Must match ammount of rows, that we've extracted

         for(int i = 0; i < line.at(3).toInt(); i++) //4th element is count. Tells us how many elements there are
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

   GlobalDatabase->Close();

   for(const QString &name : qAsConst(m_ElementsAdditionList))
   {
      int count = 0;

      for(const QString &existingName : GetModelData())
         if(name == existingName)
            count++;

      if(count > 0)
      {
         //Element already exists, increment the count
         Querry = "UPDATE " + InsertTableName + " SET Count = " + std::to_string(count+1) + " ";
         Querry += "WHERE " + InsertTableName + ".Id = ( ";
         Querry += "SELECT " + InsertTableName + ".Id FROM " + InsertTableName + " ";
         Querry += "INNER JOIN Days ON (Days.Year = " + std::to_string(m_SelectedYear) + ") & (Days.Month = " + std::to_string(m_SelectedMonth) + ") & (Days.Day = " + std::to_string(m_SelectedDay) + ") ";
         Querry += "INNER JOIN " + ElementsTableName + " ON " + ElementsTableName + ".Name = \"" + name.toStdString() + "\" ";
         Querry += "WHERE (" + InsertTableName + ".DayId = Days.Id) & (" + InsertTableName + ".ExerciseId = " + ElementsTableName + ".Id)";
         Querry += ")";
      }
      else if(count == 0)
      {
         //Element doesn't exist yet, add it
         Querry = "INSERT INTO " + InsertTableName + " (DayId, " + InsertTableColumnName + ", Count) ";
         Querry += "SELECT Days.Id, " + ElementsTableName + ".Id, 1 FROM Days ";
         Querry += "INNER JOIN " + ElementsTableName + " ON " + ElementsTableName + ".Name = \"" + name.toStdString() + "\" ";
         Querry += "WHERE (Days.Year = " + std::to_string(m_SelectedYear) + ") & (Days.Month = " + std::to_string(m_SelectedMonth) + ") & (Days.Day = " + std::to_string(m_SelectedDay) + ")";
      }
      else
         assert(false); //Unknown scenario


      //Need to open/close database before each time calling this, since we update values and we close db there
      GlobalDatabase->Open();
      GlobalDatabase->ExecuteCustomQuerry(Querry);
      GlobalDatabase->Close();
      updateValues();
   }

   GlobalDatabase->Close();
   m_ElementsAdditionList.clear();
}


void DayInfo::addToRemovalList(int index)
{
   m_ElementsIndexRemovalList.push_back(index);
}

void DayInfo::removeFromRemovalList(int index)
{
   m_ElementsIndexRemovalList.removeAll(index);
}

void DayInfo::removeSelectedElements()
{
   QStringList ElementsNameToRemove = {};

   //Find names in accordance with provided indexes
   for(int index : qAsConst(m_ElementsIndexRemovalList))
      ElementsNameToRemove.push_back(GetModelData().at(index));


   //Tables and row names will differ for exercises and dishes
   std::string Table1Name;
   std::string Table1ColumnName;
   std::string ElementsTableName;

   if(GetIsExercisesSelected())
   {
      Table1Name = "ExercisesInDays";
      Table1ColumnName = "ExerciseId";
      ElementsTableName = "Exercises";
   }
   else
   {
      Table1Name = "DishesInDays";
      Table1ColumnName = "DishId";
      ElementsTableName = "Dishes";
   }

   std::string Querry;


   for(const QString &name : qAsConst(ElementsNameToRemove))
   {
      int count = 0;

      for(const QString &existingName : GetModelData())
         if(name == existingName)
            count++;

      if(count > 1)
      {
         //Substract the count
         Querry = "UPDATE " + Table1Name + " SET Count = " + std::to_string(count-1) + " ";
      }
      else if(count == 1)
      {
         //Delete the record
         Querry = "DELETE FROM " + Table1Name + " ";
      }
      else
         assert(false); //Unknown scenario


      Querry += "WHERE " + Table1Name + ".Id = ( ";
      Querry += "SELECT " + Table1Name + ".Id FROM " + Table1Name + " ";
      Querry += "INNER JOIN Days ON (Days.Year = " + std::to_string(m_SelectedYear) + ") & (Days.Month = " + std::to_string(m_SelectedMonth) + ") & (Days.Day = " + std::to_string(m_SelectedDay) + ") ";
      Querry += "INNER JOIN " + ElementsTableName + " ON " + ElementsTableName + ".Name = \"" + name.toStdString() + "\" ";
      Querry += "WHERE (" + Table1Name + ".DayId = Days.Id) & (" + Table1Name + ".ExerciseId = " + ElementsTableName + ".Id)";
      Querry += ")";

      GlobalDatabase->Open();
      GlobalDatabase->ExecuteCustomQuerry(Querry);
      GlobalDatabase->Close();

      updateValues();
   }

   m_ElementsIndexRemovalList.clear();
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
