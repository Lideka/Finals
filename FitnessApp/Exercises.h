#ifndef EXERCISES_H
#define EXERCISES_H

#include <QObject>

class Exercises : public QObject
{
    Q_OBJECT


public:
    explicit Exercises(QObject *parent = nullptr);

    struct Exercise{
        QString name;
        int calories;

        QString description;
    };

    std::vector<Exercise> GetExercisesList();

    void AddExercise(QString name, int calories, QString description);
    void RemoveExercise(int id);

    int GetTotalCalories();

    QString GetNameByIndex(int index);
    int GetCaloriesByIndex(int index);

private:

    static std::vector<Exercise> m_ExercisesList;

signals:

};

extern Exercises* GlobalExercises;

#endif // EXERCISES_H
