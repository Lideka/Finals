import QtQuick 2.0

Item {
   width: secondWindowWidth
   height: secondWindowHeight

   Text {
      id: mainText

      anchors.centerIn: parent

      text: "Made by: Augustas Kazanavičius"
   }

   Component.onCompleted: {
      console.log("Component.onCompleted")
      backArrowDir = "Settings.qml"
   }

}
