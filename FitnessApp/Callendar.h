#ifndef CALLENDAR_H
#define CALLENDAR_H

#include <QObject>

class Callendar : public QObject
{
    Q_OBJECT
public:
    explicit Callendar(bool isFirstLaunch, QObject *parent = nullptr);

    //Doesn't work with a notifier, but is it needed though?
    Q_PROPERTY(int selectedYear MEMBER m_SelectedYear);
    Q_PROPERTY(int selectedMonth MEMBER m_SelectedMonth);
    Q_PROPERTY(QStringList daysList READ GetDaysList NOTIFY DaysListChanged);

    Q_INVOKABLE void updateLists();

signals:
    void DaysListChanged();

private:

//Q_PROPERTY variables
    QStringList m_YearList = {};
    QStringList m_MonthsList = {};

    QStringList GetDaysList();

    int m_SelectedYear = -1;
    int m_SelectedMonth = -1;

    int m_CurrentYear = -1;
    int m_CurrentMonth = -1;

//Q_PROPERTY variables --end

    struct DayInfo_t {
       int Id;
       int Year;
       int Month;
       int Day;
    };

    std::vector<DayInfo_t> m_DaysInfo;


//helpers
    int GetNumberOfDays(int month, int year);
};

extern Callendar* GlobalCallendar;

#endif // CALLENDAR_H
