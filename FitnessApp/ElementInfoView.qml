import QtQuick 2.0
import QtQuick.Controls 2.0

import Elements 1.0

Item {

    width: secondWindowWidth
    height: secondWindowHeight

    Text {
        id: name

        x: 20
        y: 150

        text: qsTr("Pavadinimas: " + Elements.elementName)

        font.pixelSize: 15
    }

    Text {
        id: calories
        text: qsTr("Kalorijos: " + Elements.elementCalories)

        x: 20

        anchors.top: name.bottom
        anchors.topMargin: 20

        font.pixelSize: 15
    }

    Text {
        id: description
        text: qsTr("Aprašymas: ")

        x: 20

        anchors.top: calories.bottom
        anchors.topMargin: 20

        font.pixelSize: 15
    }

    TextArea {
        id: descriptionText

        x: 20

        width: 200
        height: 200

        readOnly: true

        wrapMode: "WordWrap"

        anchors.top: description.bottom
        anchors.topMargin: 10

        text: Elements.elementDescription


    }

    Component.onCompleted: Elements.initializeElementsInfo()

}
