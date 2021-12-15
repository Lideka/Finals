#include "Elements.h"

#include <QDebug>

#include "Exercises.h"
#include "Dishes.h"

Elements::Elements(QObject *parent) : QObject(parent)
{
}

//Elements

void Elements::updateLists()
{
    QStringList exercisesNames;

    if(!GlobalExercises->GetExercisesList().empty())
        for(size_t i = 0; i < GlobalExercises->GetExercisesList().size(); i++)
            exercisesNames.push_back(GlobalExercises->GetExercisesList().at(i).Name);

    m_ExercisesNamesList = exercisesNames;
    emit ExercisesNamesListChanged();

    QStringList dishesNames;

    if(!GlobalDishes->GetDishesList().empty())
        for(size_t i = 0; i < GlobalDishes->GetDishesList().size(); i++)
            dishesNames.push_back(GlobalDishes->GetDishesList().at(i).name);

    m_DishesNamesList = dishesNames;
    emit DishesNamesListChanged();
}

//ElementInfo

void Elements::initializeElementsInfo()
{
    if(m_IsExercisesSelected){
        m_ElementName = m_ExercisesNamesList.at(m_SelectedElement);
        emit ElementNameChanged();

        m_ElementCalories = std::to_string(GlobalExercises->GetExercisesList().at(m_SelectedElement).Calories).c_str();
        emit ElementCaloriesChanged();

        m_ElementDescription = GlobalExercises->GetExercisesList().at(m_SelectedElement).Description;
        emit ElementDescriptionChanged();
    }
    else if(m_IsDishesSelected){
        m_ElementName = m_DishesNamesList.at(m_SelectedElement);
        emit ElementNameChanged();

        m_ElementCalories = std::to_string(GlobalDishes->GetDishesList().at(m_SelectedElement).calories).c_str();
        emit ElementCaloriesChanged();

        m_ElementDescription = GlobalDishes->GetDishesList().at(m_SelectedElement).description;
        emit ElementDescriptionChanged();
    }
}

//ElementAddRemove

void Elements::addElement(QString name, QString calories, QString description){

    if(name != "" && calories != "" && description != ""){

        if(m_IsExercisesSelected){
            for(size_t i = 0; i < GlobalExercises->GetExercisesList().size(); i++){
                if(GlobalExercises->GetExercisesList().at(i).Name == name){
                    qDebug() << "Elements::addElement this exercise name already exists";
                    return;
                }
            }

            GlobalExercises->AddExercise(name, calories.toInt(), description);
            qDebug() << "Elements::addElement pratimas sėkmingai pridėtas";
        }
        else if(m_IsDishesSelected){
            for(size_t i = 0; i < GlobalDishes->GetDishesList().size(); i++){
                if(GlobalDishes->GetDishesList().at(i).name == name){
                    qDebug() << "Elements::addElement this dish name already exists";
                    return;
                }
            }

            GlobalDishes->AddDish(name, calories.toInt(), description);
            qDebug() << "Elements::addElement patiekalas sėkmingai pridėtas";
        }
        else{
            qDebug() << "Elements::addElement element type not found";
        }
    }
    else{
        qDebug() << "Elements::addElement There can't be any empty fields";
    }
}

void Elements::removeElement(QString name){

    if(name == ""){
        qDebug() << "Elements::removeElement Būtina įvesti pavadinimą";
        return;
    }



    if(m_IsExercisesSelected){
        for(size_t i = 0; i < GlobalExercises->GetExercisesList().size(); i++){
            if(GlobalExercises->GetExercisesList().at(i).Name == name){
               GlobalExercises->RemoveExercise(i);
               qDebug() << "Pratimas sėkmingai ištrintas";
               return;
            }
        }
    }
    else if(m_IsDishesSelected){
        for(size_t i = 0; i < GlobalDishes->GetDishesList().size(); i++){
            if(GlobalDishes->GetDishesList().at(i).name == name){
               GlobalDishes->RemoveDish(i);
               qDebug() << "Patiekalas sėkmingai ištrintas";
               return;
            }
        }
    }
    else{
        qDebug() << "Elements::removeElement  elemento tipas nerastas";
        return;
    }

    qDebug() << "Elements::removeElement Įvestas pavadinimas nebuvo surastas";
}
