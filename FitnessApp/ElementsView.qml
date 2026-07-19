import QtQuick 2.0
import QtQuick.Controls 2.5

import Elements 1.0

Item {
    width: secondWindowWidth
    height: secondWindowHeight

    Item{
        width: 337.232
        height: 150

        anchors.centerIn: parent
        anchors.horizontalCenter: parent.horizontalCenter

        visible: !Elements.isExercisesSelected && !Elements.isDishesSelected

        Rectangle{
            id: exercisesButton

            width: 150
            height: 143.616

            anchors.left: parent.left

            Image{
                id: exercisesIcon

                width: 148
                height: 141.616

                anchors.centerIn: parent

                source: "Pictures/exercisesLogo.png"
            }

            MouseArea{
                anchors.fill: parent

                onClicked: {
                    Elements.isExercisesSelected = true
                    windowTitle = "Exercises in the system"
                }
            }

            border.width: 1
        }

        Rectangle{
            id: dishesButton

            width: 150
            height: 143.616

            anchors.right: parent.right

            Image{
                id: notesIcon

                anchors.centerIn: parent

                width: 148
                height: 141.616

                source: "Pictures/dishesLogo.png"
            }

            MouseArea{
                anchors.fill: parent

                onClicked: {
                    Elements.isDishesSelected = true
                    windowTitle = "Dishes in the system"

                }
            }

            border.width: 1
        }

    }


    Text {
        id: tableName

        y: 150
        anchors.horizontalCenter: parent.horizontalCenter

        text: Elements.isExercisesSelected ? "Exercises:" : "Dishes:"

        visible: Elements.isExercisesSelected || Elements.isDishesSelected
    }

    Item {
        id: elementsBox

        width: 200
        height: 200

        anchors.top: tableName.bottom
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter

        visible: Elements.isExercisesSelected || Elements.isDishesSelected

        ListView {
            id: elementsList

            anchors.horizontalCenter: parent.horizontalCenter

            model: Elements.isExercisesSelected ? Elements.exercisesNamesList : Elements.dishesNamesList

            width: parent.width
            height: parent.height

            clip: true

            delegate: Button {
                width: elementsBox.width
                height: 50

                text: Elements.isExercisesSelected ? Elements.exercisesNamesList[index] : Elements.dishesNamesList[index]

                onClicked: {
                    Elements.selectedElement = index

                    navigateTo("ElementInfoView.qml")
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

    Button {
        id: addElementButton

        anchors.top: elementsBox.bottom
        anchors.topMargin: 20

        anchors.horizontalCenter: parent.horizontalCenter

        text: Elements.isExercisesSelected ? "Insert exercise" : "Insert dish"

        visible: Elements.isExercisesSelected || Elements.isDishesSelected

        onClicked: {
            windowTitle = Elements.isExercisesSelected ? "Insert exercise" : "Insert dish"
            Elements.isAddSelected = true
            navigateTo("ElementAddRemoveView.qml")
        }
    }

    Button {
        id: removeElementButton

        anchors.top: addElementButton.bottom
        anchors.topMargin: 20

        anchors.horizontalCenter: parent.horizontalCenter

        text: Elements.isExercisesSelected ? "Remove exercise" : "Remove dish"

        visible: Elements.isExercisesSelected || Elements.isDishesSelected

        onClicked: {
            windowTitle = Elements.isExercisesSelected ? "Remove exercise" : "Remove dish"

            Elements.isRemoveSelected = true
            navigateTo("ElementAddRemoveView.qml")
        }
    }

    Component.onCompleted: {
        Elements.updateLists()

        Elements.isExercisesSelected = false
        Elements.isDishesSelected = false

        Elements.isAddSelected = false
        Elements.isRemoveSelected = false
    }

}
