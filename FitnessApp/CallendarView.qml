import QtQuick 2.0
import QtQuick.Controls 2.14

import Callendar 1.0

Item{

   property int dayCount: 0
   property int rowCount: 0

   width: secondWindowWidth
   height: secondWindowHeight

   GridView {
      id: weekDays

      y: topBar.height //Bad solution but work

      anchors.horizontalCenter: parent.horizontalCenter

      width: 700
      height: 20

      model: Callendar.weekDays

      //Unsure why it doesn't work if I put text here directly D:
      delegate: Item{

         width: 100
         height: 20

            Text {
               id: weekDay
               text: modelData
               anchors.centerIn:  parent
               font.pixelSize: 17
            }
      }

   }

   GridView {
      id: grid

      anchors.top: weekDays.bottom

      width: 700; height: 500

      cellWidth: 100; cellHeight: 100

      interactive: false

      visible: true

      model: Callendar.daysList
      delegate: Item{

         Rectangle{
            id: rect
            width: 100
            height: 100

            Text {
               id: date
               text: modelData//Callendar.daysList[index]
               anchors.centerIn:  parent
               font.pixelSize: 25

               //Highlight the current day
               color: index + 1 === Callendar.currentDay ? "red" : "black"
            }

            border.width: 1

            MouseArea {
               anchors.fill: parent

               onClicked: {
                  windowTitle = Callendar.daysList[index]
                  contentLoader.source = "DayInfoView.qml"
                  console.log(weekDays.height)
               }
            }
         }
      }

      highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
      focus: true
   }

   Component.onCompleted: Callendar.updateLists()
}
