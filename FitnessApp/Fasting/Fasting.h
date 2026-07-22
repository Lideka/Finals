#ifndef FASTING_H
#define FASTING_H

#include <QObject>

#include <QTime>

class Fasting : public QObject
{
   Q_OBJECT
public:
   explicit Fasting(QObject *parent = nullptr);

   Q_INVOKABLE void saveFirst();
   Q_INVOKABLE void saveSecond();

   Q_INVOKABLE void execute();

signals:

private:
   QTime m_CurrentTime;

   std::chrono::steady_clock::time_point m_FirstPoint;
   std::chrono::steady_clock::time_point m_SecondPoint;
};

#endif // FASTING_H
