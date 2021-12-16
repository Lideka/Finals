#ifndef DAYINFO_H
#define DAYINFO_H

#include <QObject>

class DayInfo : public QObject
{
   Q_OBJECT
public:
   explicit DayInfo(QObject *parent = nullptr);

   Q_PROPERTY(QStringList modelData READ GetModelData NOTIFY ModelDataChanged);

   Q_PROPERTY(bool isExercisesSelected READ GetIsExercisesSelected WRITE SetIsExercisesSelected NOTIFY IsExercisesSelectedChanged);

   Q_INVOKABLE void setCurrentDate(int Year, int Month, int Day);
   Q_INVOKABLE void updateValues();

   //Popup properties
   Q_PROPERTY(QStringList popupModelData READ GetPopupModelData NOTIFY PopupModelDataChanged);

   Q_INVOKABLE void addToAdditionList(QString name);

signals:
   void ModelDataChanged();

   void IsExercisesSelectedChanged();

   void PopupModelDataChanged();

private:

   struct Element {
      QString Name;
      QString Description;
      int Calories;
   };

   //Q_PROPERTY variables and methods

   QStringList m_ModelData;
   QStringList GetModelData();

   bool m_IsExercisesSelected = true;
   bool GetIsExercisesSelected();
   void SetIsExercisesSelected(bool value);

   QStringList m_PopupModelData;
   QStringList GetPopupModelData();

   //Q_PROPERTY variables and methods --end

   int m_SelectedYear;
   int m_SelectedMonth;
   int m_SelectedDay;

   std::vector<Element> m_ExercisesList;
   std::vector<Element> m_DishesList;


   QStringList m_ElementsAdditionList;
};

#endif // DAYINFO_H
