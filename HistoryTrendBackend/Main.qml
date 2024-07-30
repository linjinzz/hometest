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
            console.log(123)
            for (var i = 0; i < historyTrendBackend.plotLineList.length; i++) {
                console.log(historyTrendBackend.plotLineList[i].linePointList.length)
                for (var j = 0; j < historyTrendBackend.plotLineList[i].linePointList.length; j++) {
                    console.log("x的值为" + historyTrendBackend.plotLineList[i].linePointList[j].x)
                    console.log("y的值为" + historyTrendBackend.plotLineList[i].linePointList[j].y)
                }
            }
        }
    }

    Rectangle {
        anchors.centerIn: parent

        width: historyTrendBackend.plotWidth
        height: historyTrendBackend.plotHeight

        color: "lightblue"
    }
}
