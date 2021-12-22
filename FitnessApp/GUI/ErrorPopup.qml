import QtQuick 2.0
import QtQuick.Controls 2.12

Popup {

   property string popupText

   id: popup

   padding: 0

   anchors.centerIn: parent

   width: secondWindowWidth * 0.4
   height: secondWindowHeight * 0.3


   Rectangle {
      id: topBar

      width: parent.width
      height: 40

      color: "lightgreen"

      border.width: 2

      anchors.top: parent.top
      anchors.horizontalCenter: parent.horizontalCenter

      Text {
         id: title
         text: "Error!"

         anchors.centerIn: parent
      }
   }

   Text {
      id: text

      anchors.centerIn: parent

      text: popupText
   }

   Button {
      id: ok

      anchors.bottom: parent.bottom
      anchors.bottomMargin: 10
      anchors.horizontalCenter: parent.horizontalCenter

      text: "OK"

      onClicked: popup.close()
   }

}
