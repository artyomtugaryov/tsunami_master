import QtQuick 2.7

Item {
    id: root

    property string bathymetryPath: "None"
    property string brickPath: "None"
    property string imageSavePath: "None"
    property string maxDistributionPath: "None"

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
        id: infoPaths

        anchors.fill: parent
        anchors.margins: 20

        ItemGroup {
            id: itemBathymetry

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 10
            width: 330
            height: 30
            text: "Bathymetry: "
            value: bathymetryPath
        }

        ItemGroup {
            id: itemBrick

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: itemBathymetry.bottom
            anchors.topMargin: 10
            width: 330
            height: 30
            text: "Brick: "
            value: brickPath
        }

        ItemGroup {
            id: itemImageSave

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: itemBrick.bottom
            anchors.topMargin: 10
            width: 330
            height: 30
            text: "Image: "
            value: imageSavePath
        }

        ItemGroup {
            id: itemMaxDistribution

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: itemImageSave.bottom

            anchors.topMargin: 10
            width: 330
            height: 30
            text: "Distribution: "
            value: maxDistributionPath
        }

    }
}

