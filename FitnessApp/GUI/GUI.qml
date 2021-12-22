import QtQuick 2.0
import QtQuick.Controls 2.14

import GUIInterface 1.0

Item {

   ErrorPopup {
      id: errorPopup
   }

   Connections {
      target: GUIInterface

      function onShowErrorPopup(text)
      {
         console.log("show error called")
         errorPopup.popupText = text
         errorPopup.open()
      }
   }

}
