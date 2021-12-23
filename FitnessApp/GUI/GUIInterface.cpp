#include "GUIInterface.h"

GUIInterface* GlobalGUI = nullptr;

GUIInterface::GUIInterface(QObject *parent) : QObject(parent)
{

}

void GUIInterface::ShowMessagePopup(std::string Title, std::string Message)
{
   emit showMessagePopup(Title.c_str(), Message.c_str());
}

void GUIInterface::ShowErrorPopup(std::string Message)
{
   emit showMessagePopup("Error!", Message.c_str());
}
{
   qDebug() << "ShowYesNoPopup called";
   emit showYesNoPopup(Title.c_str(), Message.c_str());

   return true;
}
