#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>

class Settings : public QObject
{
   Q_OBJECT
public:
   explicit Settings(QObject *parent = nullptr);

   //AddGlobalElement properties and methods
   Q_PROPERTY(bool isExerciseSelected MEMBER m_IsExerciseSelected NOTIFY IsExerciseSelectedChanged);

   Q_INVOKABLE void addElement(QString Name, QString Calories, QString Description);

   //RemoveGlobalElement properties and methods
   Q_PROPERTY(QStringList removeGlobalElementModelData READ GetRemoveGlobalElementModelData NOTIFY RemoveGlobalElementModelDataChanged);

   Q_INVOKABLE void setShowInfoElement(int index);

signals:
   void IsExerciseSelectedChanged();

   void RemoveGlobalElementModelDataChanged();

private:
   bool m_IsExerciseSelected;

   QStringList GetRemoveGlobalElementModelData();

};

#endif // SETTINGS_H
