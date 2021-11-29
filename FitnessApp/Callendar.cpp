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

   //By default, we show current year and month on first open
   m_SelectedYear = m_CurrentYear;
   m_SelectedMonth = m_CurrentMonth;
}

void Callendar::updateLists(){
   m_YearList.clear();
   m_MonthsList.clear();

   m_DaysInfo.clear();

   int daysInCurrentMonth = GetNumberOfDays(m_SelectedMonth, m_SelectedYear);

   for(int i = 1; i <= daysInCurrentMonth; i++)
      m_DaysInfo.push_back({ m_SelectedYear, m_SelectedMonth, i });

   emit DaysListChanged();
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
