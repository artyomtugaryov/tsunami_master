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

            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10
            height: 30
            text: "Bathymetry: "
            value: bathymetryPath
            bold: false
            fontSize: 9
        }

        ItemGroup {
            id: itemBrick

            anchors.top: itemBathymetry.bottom
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10
            height: 30
            text: "Brick: "
            value: brickPath
            bold: false
            fontSize: 9
        }

        ItemGroup {
            id: itemImageSave

            anchors.top: itemBrick.bottom
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10
            height: 30
            text: "Image: "
            value: imageSavePath
            bold: false
            fontSize: 9
        }

        ItemGroup {
            id: itemMaxDistribution

            anchors.top: itemImageSave.bottom
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10
            height: 30
            text: "Distribution: "
            value: maxDistributionPath
            bold: false
            fontSize: 9
        }

    }
}

