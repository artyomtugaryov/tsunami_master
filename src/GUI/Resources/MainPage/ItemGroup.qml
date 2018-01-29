import QtQuick 2.7

Item {
    id: root

    property string text: ""
    property var value
    property bool bold: true
    property int fontSize: 11
    onValueChanged: itemValue.text = value

    QtObject {
        id: internal

        property int prevKey: 0
    }

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

    Item {
        id: ancorsHelp

        anchors.left: itemText.right
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        clip: true

        TextEdit {
            id: itemValue

            anchors {
                right: parent.right
                verticalCenter: parent.verticalCenter
                rightMargin: root.bold ? 5 : itemValue.width < root.width - itemText.width
                             ?  (root.width - 50 - (itemValue.width)) / 2 : 5
            }
            text: root.value
            font.bold: root.bold
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: fontSize
            verticalAlignment: Text.AlignVCenter

            onFocusChanged: focus ? selectAll() : 0
            onTextChanged: text = root.value
            clip: true
        }
    }
}
