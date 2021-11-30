#include "Exercises.h"

#include "Database.h"

std::vector<Exercises::Exercise> Exercises::m_ExercisesList = {};

Exercises* GlobalExercises = nullptr;

Exercises::Exercises(QObject *parent) : QObject(parent)
{
   GlobalDatabase->Open();
   QList<QVariantList> querryResult = GlobalDatabase->ExecuteSelectQuerry("Exercises", "Name, Description, Calories");
   GlobalDatabase->Close();

   for(QVariantList line : querryResult)
   {
      AddExercise(line.at(0).toString(), line.at(1).toInt(), line.at(2).toString());
   }

   qDebug() << GetExercisesList().size() << " exercises loaded";

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
