import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import QtQuick.Controls

Button {
    property string textContent

    background: Rectangle {
        radius: 4
        color: "#444545"
    }

    implicitWidth: implicitContentWidth + leftPadding + rightPadding
    implicitHeight: implicitContentHeight + topPadding + bottomPadding

    leftPadding: 16
    rightPadding: 16
    topPadding: 12
    bottomPadding: 12

    contentItem: Text {
        text: textContent

        font.pixelSize: 20
        color: "#FFF"
        font.weight: 500
    }
}
