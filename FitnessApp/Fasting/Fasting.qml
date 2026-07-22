import QtQuick 2.0
import QtQuick.Controls 2.14

import Fasting 1.0

Item {

   width: secondWindowWidth
   height: secondWindowHeight

   Button {
      id: first

      y: topBar.height + 20
      anchors.horizontalCenter: parent.horizontalCenter

      text: "Set 1"

      onClicked: Fasting.saveFirst()
   }

   Button {
      id: second

      anchors.top: first.bottom
      anchors.topMargin: 20
      anchors.horizontalCenter: parent.horizontalCenter

      text: "Set 2"

      onClicked: Fasting.saveSecond()
   }

   Button {
      id: third

      anchors.top: second.bottom
      anchors.topMargin: 20
      anchors.horizontalCenter: parent.horizontalCenter

      text: "Go"

      onClicked: Fasting.execute()
   }

}
