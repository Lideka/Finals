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

      interactive: false

      anchors.horizontalCenter: parent.horizontalCenter

      width: secondWindowWidth
      height: 20

      cellWidth: secondWindowWidth / 7; cellHeight: 20

      model: Callendar.weekDays

      //Unsure why it doesn't work if I put text here directly D:
      delegate: Item {

         width: secondWindowWidth / 7
         height: 20

            Text {
               id: weekDay
               text: modelData
               anchors.centerIn:  parent
               font.pixelSize: 14
            }
      }

   }

   GridView {
      id: grid

      anchors.top: weekDays.bottom

      width: secondWindowWidth; height: (secondWindowWidth / 7) * 6

      cellWidth: secondWindowWidth / 7; cellHeight: secondWindowWidth / 7

      interactive: false

      visible: true

      model: Callendar.daysList
      delegate: Item{

         Rectangle{
            id: rect
            width: grid.cellWidth
            height: grid.cellHeight

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
                  //Do not open day info, if the day is greyed out
                  if(Callendar.firstLaunchYear === Callendar.selectedYear && Callendar.firstLaunchMonth === Callendar.selectedMonth && parseInt(Callendar.daysList[index]) < Callendar.firstLaunchDay)
                     return;

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
