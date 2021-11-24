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

    property string windowTitle: "Home"

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

        source: "Home.qml"
    }

    /*Text {
        id: name
        anchors.centerIn: parent
        text: qsTr("Sveiki atvykę į pagrindinį puslapį!")

        font.pixelSize: 30

        visible: contentLoader.source == "" ? true : false
    }*/

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



    property variant buttons: [
        { name: "Namai",        file: "Home.qml",          image: "Pictures/homeLogo.png" },
        { name: "Pasnikas",     file: "Fasting.qml",       image: "Pictures/fastingLogo.png" },
        { name: "Kalendorius",  file: "CallendarView.qml", image: "Pictures/callendarLogo.png" },
        { name: "#4",           file: "ElementsView.qml",  image: "Pictures/dishesLogo.png" },
        { name: "Nustatymai",   file: "Settings.qml",      image: "Pictures/settingsLogo.png" }
    ];



    Component.onCompleted: {
        console.log("completed");

        console.log("buttons length: " + buttons.length)
    }

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

            MouseArea{
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
