import QtQuick 2.0
import QtQuick.Controls 2.14

Item {

   width: secondWindowWidth
   height: secondWindowHeight


   property variant menu: [
      { text: "Add global elements",         file: "Settings/AddGlobalElement.qml" },
      { text: "Remove global elements",      file: "Settings/RemoveGlobalElement.qml" },
      { text: "About us",                    file: "Settings/AboutUs.qml" }
   ];


   ListView {
      id: mainList

      anchors.horizontalCenter: parent.horizontalCenter
      y: topBar.height - 1

      width: secondWindowWidth
      height: secondWindowHeight

      model: menu

      clip: true

      delegate: Button {
         width: parent.width
         height: 70

         text: menu[index].text

         onClicked: {
            contentLoader.source = menu[index].file
         }

         //Border
         Rectangle {
            anchors.fill: parent
            color: "transparent"

            border.color: "black"
            border.width: 1
         }
      }
   }

}
