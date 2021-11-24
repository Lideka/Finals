import QtQuick 2.0

import Home 1.0

Item {


    width: secondWindowWidth
    height: secondWindowHeight


    Flickable {
        id: homeContent

        anchors.fill: parent


        Rectangle {

            width: secondWindowWidth * 0.7
            height: 200

            Text {
                id: title

                anchors {

                    horizontalCenter: parent.horizontalCenter

                    top: parent.top
                    topMargin: 20
                }

                text: "Water you've drank today"

                font.pixelSize: 24
            }

            GridView {
                id: waterDrops

                width: parent.width
                height: 100

                //anchors.centerIn: parent
                anchors {
                    horizontalCenter: parent.horizontalCenter

                    top: title.bottom
                    topMargin: 10
                }

                cellWidth: parent.width / 8; cellHeight: cellWidth

                interactive: false //?

                model: 8

                delegate: Rectangle {
                    /*width: parent.width / buttons.length
                    height: parent.height*/

                    Image {
                        height: waterDrops.cellHeight
                        width: waterDrops.cellWidth

                        //anchors.centerIn: parent

                        source: index >= Home.waterAmmount ? "Pictures/emptyWaterDropIcon.png" : "Pictures/fullWaterDropIcon.png"

                        MouseArea {
                            anchors.fill: parent

                            onClicked: {
                                console.log("clicked index: " + index)
                                Home.waterAmmount = index + 1
                            }
                        }
                    }


                }

                /*Rectangle {

                    anchors.fill: parent
                    color: "transparent"

                    border.width: 1
                    border.color: "green"
                }*/
            }


            anchors.centerIn: parent

            border.width: 1

        }


    }
}
