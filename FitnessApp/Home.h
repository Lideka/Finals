#ifndef HOME_H
#define HOME_H

#include <QObject>

class Home : public QObject
{
   Q_OBJECT
public:
   explicit Home(QObject *parent = nullptr);

   Q_PROPERTY(int waterAmmount MEMBER m_WaterAmmount NOTIFY waterAmmountChanged);

signals:
   void waterAmmountChanged();

private:
   int m_WaterAmmount = 2; //1 water ammount = 250ml

};

#endif // HOME_H
