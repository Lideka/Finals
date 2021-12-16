#ifndef DISHES_H
#define DISHES_H

#include <QObject>

class Dishes : public QObject
{
   Q_OBJECT

public:
   explicit Dishes(QObject *parent = nullptr);

   struct Dish {
      QString Name;
      int Calories;
      QString Description;
   };

   std::vector<Dish> GetDishesList();

   void AddDish(QString name, int calories, QString description);
   void RemoveDish(int id);

   int GetTotalCalories();

   void UpdateDishesList();

private:

   static std::vector<Dish> m_DishesList;

signals:

};

extern Dishes* GlobalDishes;
#endif // DISHES_H
