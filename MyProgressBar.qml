import QtQuick
import QtQuick.Controls.Basic

ProgressBar {
    id: control
    value: 0
    padding: 2

    implicitHeight: 20
    implicitWidth: 518

    Timer {
        repeat: true
        running: true
        interval: 1000 / 60

        onTriggered: {
            control.value += 0.001
            if (control.value >= 1) {
                control.value = 0
            }
        }
    }

    background: Rectangle {
        // implicitWidth: 200
        // implicitHeight: 6
        anchors.fill: parent
        color: "#202020"
    }

    contentItem: Item {

        // implicitWidth: 200
        // implicitHeight: 4
        anchors.fill: parent

        // Progress indicator for determinate state.
        Rectangle {
            width: control.visualPosition * parent.width
            height: parent.height
            color: "#00BD5E"
            visible: !control.indeterminate
        }

        // Scrolling animation for indeterminate state.
        Item {
            anchors.fill: parent
            visible: control.indeterminate
            clip: true

            Row {
                spacing: 20

                Repeater {
                    model: control.width / 40 + 1

                    Rectangle {
                        color: "#17a81a"
                        width: 20
                        height: control.height
                    }
                }
                XAnimator on x {
                    from: 0
                    to: -40
                    loops: Animation.Infinite
                    running: control.indeterminate
                }
            }
        }
    }
}
