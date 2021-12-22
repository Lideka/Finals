#include "GUIInterface.h"

GUIInterface* GlobalGUI = nullptr;

GUIInterface::GUIInterface(QObject *parent) : QObject(parent)
{

}

void GUIInterface::ShowErrorPopup(std::string Message)
{
   emit showErrorPopup(Message.c_str());
}
