#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>

class Settings : public QObject
{
   Q_OBJECT
public:
   explicit Settings(QObject *parent = nullptr);

   Q_PROPERTY(bool isExerciseSelected MEMBER m_IsExerciseSelected NOTIFY IsExerciseSelectedChanged);

   Q_INVOKABLE void addElement(QString Name, QString Calories, QString Description);

signals:
   void IsExerciseSelectedChanged();

private:
   bool m_IsExerciseSelected;
};

#endif // SETTINGS_H
