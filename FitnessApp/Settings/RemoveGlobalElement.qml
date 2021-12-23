import QtQuick 2.0
import QtQuick.Controls 2.5

import Settings 1.0
import DayInfo 1.0

Item {
   width: secondWindowWidth
   height: secondWindowHeight


   ListView {
      id: mainList


      y: topBar.height - 1 //-1 so the border doesn't seem too thicc

      anchors.horizontalCenter: parent.horizontalCenter

      width: secondWindowWidth
      height: secondWindowHeight - (topBar.height - 1)

      model: Settings.removeGlobalElementModelData

      clip: true

      delegate: Item {
         width: parent.width
         height: 80

         Rectangle {
            width: parent.width
            height: parent.height

            color: "transparent"

            border.width: 1
            border.color: "red"

            Text {
               anchors.centerIn: parent

               text: modelData
            }
         }

         MouseArea {
            anchors.fill: parent

            onClicked: {
               Settings.setShowInfoElement(index)
               isRemovalMode = true
               contentLoader.source = "../ShowElementInfo.qml" //Because we're currently in Settings folder
            }

         }
      }

   }
}
