import QtQuick 2.15
import QtCharts 2.15
import QtQuick.Controls 2.15

Window {
    height: 600
    width: 800
    visible: true

    Button {
        height: 40
        width: 40
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        onClicked: {
            if (plot.height === 12) {
                plot.height = 59
            } else {
                plot.height = 12
            }
        }
    }

    Rectangle {
        id: rec2
        width: plot.width
        height: plot.height
        x: plot.x
        y: plot.y
        color: "#595959"
        visible: false

        Component.onCompleted: {
            for (var i = 0; i < myList.length; i++) {
                if (myList[i].lineColor !== "#787878") {
                    var leftMargin = myList[i].linePoints[0].x / 100 * 669
                    var firstPoint = myList[i].linePoints[0]
                    var lastPoint = myList[i].linePoints[myList[i].linePoints.length - 1]
                    var recLength = (lastPoint.x - firstPoint.x) / 100 * 669

                    var component = indicator
                    var topMargin = myList[i].lineColor === "#FAB700" ? 4 : 0

                    if (component.status === Component.Ready) {
                        var recIndicator = component.createObject(rec2, {
                                                                      "recWidth": recLength,
                                                                      "topMargin": topMargin,
                                                                      "leftMargin": leftMargin,
                                                                      "recColor": myList[i].lineColor
                                                                  })
                    }
                }
            }
        }
    }

    Component {
        id: indicator
        Rectangle {
            property double recWidth
            property double topMargin
            property double leftMargin
            property string recColor
            height: 4
            width: recWidth
            anchors.top: parent.top
            anchors.topMargin: topMargin
            anchors.left: parent.left
            anchors.leftMargin: leftMargin
            color: recColor
        }
    }

    Rectangle {
        id: plot
        property bool collapes: false
        property bool animationComplete: true
        visible: true
        property double yMaximum: 120
        property double yMinimum: 40

        function changVisible() {
            if (collapes == false && visible === true
                    && animationComplete == true) {
                collapes = true
                visible = true
            } else if (collapes == true && visible === true
                       && animationComplete == true) {
                visible = false
                rec2.visible = true
            } else if (collapes == true && visible === false
                       && animationComplete == true) {
                collapes = false
                visible = true
                animationComplete = false
            } else if (collapes == false && visible === true
                       && animationComplete == false) {
                collapes = false
                visible = true
                rec2.visible = false
                animationComplete = true
            }
        }

        function toYPixels(y) {
            return plot.height - ((y - yMinimum) / (yMaximum - yMinimum) * plot.height)
        }

        property double xMaximum: 100
        property double xMinimum: 0
        function toXPixels(x) {
            return (x - xMinimum) / (xMaximum - xMinimum) * plot.width
        }

        Behavior on height {
            PropertyAnimation {
                alwaysRunToEnd: true
                duration: 400
                easing.type: Easing.Linear

                onRunningChanged: {
                    plot.changVisible()
                }
            }
        }

        anchors.centerIn: parent
        width: 669
        height: 59
        color: Qt.lighter("#E8E8E8", 0.3)

        Canvas {
            id: canvas
            anchors.fill: parent

            onPaint: {
                var context = getContext("2d")
                context.clearRect(0, 0, plot.width, plot.height)
                context.lineWidth = 4

                for (var i = 0; i < myList.length; i++) {
                    context.beginPath()
                    context.strokeStyle = myList[i].lineColor
                    for (var k = 0; k < myList[i].linePoints.length; k++) {
                        var pointF = myList[i].linePoints[k]
                        if (k === 0) {
                            context.moveTo(plot.toXPixels(pointF.x),
                                           plot.toYPixels(pointF.y))
                        } else {
                            context.lineTo(plot.toXPixels(pointF.x),
                                           plot.toYPixels(pointF.y))
                        }
                    }
                    context.stroke()
                }
            }
        }

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onPositionChanged: mouse => {
                                   var closestY
                                   var closestDistance = Number.MAX_VALUE

                                   for (var i = 0; i < myList.length; i++) {
                                       for (var k = 0; k < myList[i].linePoints.length; k++) {
                                           var pointF = myList[i].linePoints[k]
                                           var xPixel = plot.toXPixels(pointF.x)
                                           var distance = Math.abs(
                                               mouse.x - xPixel)

                                           if (distance < closestDistance) {
                                               closestDistance = distance
                                               closestY = pointF.y
                                           }
                                       }
                                   }

                                   if (closestY !== undefined) {
                                       yValueDisplay.text = "Y: " + closestY.toFixed(
                                           2)
                                   } else {
                                       yValueDisplay.text = ""
                                   }
                               }
        }
    }

    // Text {
    //     id: yValueDisplay
    //     //text: "Y:"
    //     anchors.top: plot.bottom
    //     anchors.horizontalCenter: parent.horizontalCenter
    //     font.pointSize: 16
    // }
}
