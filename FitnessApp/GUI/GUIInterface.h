#ifndef GUIINTERFACE_H
#define GUIINTERFACE_H

#include <QObject>

class GUIInterface : public QObject
{
   Q_OBJECT
public:
   explicit GUIInterface(QObject *parent = nullptr);

   void ShowMessagePopup(std::string Title, std::string Message);
   void ShowErrorPopup(std::string Message);
   bool ShowYesNoPopup(std::string Title, std::string Message);

signals:
   void showMessagePopup(QString Title, QString Message);
   void showYesNoPopup(QString Title, QString Message);

};

extern GUIInterface* GlobalGUI;

#endif // GUIINTERFACE_H
