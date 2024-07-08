import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import QtQuick.Controls

Window {
    width: 1000
    height: 500
    visible: true
    title: qsTr("Hello World")



    Rectangle {
        width: 947
        height: 196

        color: "#2B2B2B"

        anchors.centerIn: parent

        // Item {
        //     id: statesItem
        //     visible: false
        //     state: "beforeCharge"
        //     states: [
        //         State {
        //             name: "beforeCharge"
        //             PropertyChanges { selectEnergy.visible: true }
        //             PropertyChanges { charing.visible:  false }
        //         },
        //         State {
        //             name: "charging"
        //             PropertyChanges { selectEnergy.visible: false }
        //             PropertyChanges { charing.visible:  true }
        //         },
        //         State {
        //             name: "afterCharging"
        //             PropertyChanges { main.opacity: 1 }
        //             PropertyChanges { wait.opacity: 0 }
        //         }
        //     ]
        // }

        Rectangle {
            id: banner

            anchors.top: parent.top
            width: parent.width
            height: 32

            color: "#373737"

            Text {
                anchors.centerIn: parent
                color: "#FFF"
                text: qsTr("Manual Defibrillation")
            }
        }

        Rectangle {

            anchors.top: banner.bottom

            color: "#2B2B2B"
            width: parent.width
            height: parent.height - banner.height

            Item {
                id: leftInfoBar

                width: 64
                height: parent.height - 20 * 2

                anchors.left: parent.left
                anchors.leftMargin: 19
                anchors.top: parent.top
                anchors.topMargin: 20

                ColumnLayout {
                    anchors.fill: parent
                    spacing: 0

                    Text {
                        opacity: 0.8
                        color: "#FFF"
                        font.pixelSize: 18
                        font.weight: 400
                        lineHeightMode: Text.FixedHeight
                        lineHeight: 16
                        text: qsTr("Shock")
                    }

                    // Item {
                    //     Layout.preferredHeight: 8
                    // }
                    Text {
                        color: "#FFF"
                        font.pixelSize: 24
                        font.weight: 500
                        lineHeightMode: Text.FixedHeight
                        lineHeight: 22
                        text: qsTr("3")
                    }

                    Item {
                        Layout.preferredHeight: 22
                        Layout.fillWidth: true

                        Rectangle {
                            anchors.centerIn: parent
                            width: parent.width
                            height: 1

                            color: Qt.rgba(1, 1, 1, 0.1)
                        }
                    }

                    Text {
                        opacity: 0.8
                        color: "#FFF"
                        font.pixelSize: 18
                        font.weight: 400
                        lineHeightMode: Text.FixedHeight
                        lineHeight: 16
                        text: qsTr("Last")
                    }

                    // Item {
                    //     Layout.preferredHeight: 8
                    // }
                    Text {
                        color: "#FFF"
                        font.pixelSize: 24
                        font.weight: 500
                        lineHeightMode: Text.FixedHeight
                        lineHeight: 22
                        text: qsTr("01:26")
                    }

                    Item {
                        Layout.fillHeight: true
                    }
                }
            }

            Rectangle {
                id: middleBanner
                width: 253
                height: 148

                radius: 4
                color: "#1A1A1A"

                anchors.left: leftInfoBar.right
                anchors.leftMargin: 18
                anchors.top: parent.top
                anchors.topMargin: 8

                Item {

                    // color: "lightblue"
                    anchors.fill: parent

                    anchors {
                        leftMargin: 12
                        rightMargin: 17
                        topMargin: 25
                        bottomMargin: 25
                    }

                    // RowLayout {
                    //     anchors.fill: parent
                    //     spacing: 0
                    Text {
                        id: leftfont
                        anchors.verticalCenter: parent.verticalCenter

                        color: "#00BD5E"
                        font.pixelSize: 108
                        font.weight: 500
                        lineHeightMode: Text.FixedHeight
                        lineHeight: 75
                        text: qsTr("150")
                    }

                    Text {
                        anchors.left: leftfont.right

                        color: "#00BD5E"
                        font.pixelSize: 52
                        font.weight: 500
                        lineHeightMode: Text.FixedHeight
                        lineHeight: 75
                        text: qsTr(" J")

                        anchors.baseline: leftfont.baseline
                    }
                }
            }

            Item {
                width: 520
                height: 148

                //color: "lightblue"
                anchors.left: middleBanner.right
                anchors.leftMargin: 36
                // anchors.right: parent.right
                // anchors.rightMargin: 37
                anchors.top: parent.top
                anchors.topMargin: 8
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 8

                Text {
                    id: selectEnergy

                    visible: false

                    anchors.left: parent.left
                    anchors.top: parent.top
                    anchors.topMargin: 20

                    font.pixelSize: 32
                    font.weight: 700
                    lineHeightMode: Text.FixedHeight
                    lineHeight: 22

                    color: "#FFF"

                    text: qsTr("Select Energy")
                }

                Item {
                    id: charing

                    width: parent.width
                    height: 88

                    visible: true

                    Text {
                        id: chargingLabel
                        anchors.top: parent.top
                        anchors.topMargin: 13

                        color: "#FFF"

                        font.pixelSize: 32
                        font.weight: 700

                        lineHeightMode: Text.FixedHeight
                        lineHeight: 22

                        text: "Charging to 150J..."
                    }

                    Button {

                        implicitWidth: implicitContentWidth + leftPadding + rightPadding
                        implicitHeight: implicitContentHeight + topPadding + bottomPadding

                        leftPadding: 16
                        rightPadding: 16
                        topPadding: 17
                        bottomPadding: 17

                        anchors.verticalCenter: parent.verticalCenter
                        anchors.verticalCenterOffset: -8
                        anchors.right: parent.right

                        background: Rectangle {
                            radius: 4
                            border.width: 2
                            border.color: Qt.rgba(1.0, 0.8039, 0.0196,0.5)

                            color: Qt.rgba(0.4118, 0.4118, 0.4118, 0.20)
                        }

                        contentItem: Text {

                            font.pixelSize: 20
                            font.weight: 500

                            lineHeightMode: Text.FixedHeight
                            lineHeight: 16

                            color: "#FFCD05"

                            text: qsTr("Disarm")
                        }
                    }

                    MyProgressBar {
                        anchors.left: parent.left
                        anchors.top: chargingLabel.bottom
                        anchors.topMargin: 18
                    }
                }

                Item {
                    id: buttonArray

                    width: parent.width
                    height: 60

                    anchors.bottom: parent.bottom

                    RowLayout {
                        anchors.fill: parent

                        spacing: 16

                        MyButton {
                            textContent: "Filtered ECG"
                        }

                        MyButton {
                            textContent: "Start NBP"
                        }

                        MyButton {
                            textContent: "Zero CO2"
                        }

                        Item {
                            Layout.fillWidth: true
                        }
                    }
                }
            }
        }
    }
}
