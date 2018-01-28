import QtQuick 2.7

Item {
    id: root

    property string sourceIconLeft: ""
    property string description: ""
    property string itemColor: "white"
    property string textColor: "white"
    property string textAction: ""
    property string textDescription: ""
    property bool checked: false
    property real radius: 0
    property bool pressed: false

    height: 40

    anchors.left: parent.left
    anchors.right: parent.right

    onPressedChanged: {
        if(pressed) {
            background.color = internal.pressedItemColor
            description.color = internal.pressedTextColor
        }
        else {
            background.color = internal.defaultItemColor
            description.color = internal.defaultTextColor
        }
    }

    QtObject{
        id: internal

        property string defaultItemColor: "#1d11a8"
        property string pressedItemColor: "#a9a3fd"
        property string defaultTextColor: "#ffffff"
        property string pressedTextColor: "#000000"
    }

    Rectangle {
        id: background

        anchors.fill: parent
        color: internal.defaultItemColor
        opacity: 0.8
    }

    Rectangle {
        id: border

        anchors.fill: parent
        color: "transparent"
        border.color: "black"
    }

    Image {
    anchors.fill: parent
    source: "Assets/buttonTab.png"
    opacity: 0.7
    }

    Image {
        id: iconLeft

        anchors.left: parent.left
        anchors.leftMargin: 2
        anchors.verticalCenter: parent.verticalCenter
        source: sourceIconLeft
    }

    Text {
        id: description

        font.family: "Arial Rounded MT Bold"
        font.pointSize: 12
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        anchors.left: iconLeft.right
        anchors.right: checkedIcon.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.leftMargin: 2
        anchors.rightMargin: 2
        text: textAction + (textAction.length === 0 ? "" : " ")
              + textDescription
        color: internal.defaultTextColor
    }

    Image {
        id: checkedIcon

        anchors.right: parent.right
        anchors.rightMargin: 2
        anchors.verticalCenter: parent.verticalCenter
        visible: checked
        source: "Assets/checked.png"
    }
}
