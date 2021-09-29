import QtQuick 2.0
import QtQuick.Controls 2.0

import Elements 1.0

Item {
    width: secondWindowWidth
    height: secondWindowHeight

    //All qml elements needed for adding an element
    Item {

        width: parent.width
        height: parent.height

        visible: Elements.isAddSelected

        Text {
            id: name

            y: 150

            anchors.horizontalCenter: parent.horizontalCenter

            text: qsTr("Pavadinimas: ")
        }

        TextField {
            id: nameTextField

            anchors.top: name.bottom
            anchors.topMargin: 5
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text {
            id: calories

            anchors.top: nameTextField.bottom
            anchors.topMargin: 20
            anchors.horizontalCenter: parent.horizontalCenter

            text: qsTr("Kalorijos: ")
        }

        TextField {
            id: caloriesTextField

            anchors.top: calories.bottom
            anchors.topMargin: 5
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text {
            id: description

            anchors.top: caloriesTextField.bottom
            anchors.topMargin: 20
            anchors.horizontalCenter: parent.horizontalCenter

            text: qsTr("Aprašymas: ")
        }

        Rectangle{
            id: descriptionTextField
            width:200
            height: 200

            anchors.top: description.bottom
            anchors.topMargin: 5
            anchors.horizontalCenter: parent.horizontalCenter

            border.width: 1

            TextArea {
                id: descriptionTextArea

                anchors.fill: parent
            }
        }

        Button {
            id: addElementButton

            text: "Prideti"

            anchors.top: descriptionTextField.bottom
            anchors.topMargin: 5

            anchors.horizontalCenter: parent.horizontalCenter

            onClicked: Elements.addElement(nameTextField.text, caloriesTextField.text, descriptionTextArea.text)
        }

    }


    //All qml elements needed for removing an element
    Item{
        width: parent.width
        height: parent.height

        visible: Elements.isRemoveSelected

        Text {
            id: nameToRemoveLabel

            y: 150

            anchors.horizontalCenter: parent.horizontalCenter

            text: Elements.isExercisesSelected ? qsTr("Įveskite norimo ištrinti pratimo pavadinimą: ") : qsTr("Įveskite norimo ištrinti patiekalo pavadinimą: ")
        }

        TextField {
            id: nameToRemoveTextField

            anchors.top: nameToRemoveLabel.bottom
            anchors.topMargin: 5
            anchors.horizontalCenter: parent.horizontalCenter

            //visible: Elements.isExercisesSelected
        }

        Button {
            id: removeElementButton

            text: "Ištrinti"

            anchors.top: nameToRemoveTextField.bottom
            anchors.topMargin: 20

            anchors.horizontalCenter: parent.horizontalCenter

            onClicked: Elements.removeElement(nameToRemoveTextField.text)
        }
    }


}

