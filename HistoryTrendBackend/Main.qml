import QtQuick

Window {
    width: 800
    height: 480
    visible: true
    title: qsTr("Hello World")

    Rectangle {
        anchors.centerIn: parent

        width: historyTrendBackend.plotWidth
        height: historyTrendBackend.plotHeight

        color: "lightblue"
    }
}
