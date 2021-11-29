#ifndef DAYINFO_H
#define DAYINFO_H

#include <QObject>

class DayInfo : public QObject
{
    Q_OBJECT
public:
    explicit DayInfo(QObject *parent = nullptr);

    Q_PROPERTY(QString year MEMBER m_Year NOTIFY YearChanged);
    Q_PROPERTY(QString month MEMBER m_Month NOTIFY MonthChanged);
    Q_PROPERTY(QString calories MEMBER m_Calories NOTIFY CaloriesChanged);

    Q_PROPERTY(QStringList exercisesList MEMBER m_ExercisesList NOTIFY ExercisesListChanged);
    Q_PROPERTY(QStringList dishesList MEMBER m_DishesList NOTIFY DishesListChanged);

    Q_INVOKABLE void updateValues();

    Q_INVOKABLE int getElementId(int index, bool isExercises);

    //DayAddRemove
    Q_PROPERTY(bool isAddSelected MEMBER m_isAddSelected NOTIFY IsAddSelectedChanged);
    Q_PROPERTY(bool isExerciseSelected MEMBER m_isExerciseSelected NOTIFY IsExerciseSelectedChanged);

    Q_INVOKABLE void addElement(int index);
    Q_INVOKABLE void removeElement(int index);

signals:
    void YearChanged();
    void MonthChanged();
    void DayChanged();
    void CaloriesChanged();

    void ExercisesListChanged();
    void DishesListChanged();

    void IsAddSelectedChanged();
    void IsExerciseSelectedChanged();

private:
    QString m_Year;
    QString m_Month;
    QString m_Day;
    QString m_Calories;

    QStringList m_ExercisesList;
    QStringList m_DishesList;

    std::vector<int> m_exercisesIndexes;
    std::vector<int> m_dishesIndexes;

    bool m_isAddSelected;
    bool m_isExerciseSelected;



};

#endif // DAYINFO_H
