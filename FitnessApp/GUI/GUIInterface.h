#ifndef GUIINTERFACE_H
#define GUIINTERFACE_H

#include <QObject>

class GUIInterface : public QObject
{
   Q_OBJECT
public:
   explicit GUIInterface(QObject *parent = nullptr);

   void ShowErrorPopup(std::string Message);

signals:
   void showErrorPopup(QString Message);

};

extern GUIInterface* GlobalGUI;

#endif // GUIINTERFACE_H
