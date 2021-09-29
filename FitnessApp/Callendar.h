#ifndef CALLENDAR_H
#define CALLENDAR_H

#include <QObject>

class Callendar : public QObject
{
    Q_OBJECT

private:
    QStringList m_YearList = {};
    QStringList m_DateList = {};

    QStringList m_ExercisesCountList = {};
    QStringList m_DishesCountList = {};

    int m_selectedDay = 0;

    struct day_t {
        QString year;
        QString date;
        int calories;

        std::vector<int> dishes;      //Nurodo vieta, kokie patiekalai paimti iš globalaus listo
        std::vector<int> exercises;   //Nurodo vieta, kokie pratimai paimti iš globalaus listo
    };
    std::vector<day_t> m_daysList;

public:
    explicit Callendar(QObject *parent = nullptr);

    Q_PROPERTY(QStringList yearList MEMBER m_YearList NOTIFY YearListChanged);
    Q_PROPERTY(QStringList dateList MEMBER m_DateList NOTIFY DateListChanged);

    Q_PROPERTY(QStringList exercisesCountList MEMBER m_ExercisesCountList NOTIFY ExercisesCountListChanged);
    Q_PROPERTY(QStringList dishesCountList MEMBER m_DishesCountList NOTIFY DishesCountListChanged);

    Q_PROPERTY(int selectedDay MEMBER m_selectedDay NOTIFY SelectedDayChanged);

    Q_INVOKABLE void updateLists();

    void AddToList(QString year, QString date, std::vector<int> exercises, std::vector<int> dishes);

    void AddElement(int index, bool isExerciseSelected);
    void RemoveElement(int index, bool isExerciseSelected);

    void GetDayInfo(QString &year, QString &date, std::vector<int> &exercises, std::vector<int> &dishes);

    int SelectedDay();

signals:
    void YearListChanged();
    void DateListChanged();

    void ExercisesCountListChanged();
    void DishesCountListChanged();

    void SelectedDayChanged();

};

extern Callendar* GlobalCallendar;

#endif // CALLENDAR_H
