#ifndef DISHES_H
#define DISHES_H

#include <QObject>

class Dishes : public QObject
{
   Q_OBJECT

public:
   explicit Dishes(QObject *parent = nullptr);

   struct Dish{
      int Id;
      QString name;
      int calories;

      QString description;
   };

   std::vector<Dish> GetDishesList();

   void AddDish(QString name, int calories, QString description);
   void RemoveDish(int id);

   int GetTotalCalories();

   QString GetNameByIndex(int index);
   int GetCaloriesByIndex(int index);

private:

   static std::vector<Dish> m_DishesList;

signals:

};

extern Dishes* GlobalDishes;
#endif // DISHES_H
