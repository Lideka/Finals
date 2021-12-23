import QtQuick 2.0

Item {
   /*ListView {
      id: mainList

      anchors.horizontalCenter: parent.horizontalCenter
      anchors.top: exercisesTab.bottom

      width: parent.width
      height: secondWindowHeight - (topBar.height - 1) - exercisesTab.height - addButton.height

      model: DayInfo.modelData

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
               if(removalMode)
               {
                  if(removeCheckBox.checkState == Qt.Unchecked)
                     removeCheckBox.checkState = Qt.Checked
                  else if(removeCheckBox.checkState == Qt.Checked)
                     removeCheckBox.checkState = Qt.Unchecked
                  else //Should never come to this statement, unless tristate is set to true
                     removeCheckBox.checkState = Qt.Unchecked
               }
            }

         }

         CheckBox {
            id: removeCheckBox
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter

            visible: removalMode

            onCheckStateChanged: {
               if(checkState)
                  DayInfo.addToRemovalList(index)
               else
                  DayInfo.removeFromRemovalList(index)
            }

            onVisibleChanged: checkState = Qt.Unchecked
         }

      }

   }*/
}
