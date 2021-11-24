#ifndef FASTING_H
#define FASTING_H

#include <QObject>

#include <QTime>

class Fasting : public QObject
{
   Q_OBJECT
public:
   explicit Fasting(QObject *parent = nullptr);

signals:

private:
   QTime m_CurrentTime;

};

#endif // FASTING_H
