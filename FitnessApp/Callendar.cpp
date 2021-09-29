#include "Callendar.h"

//#include <QtCharts>

//using namespace QtCharts;

#include <QDebug>

Callendar* GlobalCallendar = nullptr;

Callendar::Callendar(QObject *parent) : QObject(parent)
{
    //Listas užpildomas užsikrovus programai

    AddToList("2021", "01-01", {1, 1, 1, 0}, {1, 1, 1, 0});
    AddToList("2021", "01-02", {1, 1, 1, 0}, {1, 1, 1, 0});
    AddToList("2021", "01-03", {1, 1, 1, 0}, {1, 1, 1, 0});
    AddToList("2021", "01-04", {1, 1, 1, 0}, {1, 1, 1, 0});
    AddToList("2021", "01-05", {1, 1, 1, 0}, {1, 1, 1, 0});
    AddToList("2021", "01-06", {1, 1, 1, 0}, {1, 1, 1, 0});
    AddToList("2021", "01-07", {1, 1, 1, 0}, {1, 1, 1, 0});

    AddToList("2021", "01-08", {1, 1}, {1, 1, 0});
    AddToList("2021", "01-09", {1, 1}, {1, 1, 0});
    AddToList("2021", "01-10", {1, 1}, {1, 1, 0});
    AddToList("2021", "01-11", {1, 1}, {1, 1, 0});
    AddToList("2021", "01-12", {1, 1}, {1, 1, 0});
    AddToList("2021", "01-13", {1, 1}, {1, 1, 0});
    AddToList("2021", "01-14", {1, 1}, {1, 1, 0});

    AddToList("2021", "01-15", {1, 1, 0}, {1, 1, 0});
    AddToList("2021", "01-16", {1, 1, 0}, {1, 1, 0});
    AddToList("2021", "01-17", {1, 1, 0}, {1, 1, 0});
    AddToList("2021", "01-18", {1, 1, 0}, {1, 1, 0});
    AddToList("2021", "01-19", {1, 1, 0}, {1, 1, 0});
    AddToList("2021", "01-20", {1, 1, 0}, {1, 1, 0});
    AddToList("2021", "01-21", {1, 1, 0}, {1, 1, 0});

    AddToList("2021", "01-22", {1, 1, 0}, {1, 1, 0});
    AddToList("2021", "01-23", {1, 1, 0}, {1, 1, 0});
    AddToList("2021", "01-24", {1, 1, 0}, {1, 1, 0});
    AddToList("2021", "01-25", {1, 1, 0}, {1, 1, 0});
    AddToList("2021", "01-26", {1, 1, 0}, {1, 1, 0});
    AddToList("2021", "01-27", {1, 1, 0}, {1, 1, 0});
    AddToList("2021", "01-28", {1, 1, 0}, {1, 1, 0});

    AddToList("2021", "01-29", {1, 1, 0}, {1, 1, 0});
    AddToList("2021", "01-30", {1, 1, 0}, {1});
    AddToList("2021", "01-31", {1, 1, 0}, {1, 1, 0});
}

void Callendar::AddToList(QString year, QString date, std::vector<int> exercises, std::vector<int> dishes){

    day_t Day;
    Day.year = year;
    Day.date = date;
    Day.exercises = exercises;
    Day.dishes = dishes;

    m_daysList.push_back(Day);
}

void Callendar::AddElement(int index, bool isExerciseSelected){
    if(isExerciseSelected)
        m_daysList.at(m_selectedDay).exercises.push_back(index);
    else
        m_daysList.at(m_selectedDay).dishes.push_back(index);
}

void Callendar::RemoveElement(int index, bool isExerciseSelected){
    if(isExerciseSelected)
        m_daysList.at(m_selectedDay).exercises.erase(m_daysList.at(m_selectedDay).exercises.begin() + index);
    else
        m_daysList.at(m_selectedDay).dishes.erase(m_daysList.at(m_selectedDay).dishes.begin() + index);
}

void Callendar::GetDayInfo(QString &year, QString &date, std::vector<int> &exercises, std::vector<int> &dishes){
    year = m_daysList.at(m_selectedDay).year;
    date = m_daysList.at(m_selectedDay).date;
    exercises = m_daysList.at(m_selectedDay).exercises;
    dishes = m_daysList.at(m_selectedDay).dishes;

    qDebug() << year;
    qDebug() << date;
}

void Callendar::updateLists(){
    m_YearList.clear();
    m_DateList.clear();
    m_ExercisesCountList.clear();
    m_DishesCountList.clear();


    for(day_t day : m_daysList){
        m_YearList.push_back(day.year);
        m_DateList.push_back(day.date);
        m_ExercisesCountList.push_back(std::to_string(day.exercises.size()).c_str());
        m_DishesCountList.push_back(std::to_string(day.dishes.size()).c_str());
    }

    emit YearListChanged();
    emit DateListChanged();
    emit ExercisesCountListChanged();
    emit DishesCountListChanged();
}

int Callendar::SelectedDay(){
    return m_selectedDay;
}

