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
        id: plot
        anchors.centerIn: parent

        color: Qt.lighter("#E8E8E8", 0.3)

        width: historyTrendBackend.plotWidth
        height: historyTrendBackend.plotHeight

        Canvas {
            id: canvas
            anchors.fill: parent
            antialiasing: true

            onPaint: {
                var context = getContext("2d")
                context.clearRect(0, 0, plot.width, plot.height)
                context.lineWidth = 4

                for (var i = 0; i < historyTrendBackend.plotLineList.length; i++) {
                    context.beginPath()
                    context.strokeStyle = historyTrendBackend.plotLineList[i].lineColor
                    for (var k = 0; k
                         < historyTrendBackend.plotLineList[i].linePointList.length; k++) {
                        var pointF = historyTrendBackend.plotLineList[i].linePointList[k]
                        if (k === 0) {
                            context.moveTo(pointF.x, pointF.y)
                        } else {
                            context.lineTo(pointF.x, pointF.y)
                        }
                    }
                    context.stroke()
                }
            }
        }

        MouseArea {
            anchors.fill: parent
            property real lastX: 0

            onPressed: mouse => lastX = mouse.x

            onPositionChanged: mouse => {
                                   var delta = mouse.x - lastX

                                   // console.log("mouse.x " + mouse.x)
                                   // console.log("lastX " + lastX)
                                   // console.log("move pix: " + delta)
                                   historyTrendBackend.updatePlot(delta)
                                   canvas.requestPaint()
                                   lastX = mouse.x
                               }
        }
    }
}
