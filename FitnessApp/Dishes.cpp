#include "Dishes.h"

#include "Database.h"

#include <QDebug>

std::vector<Dishes::Dish> Dishes::m_DishesList = {};

Dishes* GlobalDishes = nullptr;

Dishes::Dishes(QObject *parent) : QObject(parent)
{
}

std::vector<Dishes::Dish> Dishes::GetDishesList()
{
   return m_DishesList;
}

void Dishes::AddDish(QString name, int calories, QString description) //Only used in Elements.cpp
{
   Dish newDish;

   newDish.Name = name;
   newDish.Calories = calories;
   newDish.Description = description;

   m_DishesList.push_back(newDish);
}

void Dishes::RemoveDish(int id)
{
   m_DishesList.erase(m_DishesList.begin() + id);
}

int Dishes::GetTotalCalories() {
   int sum = 0;

   for(const Dish &dish : m_DishesList)
      sum += dish.Calories;

   return sum;
}

void Dishes::UpdateDishesList()
{
   GlobalDatabase->Open();
   QList<QVariantList> querryResult = GlobalDatabase->ExecuteSelectQuerry("Dishes", "Name, Description, Calories");
   GlobalDatabase->Close();

   m_DishesList.clear();

   for(const QVariantList &line : qAsConst(querryResult))
      AddDish(line.at(0).toString(), line.at(1).toInt(), line.at(2).toString());
}
