#ifndef CALLENDAR_H
#define CALLENDAR_H

#include <QObject>

class Callendar : public QObject
{
   Q_OBJECT
public:
   explicit Callendar(bool isFirstLaunch, QObject *parent = nullptr);

   Q_PROPERTY(int selectedYear MEMBER m_SelectedYear NOTIFY SelectedYearChanged);
   Q_PROPERTY(int selectedMonth MEMBER m_SelectedMonth NOTIFY SelectedMonthChanged);

   Q_PROPERTY(int currentYear MEMBER m_CurrentYear NOTIFY CurrentYearChanged);
   Q_PROPERTY(int currentMonth MEMBER m_CurrentMonth NOTIFY CurrentMonthChanged);
   Q_PROPERTY(int currentDay MEMBER m_CurrentDay NOTIFY CurrentDayChanged);

   Q_PROPERTY(int firstLaunchYear MEMBER m_FirstLaunchYear NOTIFY FirstLaunchYearChanged);
   Q_PROPERTY(int firstLaunchMonth MEMBER m_FirstLaunchMonth NOTIFY FirstLaunchMonthChanged);
   Q_PROPERTY(int firstLaunchDay MEMBER m_FirstLaunchDay NOTIFY FirstLaunchDayChanged);


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

   void FirstLaunchYearChanged();
   void FirstLaunchMonthChanged();
   void FirstLaunchDayChanged();

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

   int m_FirstLaunchYear = -1;
   int m_FirstLaunchMonth = -1;
   int m_FirstLaunchDay = -1;


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
