import QtQuick
import QtQuick.Controls

Window {
    width: 800
    height: 480
    visible: true
    title: qsTr("Hello World")

    Button {
        height: 40
        width: 40

        anchors.top: parent.top
        anchors.topMargin: 100

        onClicked: {

            //     for (var i; i < historyTrendBackend.plotLineList.length; i++) {
            //         var lineList = historyTrendBackend.plotLineList[i]
            //         for (var j; j < lineList.length; j++) {
            //             var p = lineList[j]
            //             console.log("x的值为" + p.x)
            //             console.log("y的值为" + p.y)
            //         }
            //     }
        }
    }

    Rectangle {
        anchors.centerIn: parent

        width: historyTrendBackend.plotWidth
        height: historyTrendBackend.plotHeight

        color: "lightblue"
    }
}
