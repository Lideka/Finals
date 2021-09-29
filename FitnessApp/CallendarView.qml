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

            model: Callendar.yearList
            delegate: Item{

                Rectangle{
                    id: rect
                    width: 100
                    height: 100

                    Text {
                        id: date
                        text: Callendar.yearList[index] + "-" + Callendar.dateList[index]
                        anchors.leftMargin:  10
                    }

                    Text {
                        id: dayInfo

                        anchors.bottom: parent.bottom

                        text: "Pratimai: " + Callendar.exercisesCountList[index] + "\n" + "Patiekalai: " + Callendar.dishesCountList[index]
                    }

                    border.width: 1

                    MouseArea{
                        anchors.fill: parent

                        onClicked: {
                            contentLoader.source = "DayInfoView.qml"

                            windowTitle = Callendar.yearList[index] + "-" + Callendar.dateList[index]

                            Callendar.selectedDay = index
                        }
                    }
                }

            }

            highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
            focus: true
        }

    Component.onCompleted: Callendar.updateLists()

}
