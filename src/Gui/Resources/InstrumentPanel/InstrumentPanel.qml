import QtQuick 2.7

Item {
    id: root

    property bool showData: false

    function itemPressed(pressed, item) {
        if(pressed) {
            item.itemColor = internal.pressedItemColor
            item.textColor = internal.pressedTextColor
        }
        else {
            item.itemColor = internal.defaultItemColor
            item.textColor = internal.defaultTextColor
        }
    }
    QtObject{
        id: internal

        property string defaultItemColor: "#1d11a8"
        property string pressedItemColor: "#a9a3fd"
        property string defaultTextColor: "#ffffff"
        property string pressedTextColor: "#000000"
    }

    Image {
        id: background
        anchors.fill: parent

        source: "Assets/InstrumentalPanel.png"
    }

    Column {
        spacing: 5

        anchors.fill: parent
        anchors.leftMargin: 2
        anchors.rightMargin: 2
        anchors.topMargin: 20
        anchors.bottomMargin: 20


        ItemColumn {
            id: showDataItem
            height: 40

            anchors.left: parent.left
            anchors.right: parent.right
            itemColor: internal.defaultItemColor
            radius: 10
            textColor: "white"
            sourceIconLeft: "Assets/eye-flat.png"
            textAction: "Show"
            textDescription: "map data"
            pressed: mouseAreaShowData.pressed
            MouseArea {
                id: mouseAreaShowData
                anchors.fill: parent
                onClicked: {
                    showDataItem.checked = !showDataItem.checked;
                    showDataItem.textAction = showDataItem.checked ? "Hide" : "Show"
                    showData = !showData
                }
            }
        }
    }
}
