#ifndef ELEMENTINFO_H
#define ELEMENTINFO_H

#include <QObject>

class ElementInfo : public QObject
{
   Q_OBJECT
public:
   explicit ElementInfo(QObject *parent = nullptr);

   Q_PROPERTY(QString name MEMBER m_Name NOTIFY NameChanged);
   Q_PROPERTY(int calories MEMBER m_Calories NOTIFY CaloriesChanged);
   Q_PROPERTY(QString description MEMBER m_Description NOTIFY DescriptionChanged);

   Q_INVOKABLE void removeCurrentElement();


   void SetElement(bool isExercise, std::string name);

signals:
   void NameChanged();
   void CaloriesChanged();
   void DescriptionChanged();

private:
   QString m_Name;
   int m_Calories;
   QString m_Description;

   bool m_IsCurrentElementExercise;

};

extern ElementInfo* GlobalElementInfo;

#endif // ELEMENTINFO_H
