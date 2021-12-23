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

   Q_INVOKABLE void setShowInfoElement(int index);

   //Popup properties
   Q_PROPERTY(QStringList popupModelData READ GetPopupModelData NOTIFY PopupModelDataChanged);

   Q_INVOKABLE void addToAdditionList(QString name);
   Q_INVOKABLE void removeFromAdditionList(QString name);
   Q_INVOKABLE void addSelectedElements();

   Q_INVOKABLE void addToRemovalList(int index);
   Q_INVOKABLE void removeFromRemovalList(int index);
   Q_INVOKABLE void removeSelectedElements();

signals:
   void ModelDataChanged();

   void IsExercisesSelectedChanged();

   void PopupModelDataChanged();

private:

   //This is ok only while Exercises and Dishes have the same properties
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

   //Add popup variables

   QStringList m_ElementsAdditionList;
   QList<int> m_ElementsIndexRemovalList;
};

#endif // DAYINFO_H
