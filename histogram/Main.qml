import QtQuick

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Rectangle {
        anchors.fill: parent

        color: "#2B2B2B"

        Rectangle {
            id: plot
            width: 288
            height: 226

            color: "#2B2B2B"

            anchors.centerIn: parent
            Component.onCompleted: {
                var seperatotNums = 5
                for (var i = 0; i < seperatotNums + 1; i++) {
                    var component = seperator
                    var interval = plot.height / seperatotNums

                    var y = i * interval

                    if (component.status == Component.Ready) {
                        var spirit = component.createObject(plot, {
                                                                "topmargin": y
                                                            })
                    }
                }

                var recrecNum = 4

                for (var i = 0; i < recrecNum; i++) {
                    var component = bar

                    var rightMargin = (52 + 2) * i

                    var height = (i + 1) * 0.1 * plot.height

                    var percentNum = (i + 1) * 0.1

                    percentNum = percentNum.toFixed(2) * 100 + ("%")

                    if (component.status == Component.Ready) {
                        var spirit = component.createObject(plot, {
                                                                "recHight": height,
                                                                "rightMargin": rightMargin,
                                                                "percent": percentNum
                                                            })
                    }
                }
            }
            Component {
                id: seperator
                Rectangle {
                    property double topmargin

                    anchors.top: parent.top
                    anchors.topMargin: topmargin
                    anchors.left: parent.left
                    width: parent.width
                    height: 1
                    color: "#454545"
                }
            }

            Component {
                id: bar

                Rectangle {
                    id: barRec
                    property double recHight
                    property double rightMargin
                    property string percent

                    width: 52
                    height: recHight

                    anchors.bottom: parent.bottom
                    anchors.right: parent.right
                    anchors.rightMargin: rightMargin

                    color: "#1474A4"

                    Component.onCompleted: {
                        var component = percentNumText

                        if (component.status == Component.Ready) {
                            var spirit = component.createObject(barRec, {
                                                                    "textConent": percent
                                                                })
                        }
                    }
                }
            }

            Component {
                id: axleLabel
                Text {
                    property string textConent
                    property double leftMargin

                    anchors.left: parent.left
                    anchors.leftMargin: leftMargin
                    anchors.top: parent.bottom
                    anchors.topMargin: 3

                    font.pixelSize: 16
                    font.weight: 400
                    color: "#9E9E9E"

                    text: textConent
                }
            }

            Component {
                id: percentNumText
                Text {
                    property string textConent

                    anchors.bottom: parent.top
                    anchors.bottomMargin: 10
                    anchors.horizontalCenter: parent.horizontalCenter

                    font.pixelSize: 16
                    font.weight: 700
                    color: "#9E9E9E"

                    text: textConent
                }
            }
        }
    }
}
