#include "Fasting.h"

#include <chrono>
#include <QDebug>

Fasting::Fasting(QObject *parent) : QObject(parent)
{

}

void Fasting::saveFirst()
{
   m_FirstPoint = std::chrono::steady_clock::now();
}

void Fasting::saveSecond()
{
   m_SecondPoint = std::chrono::steady_clock::now();
}


void Fasting::execute()
{
   qDebug() << std::chrono::duration_cast<std::chrono::seconds>(m_SecondPoint - m_FirstPoint).count();
}
