import QtQuick 2.0
import QtQuick.Controls 2.12

Popup {

   property string popupText
   property string popupTitle

   property bool wasYesPressed: false
   property bool wasNoPressed: false

   id: popup

   closePolicy: "CloseOnEscape"
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
         text: popupTitle

         anchors.centerIn: parent
      }
   }

   Text {
      id: text

      width: parent.width * 0.7

      anchors.centerIn: parent

      wrapMode: Text.Wrap
      horizontalAlignment: Text.AlignHCenter

      text: popupText
   }

   Item {
      width: ok.width * 2 + 20
      height: ok.height

      anchors.bottom: parent.bottom
      anchors.bottomMargin: 10
      anchors.horizontalCenter: parent.horizontalCenter

      Button {
         id: ok

         anchors.bottom: parent.bottom
         anchors.left: parent.left

         text: "OK"

         onClicked: {
            wasYesPressed = true
            popup.close()
         }
      }

      Button {
         id: cancel

         anchors.right: parent.right
         anchors.bottom: parent.bottom

         text: "Cancel"

         onClicked: {
            wasNoPressed = true
            popup.close()
         }
      }
   }


}
