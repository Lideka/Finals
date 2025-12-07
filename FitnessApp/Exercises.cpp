#include "Exercises.h"

#include "Database.h"

std::vector<Exercises::Exercise> Exercises::m_ExercisesList = {};

Exercises* GlobalExercises = nullptr;

Exercises::Exercises(QObject *parent) : QObject(parent)
{
}

std::vector<Exercises::Exercise> Exercises::GetExercisesList()
{
   return m_ExercisesList;
}

void Exercises::AddExercise(QString name, int calories, QString description)
{
   Exercise newExercise;

   newExercise.Name = name;
   newExercise.Calories = calories;
   newExercise.Description = description;

   m_ExercisesList.push_back(newExercise);
}

void Exercises::RemoveExercise(int id)
{
   m_ExercisesList.erase(m_ExercisesList.begin() + id);
}

int Exercises::GetTotalCalories()
{
   int sum = 0;

   for(const Exercise &exercise : m_ExercisesList)
      sum += exercise.Calories;

   return sum;
}

void Exercises::UpdateExercisesList()
{
   GlobalDatabase->Open();
   QList<QVariantList> querryResult = GlobalDatabase->ExecuteSelectQuerry("Exercises", "Name, Description, Calories");
   GlobalDatabase->Close();

   m_ExercisesList.clear();

   for(const QVariantList &line : std::as_const(querryResult))
      AddExercise(line.at(0).toString(), line.at(1).toInt(), line.at(2).toString());
}
