import QtQuick 2.0

Item {

    width: secondWindowWidth
    height: secondWindowHeight

    Rectangle{

        width: parent.width
        height: parent.height

        border.width: 1

        Text {
            id: name
            text: qsTr("užrašai bled")

            font.pointSize: 20

            anchors.centerIn: parent
        }

        color: "red"
    }

}
