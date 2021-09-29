#include "Dishes.h"

std::vector<Dishes::Dish> Dishes::m_DishesList = {};

Dishes* GlobalDishes = nullptr;

Dishes::Dishes(QObject *parent) : QObject(parent)
{
    AddDish("Kotletas", 500, "Gaminamas iš mėsos, apvalios formos");
    AddDish("Plovas", 450, "Gaminamas iš mėsos ir ryžių, be padažo");
    AddDish("Meduolis", 300, "Cukrinis desertas");
    AddDish("Sultys", 150, "Cido sultys iš Norfos");
    AddDish("Vanduo", 10, "Dienai reikalingas vandens kiekis");
}

std::vector<Dishes::Dish> Dishes::GetDishesList(){
    return m_DishesList;
}

void Dishes::AddDish(QString name, int calories, QString description)
{
    Dish newDish;

    newDish.name = name;
    newDish.calories = calories;
    newDish.description = description;

    m_DishesList.push_back(newDish);
}

void Dishes::RemoveDish(int id)
{
     m_DishesList.erase(m_DishesList.begin() + id);
}

int Dishes::GetTotalCalories(){
    int sum = 0;

    for(Dish dish : m_DishesList)
        sum += dish.calories;

    return sum;
}


QString Dishes::GetNameByIndex(int index){
    return m_DishesList.at(index).name;
}

int Dishes::GetCaloriesByIndex(int index){
    return m_DishesList.at(index).calories;
}
