import QtQuick 2.0
import QtQuick.Controls 2.14

import GUIInterface 1.0

Item {

   //Grey popup background
   Rectangle {
      id: background

      color: "grey"
      opacity: 0.7

      anchors.fill: parent

      visible: false

      //To prevent user from being able to click outside popup
      MouseArea {
         anchors.fill: parent
      }
   }


   //Popups & theyr methods

   //Message popup
   MessagePopup {
      id: messagePopup

      onClosed: background.visible = false //Remove background when popup closes
   }

   Connections {
      target: GUIInterface

      function onShowMessagePopup(title, text)
      {
         showMessagePopup(title, text)
      }
   }

   //Additional declaration, so we could use it in qml also
   function showMessagePopup(title, text)
   {
      messagePopup.popupTitle = title
      messagePopup.popupText = text
      messagePopup.open()
      background.visible = true //Show background

   }
}
