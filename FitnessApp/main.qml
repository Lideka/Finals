import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.5

import Elements 1.0
import Callendar 1.0

Window {

   //Main window properties

   id: window

   width: defaultWidth
   height: defaultHeight

   minimumWidth: defaultWidth
   minimumHeight: defaultHeight

   visible: true //Apparently not visible by default

   title: qsTr("Fiznio aktyvumo planavimo irankis")

   //Main window properties --end

   //Local qml properties

   property int defaultWidth: 700
   property int defaultHeight: 700

   property int secondWindowWidth: window.width
   property int secondWindowHeight: window.height - bottomBox.height

   property string windowTitle: "Home"

   //ElementsView properties
   //property bool isExercisesSelected: false
   //property bool isDishesSelected: false

   //Local qml properties --end


   PopupWindow {
      id: popup
      width: 300
      height: 300
   }


   Loader {
      id: contentLoader

      x: 0
      y: 0

      source: "Home.qml"//"CallendarView.qml"
   }

   //Main window interface code

   Rectangle {
      id: topBar

      width: window.width
      height: 50

      color: "lightgreen"

      border.width: 2

      anchors.top: parent.top
      visible: true

      Text {
         id: title
         text: windowTitle

         anchors.centerIn: parent

         font.pointSize: 20
      }

      //Backward arrow to go back
      Image {
         //0.64 ratio, vertically bigger
         id: backArrow

         anchors.left: parent.left
         anchors.leftMargin: 10
         anchors.verticalCenter: parent.verticalCenter

         visible: contentLoader.source == "qrc:/DayInfoView.qml" ? true : false

         source: "Pictures/ArrowLeft.png"

         height: parent.height * 0.7
         width: height * 0.64

         MouseArea {
            anchors.fill: parent
            onClicked:  {
               contentLoader.source = "CallendarView.qml"
               windowTitle = Callendar.selectedMonthString + ", " + Callendar.selectedYear //Need to update every time, since qml is wonderful
            }
         }
      }


      //Forward/backward arrows for callendar
      Image {
         //0.64 ratio, vertically bigger
         id: arrowRight

         anchors.rightMargin: 10
         anchors.right: parent.right
         anchors.verticalCenter: parent.verticalCenter

         visible: contentLoader.source == "qrc:/CallendarView.qml" ? true : false

         source: "Pictures/ArrowRight.png"

         height: parent.height * 0.7
         width: height * 0.64

         MouseArea {
            anchors.fill: parent
            onClicked: {
               Callendar.arrowClicked(true)
               windowTitle = Callendar.selectedMonthString + ", " + Callendar.selectedYear //Need to update every time, since qml is wonderful
            }
         }
      }

      //0.64 ratio, vertically bigger
      Image {
         id: arrowLeft

         anchors.right: arrowRight.left
         anchors.rightMargin: 20
         anchors.verticalCenter: parent.verticalCenter

         visible: contentLoader.source == "qrc:/CallendarView.qml" ? true : false

         source: "Pictures/ArrowLeft.png"

         height: parent.height * 0.7
         width: height * 0.64

         MouseArea {
            anchors.fill: parent
            onClicked:  {
               Callendar.arrowClicked(false)
               windowTitle = Callendar.selectedMonthString + ", " + Callendar.selectedYear //Need to update every time, since qml is wonderful
            }
         }
      }
   }



   property variant buttons: [
      { name: "Namai",                                                        file: "Home.qml",          image: "Pictures/homeLogo.png" },
      { name: "Pasnikas",                                                     file: "Fasting.qml",       image: "Pictures/fastingLogo.png" },
      { name: Callendar.selectedMonthString + ", " + Callendar.selectedYear,  file: "CallendarView.qml", image: "Pictures/callendarLogo.png" },
      { name: "#4",                                                           file: "ElementsView.qml",  image: "Pictures/dishesLogo.png" },
      { name: "Nustatymai",                                                   file: "Settings.qml",      image: "Pictures/settingsLogo.png" }
   ];

   GridView {
      id: bottomBox

      width: window.width
      height: 100

      y: window.height - height //This is at the bottom (height of the window - this object height)

      cellWidth: window.width / buttons.length; cellHeight: 100

      interactive: false //?

      model: buttons

      delegate: Rectangle {
         width: parent.width / buttons.length
         height: parent.height

         Image {
            height: 80
            width: 76.5

            anchors.centerIn: parent

            source: buttons[index].image
         }

         MouseArea {
            anchors.fill: parent

            onClicked: {
               contentLoader.source = buttons[index].file
               windowTitle = buttons[index].name
            }
         }

         border.width: 1
      }
   }

}
