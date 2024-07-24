import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Window {
    visible: true
    height: 600
    width: 800

    Rectangle {
        id: root
        property bool collapsed: false
        property list<QtObject> recList

        function productInfoRec() {
            for (var i = 0; i < root.recList.length; i++) {
                var rec = root.recList[i]
                rec.destroy()
            }

            root.recList.length = 0

            var displayColors = []

            for (var i = 0; i < listView.model.count; i++) {
                var priority = listView.model.get(i).priority

                if (!displayColors.includes(priority)) {
                    displayColors.push(priority)

                    if (displayColors.length > 2) {
                        break
                    }
                }
            }

            for (var i = 0; i < displayColors.length; i++) {
                var color
                if (displayColors[i] === 1) {
                    color = "#C03831"
                }

                if (displayColors[i] === 2) {
                    color = "#E5AA15"
                }

                if (displayColors[i] === 3) {
                    color = "#1DBCD2"
                }

                var component = myRecCop

                var margin = (8 + 2) * i

                if (component.status == Component.Ready) {
                    var rec = component.createObject(root, {
                                                         "recColor": color,
                                                         "recRightMargin": margin
                                                     })

                    recList.push(rec)
                }
            }
        }
        height: collapsed ? listView.contentHeight : 40
        width: 900

        anchors.top: parent.top

        color: "black"

        Behavior on height {
            NumberAnimation {
                alwaysRunToEnd: true
                duration: 750
                easing.type: Easing.OutExpo
            }
        }

        ListView {
            id: listView

            width: parent.width
            height: parent.height

            clip: true

            spacing: 4

            model: listModel

            delegate: rollDelegate

            signal updateAlarmInfo

            NumberAnimation {
                id: animation
                target: listView
                property: "contentY"
                duration: 800
                alwaysRunToEnd: true
            }

            add: Transition {
                NumberAnimation {
                    property: "opacity"
                    from: 0
                    to: 1.0
                    duration: 400
                    alwaysRunToEnd: true
                }
                NumberAnimation {
                    property: "scale"
                    from: 0
                    to: 1.0
                    duration: 400
                    alwaysRunToEnd: true
                }
            }
        }

        Connections {
            target: listView

            function onUpdateAlarmInfo() {
                if (listView.count === 1)
                    return

                listView.forceLayout()

                var nextindex = listView.currentIndex + 1

                var curpos = listView.contentY
                var nextpos = curpos + 40 + 4
                listView.positionViewAtIndex(nextindex, ListView.Contain)
                listView.currentIndex = nextindex
                animation.from = curpos
                animation.to = nextpos
                animation.running = true
            }
        }

        Connections {
            target: listView.model
            function onRowsInserted() {
                root.productInfoRec()
                //onRowsRemoved: listView.updateNotifications()
                // 添加其他可能改变模型的信号处理
            }
        }

        MouseArea {
            anchors.fill: parent

            onClicked: {
                root.collapsed = !root.collapsed
            }
        }
    }

    Component {
        id: rollDelegate
        Item {

            height: 40
            width: listView.width

            Row {
                anchors.fill: parent
                spacing: 0

                Rectangle {
                    width: 314
                    height: parent.height

                    color: alarmInfoColor

                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 20
                        id: name
                        text: alarmInfo

                        // color: "#FFF"
                    }
                }

                Rectangle {
                    width: parent.width - 314
                    height: parent.height

                    color: Qt.lighter(alarmInfoColor, 0.2)
                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 16

                        color: "#FFF"

                        text: alarmContent
                    }
                }
            }
        }
    }

    ListModel {
        id: listModel
        ListElement {
            priority: 1
            alarmInfoColor: "#C03831"
            alarmInfo: "ECG Leads Off"
            alarmContentColor: "#33C03831"
            alarmContent: "Plugin ECG leads to get numeric info"
        }
        // ListElement {
        //     priority: 2
        //     alarmInfoColor: "#E5AA15"
        //     alarmInfo: "Battery Empty"
        //     alarmContentColor: "#E5AA1533"
        //     alarmContent: "Connect the device to power supply"
        // }
        // ListElement {
        //     priority: 3
        //     alarmInfoColor: "#1DBCD2"
        //     alarmInfo: "ECG Leads Off"
        //     alarmContentColor: "#1DBCD233"
        //     alarmContent: "Plugin ECG leads to get numeric info"
        // }
    }

    Button {
        id: addBtn
        anchors.centerIn: parent

        text: "addRed"

        onClicked: {
            var listNode = {
                "priority": 1,
                "alarmInfoColor": "#C03831",
                "alarmInfo": "ECG Leads Off",
                "alarmContentColor": "#33C03831",
                "alarmContent": "Plugin ECG leads to get numeric info"
            }
            console.log(listView.model.count)

            var currntNode = listView.model.get(0)
            console.log(currntNode.priority)
            console.log(listNode.priority)

            for (var i = 0; i < listView.model.count; i++) {
                currntNode = listView.model.get(i)

                if (currntNode.priority > listNode.priority) {
                    listView.model.insert(i, listNode)
                    break
                }

                if (i === listView.model.count - 1) {
                    listView.model.append(listNode)
                    break
                }
            }
        }
    }

    Component {
        id: myRecCop

        Rectangle {
            visible: !root.collapsed && listView.model.count > 1

            z: 999

            property string recColor
            property double recRightMargin

            anchors.right: parent.right
            anchors.rightMargin: recRightMargin

            width: 8
            height: 40

            color: recColor
        }
    }

    Button {
        id: addYellow
        anchors.left: addBtn.right
        anchors.verticalCenter: addBtn.verticalCenter
        anchors.leftMargin: 10

        text: "add yellow"

        onClicked: {
            var listNode = {
                "priority": 2,
                "alarmInfoColor": "#E5AA15",
                "alarmInfo": "Battery Empty",
                "alarmContentColor": "#E5AA1533",
                "alarmContent": "Connect the device to power supply"
            }

            console.log(listView.model.count)

            var currntNode = listView.model.get(0)
            console.log(currntNode.priority)
            console.log(listNode.priority)

            for (var i = 0; i < listView.model.count; i++) {
                currntNode = listView.model.get(i)

                if (currntNode.priority > listNode.priority) {
                    listView.model.insert(i, listNode)
                    break
                }

                if (i === listView.model.count - 1) {
                    listView.model.append(listNode)
                    break
                }
            }
        }
    }

    Button {
        anchors.left: addYellow.right
        anchors.verticalCenter: addYellow.verticalCenter
        anchors.leftMargin: 10

        text: "add blue"

        onClicked: {
            var listNode = {
                "priority": 3,
                "alarmInfoColor": "#1DBCD2",
                "alarmInfo": "Battery Empty",
                "alarmContentColor": "#E5AA1533",
                "alarmContent": "Connect the device to power supply"
            }

            console.log(listView.model.count)

            var currntNode = listView.model.get(0)
            console.log(currntNode.priority)
            console.log(listNode.priority)

            for (var i = 0; i < listView.model.count; i++) {
                currntNode = listView.model.get(i)

                if (currntNode.priority > listNode.priority) {
                    listView.model.insert(i, listNode)
                    break
                }

                if (i === listView.model.count - 1) {
                    listView.model.append(listNode)
                    break
                }
            }
        }
    }
}
