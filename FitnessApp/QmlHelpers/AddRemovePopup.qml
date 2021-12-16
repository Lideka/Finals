import QtQuick 2.0
import QtQuick.Controls 2.12

import Callendar 1.0
import DayInfo 1.0

Popup {
   property bool isExercisesSelected: true
   property string backDirection

   function openPopup(isExercisesSelectedArg, backDirectionArg) {
      isExercisesSelected = isExercisesSelectedArg
      backDirection = backDirectionArg

      popup.open()
   }


   id: popup


   Rectangle {
      id: popupBar

      width: parent.width
      height: 50

      color: "lightgreen"

      border.width: 2

      anchors.top: parent.top
      anchors.left: parent.left
      visible: true

      Text {
         id: title

         anchors.centerIn: parent

         font.pointSize: 20

         text: {
            if (isExercisesSelected)
               return "Add exercises to: " + Callendar.selectedMonthString + " " + Callendar.selectedDay
            else
               return "Add dishes to: "    + Callendar.selectedMonthString + " " + Callendar.selectedDay
         }
      }

      //Backward arrow to go back
      Image {
         //0.64 ratio, vertically bigger
         id: backArrow

         anchors.left: parent.left
         anchors.leftMargin: 10
         anchors.verticalCenter: parent.verticalCenter

         source: "../Pictures/ArrowLeft.png"

         height: parent.height * 0.7
         width: height * 0.64

         MouseArea {
            anchors.fill: parent
            onClicked: {
               contentLoader.source = backDirection
               popup.close()
            }
         }
      }


      //Forward arrow to execute action
      Image {
         //0.64 ratio, vertically bigger
         id: confirmArrow

         anchors.right: parent.right
         anchors.rightMargin: 10
         anchors.verticalCenter: parent.verticalCenter

         source: "../Pictures/ArrowRight.png"

         height: parent.height * 0.7
         width: height * 0.64

         MouseArea {
            anchors.fill: parent
            onClicked: {
               DayInfo.addSelectedElements()
               contentLoader.source = backDirection
               popup.close()
            }
         }
      }
   }


   ListView {
      id: mainList

      anchors.horizontalCenter: parent.horizontalCenter
      anchors.top: popupBar.bottom

      width: parent.width
      height: parent.height - (popupBar.height - 1)

      model: DayInfo.popupModelData

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
               if(addCheckBox.checkState == Qt.Unchecked)
                  addCheckBox.checkState = Qt.Checked
               else if(addCheckBox.checkState == Qt.Checked)
                  addCheckBox.checkState = Qt.Unchecked
               else //Should never come to this statement, unless tristate is set to true
                  addCheckBox.checkState = Qt.Unchecked
            }
         }

         CheckBox {
            id: addCheckBox
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter

            onCheckStateChanged: {
               if(checkState)
                  DayInfo.addToAdditionList(modelData)
               else
                  DayInfo.removeFromAdditionList(modelData)
            }

            Component.onCompleted: checkState = Qt.Unchecked
         }

      }

   }

}
