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


      //Backward arrow to go back
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

      model: DayInfo.popupModelData //[1, 2, 3]

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

         CheckBox {
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter

            visible: removalMode
         }

      }

   }

}
