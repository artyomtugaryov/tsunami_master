import QtQuick 2.7

Item {
    id: root

    property string text: ""
    property var value
    Rectangle {
        id: item

        anchors.fill: parent
        color: "white"
        opacity: 0.8
        border.color: "black"
        radius: 3
    }

    Text {
        id: itemText

        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: 5

        text: root.text
        font.bold: true
        font.pointSize: 11
        verticalAlignment: Text.AlignVCenter
    }

    TextEdit {
        id: itemValue

        anchors.left: itemText.right
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: 2
        anchors.rightMargin: 2

        text: Number(root.value)
        font.bold: true
        horizontalAlignment: Text.AlignHCenter
        font.pointSize: 11
        verticalAlignment: Text.AlignVCenter
        onFocusChanged: focus ? selectAll() : 0
        onTextChanged: text = Number(root.value)
    }
}
