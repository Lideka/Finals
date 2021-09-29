#include "Exercises.h"

std::vector<Exercises::Exercise> Exercises::m_ExercisesList = {};

Exercises* GlobalExercises = nullptr;

Exercises::Exercises(QObject *parent) : QObject(parent)
{
    AddExercise("Atsilenkimai", 200, "Reikia daryti atsilenkimus sulenkus keliusReikia daryti atsilenkimus sulenkus keliusReikia daryti atsilenkimus sulenkus keliusReikia daryti atsilenkimus sulenkus keliusReikia daryti atsilenkimus sulenkus keliusReikia daryti atsilenkimus sulenkus keliusReikia daryti atsilenkimus sulenkus keliusReikia daryti atsilenkimus sulenkus keliusReikia daryti atsilenkimus sulenkus keliusReikia daryti atsilenkimus sulenkus keliusReikia daryti atsilenkimus sulenkus keliusReikia daryti atsilenkimus sulenkus keliusReikia daryti atsilenkimus sulenkus keliusReikia daryti atsilenkimus sulenkus keliusReikia daryti atsilenkimus sulenkus keliusReikia daryti atsilenkimus sulenkus kelius");
    AddExercise("Pritūpimai", 300, "Pilnai pritūpti sulenkiant kelius");
    AddExercise("Bėgimas", 600, "2 kilometrų bėgimas vidutiniu tempu");
}

std::vector<Exercises::Exercise> Exercises::GetExercisesList(){
    return m_ExercisesList;
}

void Exercises::AddExercise(QString name, int calories, QString description)
{
    Exercise newExercise;

    newExercise.name = name;
    newExercise.calories = calories;
    newExercise.description = description;

    m_ExercisesList.push_back(newExercise);
}

void Exercises::RemoveExercise(int id)
{
     m_ExercisesList.erase(m_ExercisesList.begin() + id);
}

int Exercises::GetTotalCalories(){
    int sum = 0;

    for(Exercise exercise : m_ExercisesList)
        sum += exercise.calories;

    return sum;
}

QString Exercises::GetNameByIndex(int index){
    return m_ExercisesList.at(index).name;
}

int Exercises::GetCaloriesByIndex(int index){
    return m_ExercisesList.at(index).calories;
}
