#ifndef CALLENDAR_H
#define CALLENDAR_H

#include <QObject>

class Callendar : public QObject
{
   Q_OBJECT
public:
   explicit Callendar(bool isFirstLaunch, QObject *parent = nullptr);

   //Doesn't work with a notifier, but is it needed though?
   Q_PROPERTY(int selectedYear MEMBER m_SelectedYear NOTIFY SelectedYearChanged);
   Q_PROPERTY(int selectedMonth MEMBER m_SelectedMonth NOTIFY SelectedMonthChanged);
   Q_PROPERTY(int currentYear MEMBER m_CurrentYear NOTIFY CurrentYearChanged);
   Q_PROPERTY(int currentMonth MEMBER m_CurrentMonth NOTIFY CurrentMonthChanged);
   Q_PROPERTY(int currentDay MEMBER m_CurrentDay NOTIFY CurrentDayChanged);

   Q_PROPERTY(QString selectedMYString MEMBER m_SelectedMYString NOTIFY SelectedMYChanged);

   Q_PROPERTY(QStringList weekDays READ GetWeekDays NOTIFY WeekDaysChanged);
   Q_PROPERTY(QStringList daysList READ GetDaysList NOTIFY DaysListChanged);

   Q_INVOKABLE void updateLists();

   Q_INVOKABLE void arrowClicked(bool isRight);

signals:
   void SelectedYearChanged();
   void SelectedMonthChanged();
   void CurrentYearChanged();
   void CurrentMonthChanged();
   void CurrentDayChanged();

   void SelectedMYChanged();

   void WeekDaysChanged();
   void DaysListChanged();

private:

   //Q_PROPERTY variables

   int m_SelectedYear = -1;
   int m_SelectedMonth = -1;

   QStringList GetWeekDays();
   QStringList GetDaysList();

   //Q_PROPERTY variables --end

   int m_CurrentYear = -1;
   int m_CurrentMonth = -1;
   int m_CurrentDay = -1;

   QString m_SelectedMYString;

   struct DayInfo_t {
      int Year;
      int Month;
      int Day;
   };
   std::vector<DayInfo_t> m_DaysInfo;

   void UpdateSelectedMYString();
   //helpers
   int GetNumberOfDays(int month, int year);
};

extern Callendar* GlobalCallendar;

#endif // CALLENDAR_H
