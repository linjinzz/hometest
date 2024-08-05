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

        }
    }

    PlotItem {
        id: plot
        anchors.centerIn: parent

        width: historyTrendBackend.plotWidth
        height: historyTrendBackend.plotHeight

        Component.onCompleted: {
            console.log(historyTrendBackend.plotLineList)
            setData(historyTrendBackend.plotLineList)
        }

        MouseArea {
            anchors.fill: parent
            property real lastX: 0
            property int num: 0

            onPressed: mouse => lastX = mouse.x

            onPositionChanged: mouse => {
                                   var startTime = new Date().getTime()

                                   // 记录开始时间
                                   var delta = mouse.x - lastX

                                   historyTrendBackend.updatePlot(delta)
                                   plot.setData(
                                       historyTrendBackend.plotLineList)
                                   lastX = mouse.x

                                   var endTime = new Date().getTime()
                                   // 记录结束时间
                                   var executionTime = endTime - startTime

                                   // 计算执行时间
                                   console.log(
                                       "onPositionChanged execution time: " + executionTime + " ms")
                               }
        }
    }
}
