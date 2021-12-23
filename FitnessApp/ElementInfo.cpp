#include "ElementInfo.h"

#include "Database.h"

ElementInfo* GlobalElementInfo = nullptr;

ElementInfo::ElementInfo(QObject *parent) : QObject(parent)
{

}


void ElementInfo::SetElement(bool isExercise, std::string name)
{
   qDebug() << "ElementInfo::SetElement: " << name.c_str();
   std::string Table;

   if(isExercise)
      Table = "Exercises";
   else
      Table = "Dishes";

   GlobalDatabase->Open();
   QList<QVariantList> res = GlobalDatabase->ExecuteSelectQuerry(Table, "Calories, Description", "Name = \"" + name + "\"");
   GlobalDatabase->Close();

   assert(!res.empty());
   assert(res.at(0).size() == 2);

   m_Name = name.c_str();
   emit NameChanged();

   m_Calories = res.at(0).at(0).toInt();
   emit CaloriesChanged();

   m_Description = res.at(0).at(1).toString();
   emit DescriptionChanged();
}
