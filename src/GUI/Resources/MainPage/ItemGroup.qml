import QtQuick 2.7

Item {
    id: root

    property string text: ""
    property var value
    property  string textValue: ""
    property bool bold: true
    property int fontSize: 11
    onValueChanged: itemValue.text = value
    property bool change: false
    property bool pressed: false
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
        anchors.right: change ? apply.left : parent.right
        anchors.rightMargin: change ? 5 : 0
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
            onTextChanged: {
                if(!change) {
                    text = root.value
                }
                else {
                    textValue = text
                }
            }
            clip: true
        }
    }

    Rectangle {
        id: apply

        visible: change
        width: 23
        height: 23
        border.color: "black"
        border.width: 1
        color: applyArea.pressed ? "blue" : "transparent";
        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.verticalCenter: parent.verticalCenter

        MouseArea {
            id: applyArea

            anchors.fill: parent

            onClicked: {
                root.pressed = !root.pressed
            }
        }
        Image {
            id: applyColorBar

            opacity: 0.8
            anchors.centerIn: parent
            source: "Assets/check.png"
        }
    }
}
