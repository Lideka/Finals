import QtQuick 2.0
import QtQuick.Controls 2.14

import Callendar 1.0

import DayInfo 1.0

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

            color: date.text === "-1" ? "grey" : "transparent"

            Text {
               id: date
               text: modelData
               anchors.centerIn:  parent
               font.pixelSize: 25

               visible: text !== "-1"

               //Highlight the current day & grey out unavailable ones
               color: Callendar.currentYear === Callendar.selectedYear && Callendar.currentMonth === Callendar.selectedMonth && parseInt(text) === Callendar.currentDay ? "red" :
                         Callendar.firstLaunchYear === Callendar.selectedYear && Callendar.firstLaunchMonth === Callendar.selectedMonth && parseInt(text) < Callendar.firstLaunchDay ? "grey" :
                     "black"
            }

            border.width: 1

            MouseArea {
               anchors.fill: parent

               onClicked: {
                  Callendar.selectedDay = parseInt(Callendar.daysList[index])

                  windowTitle = Callendar.selectedMonthString + " " + Callendar.daysList[index] + ", " + Callendar.selectedYear
                  DayInfo.setCurrentDate(Callendar.selectedYear, Callendar.selectedMonth, Callendar.daysList[index])

                  contentLoader.source = "DayInfoView.qml"
               }
            }
         }
      }

      highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
      focus: true
   }

   Component.onCompleted: Callendar.updateLists()
}
