import QtQuick 2.0
import QtQuick.Controls 2.14

import Callendar 1.0

Item{

   property int dayCount: 0
   property int rowCount: 0

   width: secondWindowWidth
   height: secondWindowHeight

   GridView {
      id: grid
      anchors.fill: parent

      anchors.topMargin: 100

      width: 700; height: 500

      cellWidth: 100; cellHeight: 100

      interactive: false

      model: Callendar.daysList
      delegate: Item{

         Rectangle{
            id: rect
            width: 100
            height: 100

            Text {
               id: date
               text: modelData//Callendar.daysList[index]
               anchors.leftMargin:  10
            }

            border.width: 1

            MouseArea {
               anchors.fill: parent

               onClicked: {
                  windowTitle = Callendar.daysList[index]
                  contentLoader.source = "DayInfoView.qml"
               }
            }
         }
      }

      highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
      focus: true
   }

   Component.onCompleted:
   {
      windowTitle = Callendar.selectedYear + "-" + Callendar.selectedMonth
      Callendar.updateLists()
   }
}
