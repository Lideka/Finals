import QtQuick 2.0
import QtQuick.Controls 2.0

import ElementInfo 1.0

Item {

    width: secondWindowWidth
    height: secondWindowHeight

    Text {
        id: name

        x: 20
        y: 150

        text: qsTr("Name: " + ElementInfo.name)

        font.pixelSize: 15
    }

    Text {
        id: calories
        text: qsTr("Calories: " + ElementInfo.calories)

        x: 20

        anchors.top: name.bottom
        anchors.topMargin: 20

        font.pixelSize: 15
    }

    Text {
        id: description
        text: qsTr("Description: ")

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

        text: ElementInfo.description


    }

}
