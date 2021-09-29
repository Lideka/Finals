import QtQuick 2.0
import QtQuick.Controls 2.5

import DayInfo 1.0
import Elements 1.0

Item {

    width: secondWindowWidth
    height: secondWindowHeight

    Text {
        id: year

        y: 120

        anchors.horizontalCenter: parent.horizontalCenter

        text: qsTr("Metai: " + DayInfo.year)
    }

    Text {
        id: date

        anchors.top: year.bottom
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter

        text: qsTr("Data: " +  + DayInfo.date)
    }

    Text {
        id: calories

        anchors.top: date.bottom
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter

        text: qsTr("Kalorijų skirtumas: " + DayInfo.calories)
    }

    Item{
        id: lists

        width: secondWindowWidth - 200
        height: 200

        anchors.top: calories.bottom
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter

        Item {
            id: exercisesBox

            width: 200
            height: parent.height

            anchors.left: parent.left

            ListView {
                id: elementsList

                anchors.horizontalCenter: parent.horizontalCenter

                model: DayInfo.exercisesList

                width: parent.width
                height: parent.height

                clip: true

                delegate: Button {
                    width: exercisesBox.width
                    height: 50

                    text: DayInfo.exercisesList[index]

                    onClicked: {
                        Elements.selectedElement = DayInfo.getElementId(index, true)
                        Elements.isExercisesSelected = true


                        contentLoader.source = "ElementInfoView.qml"
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

        Item {
            id: dishesBox

            width: 200
            height: parent.height

            anchors.right: parent.right

            ListView {
                id: dishesList

                anchors.horizontalCenter: parent.horizontalCenter

                model: DayInfo.dishesList

                width: parent.width
                height: parent.height

                clip: true

                delegate: Button {
                    width: dishesBox.width
                    height: 50

                    text: DayInfo.dishesList[index]

                    onClicked: {
                        Elements.selectedElement = DayInfo.getElementId(index, false)
                        Elements.isDishesSelected = true

                        contentLoader.source = "ElementInfoView.qml"
                    }
                }
            }

            Rectangle {
                id: dishesBorders

                anchors.fill: parent

                border.width: 1

                color: 'transparent'
            }
        }

    }

    Button{
        id: addExercise

        y: lists.y + lists.height + 10
        anchors.left: lists.left

        width: 200

        text: "Pridėti pratimą"

        onClicked: {
            DayInfo.isAddSelected = true
            DayInfo.isExerciseSelected = true

            contentLoader.source = "DayAddRemoveView.qml"
        }
    }

    Button{
        id: removeExercise

        anchors.top: addExercise.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: addExercise.horizontalCenter

        width: 200

        text: "Ištrinti pratimą"

        onClicked: {
            DayInfo.isAddSelected = false
            DayInfo.isExerciseSelected = true

            contentLoader.source = "DayAddRemoveView.qml"
        }
    }

    Button{
        id: addDish

        anchors.right: lists.right
        y: lists.y + lists.height + 10

        width: 200

        text: "Pridėti patiekalą"

        onClicked: {
            DayInfo.isAddSelected = true
            DayInfo.isExerciseSelected = false

            contentLoader.source = "DayAddRemoveView.qml"
        }
    }

    Button{
        id: removeDish

        anchors.top: addDish.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: addDish.horizontalCenter

        width: 200

        text: "Ištrinti patiekalą"

        onClicked: {
            DayInfo.isAddSelected = false
            DayInfo.isExerciseSelected = false

            contentLoader.source = "DayAddRemoveView.qml"
        }
    }

    Component.onCompleted: DayInfo.updateValues()
}
