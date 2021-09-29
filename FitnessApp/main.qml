import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.5

import Elements 1.0


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

    property string windowTitle: "Main menu"

    //ElementsView properties
    //property bool isExercisesSelected: false
    //property bool isDishesSelected: false

    //Local qml properties --end


    PopupWindow{
        id: popup
        width: 300
        height: 300
    }


    Loader{
        id: contentLoader

        x: 0
        y: 0
    }

    Text {
        id: name
        anchors.centerIn: parent
        text: qsTr("Sveiki atvykę į pagrindinį puslapį!")

        font.pixelSize: 30

        visible: contentLoader.source == "" ? true : false
    }

    //Main window interface code

    Rectangle{
        id: topBar

        width: window.width
        height: 100

        color: "lightgreen"

        border.width: 2

        anchors.top: parent.top

        Text {
            id: title
            text: windowTitle

            anchors.centerIn: parent

            font.pointSize: 20
        }
    }


    Rectangle {
        id: bottomBox

        width: window.width //Bottom bar is screen wide
        height: 100 //Custom height

        y: window.height - height //This is at the bottom (height of the window - this object height)

        Rectangle {
            id: callendarButton

            width: parent.width / 3
            height: parent.height

            Image{
                id: callendarIcon

                anchors.left: parent.left

                height: 80
                width: 76.5

                anchors.centerIn: parent

                source: "Pictures/callendarLogo.png"
            }

            MouseArea{
                anchors.fill: parent

                onClicked: {
                    contentLoader.source = "CallendarView.qml"
                    windowTitle = "Kalendorius"
                }
            }

            border.width: 1
        }

        Rectangle {
            id: elementsButton

            width: parent.width / 3
            height: parent.height

            anchors.left: callendarButton.right

            Image{
                id: elementsIcon

                anchors.left: parent.left

                height: 80
                width: 76.5

                anchors.centerIn: parent

                source: "Pictures/notesLogo.png"
            }

            MouseArea{
                anchors.fill: parent

                onClicked: {
                    contentLoader.source = "ElementsView.qml"
                    windowTitle = "Sistemoje esantys pratimai ir patiekalai"

                    Elements.updateLists()

                    Elements.isExercisesSelected = false
                    Elements.isDishesSelected = false
                }
            }

            border.width: 1
        }

        Button{
            id: stepsButton

            anchors.left: elementsButton.right

            width: parent.width / 3
            height: parent.height

            text: "3"
        }
    }

}
