#ifndef ELEMENTS_H
#define ELEMENTS_H

#include <QObject>

class Elements : public QObject
{
    Q_OBJECT
public:
    explicit Elements(QObject *parent = nullptr);

    //Elements view
    Q_PROPERTY(QStringList exercisesNamesList MEMBER m_ExercisesNamesList NOTIFY ExercisesNamesListChanged);
    Q_PROPERTY(QStringList dishesNamesList MEMBER m_DishesNamesList NOTIFY DishesNamesListChanged);

    Q_PROPERTY(int selectedElement MEMBER m_SelectedElement NOTIFY SelectedElementChanged);
    Q_PROPERTY(bool isExercisesSelected MEMBER m_IsExercisesSelected NOTIFY IsExercisesSelectedChanged)
    Q_PROPERTY(bool isDishesSelected MEMBER m_IsDishesSelected NOTIFY IsDishesSelectedChanged)

    Q_INVOKABLE void updateLists();


    //ElementsInfo view
    Q_PROPERTY(QString elementName MEMBER m_ElementName NOTIFY ElementNameChanged);
    Q_PROPERTY(QString elementCalories MEMBER m_ElementCalories NOTIFY ElementCaloriesChanged);
    Q_PROPERTY(QString elementDescription MEMBER m_ElementDescription NOTIFY ElementDescriptionChanged);

    Q_INVOKABLE void initializeElementsInfo();

    //ElementsAddRemove view
    Q_PROPERTY(bool isAddSelected MEMBER m_IsAddSelected NOTIFY IsAddSelectedChanged);
    Q_PROPERTY(bool isRemoveSelected MEMBER m_IsRemoveSelected NOTIFY IsRemoveSelectedChanged);

    Q_INVOKABLE void addElement(QString name, QString calories, QString description);
    Q_INVOKABLE void removeElement(QString name);


signals:
    void ExercisesNamesListChanged();
    void DishesNamesListChanged();
    void SelectedElementChanged();
    void IsExercisesSelectedChanged();
    void IsDishesSelectedChanged();

    void ElementNameChanged();
    void ElementCaloriesChanged();
    void ElementDescriptionChanged();

    void IsAddSelectedChanged();
    void IsRemoveSelectedChanged();

private:
    QStringList m_ExercisesNamesList = {};
    QStringList m_DishesNamesList = {};
    int m_SelectedElement;
    bool m_IsExercisesSelected = false;
    bool m_IsDishesSelected = false;

    QString m_ElementName;
    QString m_ElementCalories;
    QString m_ElementDescription;

    bool m_IsAddSelected = false;
    bool m_IsRemoveSelected = false;

};

#endif // ELEMENTS_H
