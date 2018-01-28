import QtQuick 2.7

Item {
    id: root

    property int sizeX: 0
    property int sizeY: 0
    property real stepX: 0
    property real stepY: 0
    property real startX: 0
    property real endX: 0
    property real startY: 0
    property real endY: 0

    Rectangle {
        id: informationGroup

        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 10
        border.color: "black"
        radius: 2
        opacity: 0.5
    }
    Item {
        id: infoColumn1

        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.margins: 20

        ItemGroup {
            id: itemSizeX

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 10
            width: 130
            height: 30
            text: "Size x: "
            value: sizeX
        }

        ItemGroup {
            id: itemStartX

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: itemSizeX.bottom
            anchors.topMargin: 10
            width: 130
            height: 30
            text: "Start x: "
            value: startX
        }

        ItemGroup {
            id: itemEndX

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: itemStartX.bottom
            anchors.topMargin: 10
            width: 130
            height: 30
            text: "End x: "
            value: endX
        }

        ItemGroup {
            id: itemDeltaX

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: itemEndX.bottom

            anchors.topMargin: 10
            width: 130
            height: 30
            text: "Step x: "
            value: stepX
        }

    }

    Item {
        id: infoColumn2

        anchors.right: parent.right
        anchors.top: parent.top
        anchors.left: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.margins: 20

        ItemGroup {
            id: itemSizeY

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 10
            width: 130
            height: 30
            text: "Size y: "
            value: sizeY
        }

        ItemGroup {
            id: itemStartY

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: itemSizeY.bottom
            anchors.topMargin: 10
            width: 130
            height: 30
            text: "Start y: "
            value: startY
        }

        ItemGroup {
            id: itemEndY

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: itemStartY.bottom
            anchors.topMargin: 10
            width: 130
            height: 30
            text: "End y: "
            value: endY
        }

        ItemGroup {
            id: itemDeltaY

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: itemEndY.bottom

            anchors.topMargin: 10
            width: 130
            height: 30
            text: "Step y: "
            value: stepY
        }

    }
}
