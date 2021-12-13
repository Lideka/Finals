#include "Callendar.h"

#include "Database.h"

//#include <QtCharts>

//using namespace QtCharts;

#include <QDebug>
#include <ctime>

Callendar* GlobalCallendar = nullptr;

Callendar::Callendar(bool isFirstLaunch, QObject *parent) : QObject(parent)
{
   //Find current year and month
   std::time_t t = std::time(nullptr);
   std::tm *const pTInfo = std::localtime(&t);

   m_CurrentYear = 1900 + pTInfo->tm_year;
   m_CurrentMonth = pTInfo->tm_mon + 1;
   m_CurrentDay = pTInfo->tm_mday;

   //By default, we show current year and month on first open
   m_SelectedYear = m_CurrentYear;
   m_SelectedMonth = m_CurrentMonth;

   UpdateSelectedMYString();
}

void Callendar::updateLists(){
   m_DaysInfo.clear();

   int daysInCurrentMonth = GetNumberOfDays(m_SelectedMonth, m_SelectedYear);

   for(int i = 1; i <= daysInCurrentMonth; i++)
      m_DaysInfo.push_back({ m_SelectedYear, m_SelectedMonth, i });

   emit DaysListChanged();
}

void Callendar::arrowClicked(bool isRight)
{
   //Check if left or right arrow was clicked
   if(isRight)
   {
      if(m_SelectedMonth == 12)
      {
         m_SelectedYear++;
         m_SelectedMonth = 1;

         emit SelectedYearChanged();
      }
      else
         m_SelectedMonth++;

   }
   else
   {
      if(m_SelectedMonth == 1)
      {
         m_SelectedYear--;
         m_SelectedMonth = 12;

         emit SelectedYearChanged();
      }
      else
         m_SelectedMonth--;
   }

   emit SelectedMonthChanged();

   UpdateSelectedMYString();
   updateLists();
}

QStringList Callendar::GetWeekDays()
{
   return {
      "Mon",
      "Tue",
      "Wed",
      "Thu",
      "Fri",
      "Sat",
      "Sun"
   };
}

QStringList Callendar::GetDaysList()
{
   QStringList retval;

   for (DayInfo_t dayInfo : m_DaysInfo)
   {
      if(dayInfo.Year == m_SelectedYear && dayInfo.Month == m_SelectedMonth)
         retval.push_back(QString::number(dayInfo.Day));
   }

   return retval;
}

void Callendar::UpdateSelectedMYString()
{
   QString MonthNames[] = {
     "January",
      "February",
      "March",
      "April",
      "May",
      "June",
      "July",
      "August",
      "September",
      "October",
      "November",
      "December",
   };

   m_SelectedMYString = MonthNames[m_SelectedMonth - 1] + ", " + QString::number(m_SelectedYear);
   emit SelectedMYChanged();
}

//Helpers
int Callendar::GetNumberOfDays(int month, int year)
{
   //leap year condition, if month is 2
   if( month == 2)
   {
      if((year%400==0) || (year%4==0 && year%100!=0))
         return 29;
      else
         return 28;
   }
   //months which has 31 days
   else if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 ||month == 10 || month==12)
      return 31;
   else
      return 30;
}
