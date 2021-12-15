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

   //Handle first launch variables
   if(isFirstLaunch)
   {
      GlobalDatabase->Open();
      GlobalDatabase->ExecuteCustomQuerry("UPDATE User SET FirstLaunchYear = " + std::to_string(m_CurrentYear));
      GlobalDatabase->ExecuteCustomQuerry("UPDATE User SET FirstLaunchMonth = " + std::to_string(m_CurrentMonth));
      GlobalDatabase->ExecuteCustomQuerry("UPDATE User SET FirstLaunchDay = " + std::to_string(m_CurrentDay));
      GlobalDatabase->Close();

      m_FirstLaunchYear = m_CurrentYear;
      m_FirstLaunchMonth = m_CurrentMonth;
      m_FirstLaunchDay = m_CurrentDay;
   }
   else
   {
      GlobalDatabase->Open();
      QList<QVariantList> res = GlobalDatabase->ExecuteSelectQuerry("User", "FirstLaunchYear, FirstLaunchMonth, FirstLaunchDay");
      GlobalDatabase->Close();

      assert(res.at(0).size() == 3);

      m_FirstLaunchYear = res.at(0).at(0).toInt();
      m_FirstLaunchMonth = res.at(0).at(1).toInt();
      m_FirstLaunchDay = res.at(0).at(2).toInt();
   }

   //By default, we show current year and month on first open
   m_SelectedYear = m_CurrentYear;
   m_SelectedMonth = m_CurrentMonth;

   UpdateSelectedMYString();
}

void Callendar::updateLists(){
   m_DaysInfo.clear();

   //Find which day of the week the first day of the month is
   std::tm time_in = { 0, 0, 0, 1, m_SelectedMonth - 1, m_SelectedYear - 1900 };
   std::time_t time_temp = std::mktime(&time_in);
   const std::tm *time_out = std::localtime(&time_temp);

   //Add empty days, to push the 1st day of the month to the correct week day
   for(int i = 0; i < time_out->tm_wday - 1; i++)
      m_DaysInfo.push_back({ m_SelectedYear, m_SelectedMonth, -1 });


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
      //Don't let the user go back further, than first launch month
      if(m_SelectedMonth == m_FirstLaunchMonth && m_SelectedYear == m_FirstLaunchYear)
         return;

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

   m_SelectedMonthString = MonthNames[m_SelectedMonth - 1];
   emit SelectedMonthStringChanged();
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
