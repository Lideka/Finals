import QtQuick 2.0
import QtQuick.Controls 2.0

import DayInfo 1.0
import Elements 1.0

Item {

    width: secondWindowWidth
    height: secondWindowHeight

    Text{
        id: addText

        y: 120
        anchors.horizontalCenter: parent.horizontalCenter

        text: DayInfo.isExerciseSelected ? "Pasirinkite norimą pratimą:" : "Pasirinkite norimą patiekalą:"
    }

    //Add element
    Item {
        id: elementsBox

        width: 200
        height: 200

        anchors.top: addText.bottom
        anchors.topMargin: 5
        anchors.horizontalCenter: parent.horizontalCenter

        visible: DayInfo.isAddSelected

        ListView {
            id: addElementsList

            anchors.horizontalCenter: parent.horizontalCenter

            model: DayInfo.isExerciseSelected ? Elements.exercisesNamesList : Elements.dishesNamesList

            width: parent.width
            height: parent.height

            clip: true

            delegate: Button {
                width: elementsBox.width
                height: 50

                text: DayInfo.isExerciseSelected ? Elements.exercisesNamesList[index] : Elements.dishesNamesList[index]

                onClicked: {
                    DayInfo.addElement(index)
                    contentLoader.source = "DayInfoView.qml"
                }
            }
        }

        Rectangle {
            id: exercisesBorders

            anchors.fill: parent

            border.width: 1

            color: 'transparent'
        }
    }

    //Remove element
    Item {
        id: removeElementsBox

        width: 200
        height: 200

        anchors.top: addText.bottom
        anchors.topMargin: 5
        anchors.horizontalCenter: parent.horizontalCenter

        visible: !DayInfo.isAddSelected

        ListView {
            id: removeElementsList

            anchors.horizontalCenter: parent.horizontalCenter

            model: DayInfo.isExerciseSelected ? DayInfo.exercisesList : DayInfo.dishesList

            width: parent.width
            height: parent.height

            clip: true

            delegate: Button {
                width: elementsBox.width
                height: 50

                text: DayInfo.isExerciseSelected ? DayInfo.exercisesList[index] : DayInfo.dishesList[index]

                onClicked: {
                    DayInfo.removeElement(index)
                    contentLoader.source = "DayInfoView.qml"
                }
            }
        }

        Rectangle {
            id: exercisesBorders2

            anchors.fill: parent

            border.width: 1

            color: 'transparent'
        }
    }


}
