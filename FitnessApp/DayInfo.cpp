#include "DayInfo.h"
#include "Callendar.h"

#include "Exercises.h"
#include "Dishes.h"

DayInfo::DayInfo(QObject *parent) : QObject(parent)
{

}

void DayInfo::updateValues()
{
    //Reset the values
    m_isAddSelected = false;
    m_isExerciseSelected = false;
    emit IsAddSelectedChanged();
    emit IsExerciseSelectedChanged();

    int exerciseCalories = 0;
    int dishCalories = 0;

    GlobalCallendar->GetDayInfo(m_Year, m_Date, m_exercisesIndexes, m_dishesIndexes);

    //Year and date get's updated immediately
    emit YearChanged();
    emit DateChanged();

    m_ExercisesList.clear();
    m_DishesList.clear();

    if(!m_exercisesIndexes.empty()){
        for(int i : m_exercisesIndexes){
            m_ExercisesList.push_back(GlobalExercises->GetNameByIndex(i));
            exerciseCalories += GlobalExercises->GetCaloriesByIndex(i);
        }
    }
    emit ExercisesListChanged();

    if(!m_dishesIndexes.empty()){
        for(int i : m_dishesIndexes){
            m_DishesList.push_back(GlobalDishes->GetNameByIndex(i));
            dishCalories += GlobalDishes->GetCaloriesByIndex(i);
        }
    }
    emit DishesListChanged();


    m_Calories = std::to_string(dishCalories - exerciseCalories).c_str();
    emit CaloriesChanged();
}

int DayInfo::getElementId(int index, bool isExercises){
    if(isExercises){
        return m_exercisesIndexes.at(index);
    }
    else{
        return m_dishesIndexes.at(index);
    }
}

void DayInfo::addElement(int index){
    GlobalCallendar->AddElement(index, m_isExerciseSelected);
}

void DayInfo::removeElement(int index){
    if(m_isExerciseSelected)
        GlobalCallendar->RemoveElement( m_exercisesIndexes.at(index), true );
    else
        GlobalCallendar->RemoveElement( m_dishesIndexes.at(index), false );
}



