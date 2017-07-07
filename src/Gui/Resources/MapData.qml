import QtQuick 2.7

Item {
    id: root

    property int sizeX: 965
    property int sizeY: 1303
    property real deltaX: 0.165
    property real deltaY: 0.266
    property real startX: 12.143
    property real endX: 33.123
    property real startY: 11.313
    property real endY: 25.44

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
            value: deltaX
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
            value: deltaY
        }

    }
}
//}
//}
