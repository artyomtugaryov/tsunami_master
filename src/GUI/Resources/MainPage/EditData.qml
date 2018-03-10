import QtQuick 2.7

Item {
    id: root

    property real isobath: 0.0
    property int calculationTime: 0
    property int updateImage: 0
    property int updateMareographs: 0

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
        id: edit

        anchors.fill: parent
        anchors.margins: 20

        ItemGroup {
            id: itemIsobath

            change: true
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10
            height: 30
            text: "Isobath: "
            value: Number(isobath)
            bold: true
            fontSize: 11

            onPressedChanged: {
                _sourceGUI.tsunamiManager.tsunamiData.setIsobath(parseFloat(textValue))
            }
        }

        ItemGroup {
            id: itemCalculationTime

            change: true
            anchors.top: itemIsobath.bottom
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10
            height: 30
            text: "Calc. time: "
            value: Number(calculationTime)
            bold: true
            fontSize: 11

            onPressedChanged: {
                _sourceGUI.tsunamiManager.tsunamiData.setCalculationTime(parseInt(textValue))
            }
        }

        ItemGroup {
            id: imageUpdate

            change: true
            anchors.top: itemCalculationTime.bottom
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10
            height: 30
            text: "Plot update: "
            value: Number(updateImage)
            bold: true
            fontSize: 11

            onPressedChanged: {
                _sourceGUI.tsunamiManager.tsunamiData.setTimeUpdate(parseInt(textValue))
            }
        }

        ItemGroup {
            id: itemMareographsUpdate

            change: true
            anchors.top: imageUpdate.bottom
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10
            height: 30
            text: "Mar. update: "
            value: Number(updateMareographs)
            bold: true
            fontSize: 11

            onPressedChanged: {
                _sourceGUI.tsunamiManager.tsunamiData.setMareographsTimeUpdate(parseInt(textValue))
            }
        }

    }
}

