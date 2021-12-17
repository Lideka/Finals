import QtQuick 2.0
import QtQuick.Controls 2.5

import DayInfo 1.0
import Elements 1.0

import Callendar 1.0

import "QmlHelpers"

Item {

   property bool removalMode: false

   width: secondWindowWidth
   height: secondWindowHeight

   Button {
      id: exercisesTab

      y: topBar.height - 1 //-1 so the border doesn't seem too thicc
      anchors.left: parent.left

      width: secondWindowWidth / 2

      text: "Exercises"

      flat: !DayInfo.isExercisesSelected //Highlight button, if it's pressed
      onClicked: DayInfo.isExercisesSelected = true

      //Borders
      Rectangle {
         anchors.fill: parent
         color: "transparent"

         border.color: "black"
         border.width: 1
      }
   }

   Button {
      id: dishesTab

      y: topBar.height - 1 //-1 so the border doesn't seem too thicc
      anchors.right: parent.right

      width: secondWindowWidth / 2

      text: "Dishes"

      flat: DayInfo.isExercisesSelected //Highlight button, if it's pressed
      onClicked: DayInfo.isExercisesSelected = false

      //Borders
      Rectangle {
         anchors.fill: parent
         color: "transparent"

         border.color: "black"
         border.width: 1
      }
   }


   ListView {
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

   }

   Button {
      id: addButton

      anchors.left: parent.left
      anchors.bottom: parent.bottom

      width: secondWindowWidth / 2

      text: removalMode ? "Remove" : "Add"

      onClicked: {
         if(!removalMode)
            popup1.openPopup(DayInfo.isExercisesSelected, "qrc:/DayInfoView.qml")
         else
         {
            DayInfo.removeSelectedElements()
            removalMode = !removalMode
         }
      }
   }

   Button {
      id: removeButton

      anchors.right: parent.right
      anchors.bottom: parent.bottom

      width: secondWindowWidth / 2

      text: removalMode ? "Cancel" : "Remove"

      onClicked: removalMode = !removalMode
   }


   AddRemovePopup {
      id: popup1


      //Borders
      Rectangle {
         anchors.fill: parent
         color: "transparent"

         border.color: "black"
         border.width: 1
      }

      width: parent.width
      height: parent.height
   }

    Component.onCompleted: {
       DayInfo.updateValues()
       DayInfo.isExercisesSelected = true
    }
}
