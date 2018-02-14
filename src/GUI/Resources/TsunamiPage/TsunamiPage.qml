import QtQuick 2.7

import "qrc:/Resources/Common/InstrumentPanel/"

Item {
    id: root

    property int currentCalculationTime: 0

    function imageUpdate() {
        internal.postfix += 1;
    }

    QtObject {
        id: internal

        property int postfix: 1
    }

    Image {
        id: background
        anchors.fill: parent
        source: "Assets/tsunamiWave.jpg"
    }

    InstrumentPanel {
        id: instrumentPanel

        anchors.left: root.left
        anchors.top: root.top
        anchors.bottom: root.bottom
        width: 260
    }

    DynamicItem {
        id: calculationWindow

        property bool colorBarPresent: false
        x: 320
        y: 20

        width: 250//plotImage.sourceSize.width > 1 ?  plotImage.sourceSize.width + 10 : 5//plotImage. ? row.width + 5 : 5
        height: 300//plotImage.sourceSize.height > 1 ? plotImage.sourceSize.height + 10 : 5//plotImage.enabled ? row.height + 5 : 5

        minWidth: visible ? plotImage.sourceSize.width : 20//100//plotImage.enabled ? plotImage.sourceSize.width : 10
        minHeight: visible ? plotImage.sourceSize.height : 20 //100//plotImage.enabled ? plotImage.sourceSize.height : 10

        visible: _sourceGUI.tsunamiManager.tsunamiData.readed
        Row {
            id: row

            anchors.fill: parent
            anchors.margins: 5

            Image {
                id: plotImage

                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: calculationWindow.width - arrows.width
                       - (calculationWindow.colorBarPresent ? colorBar.width : 0) - 10
                //anchors.margins: 5
                source: "image://plot/" + (internal.postfix).toString()
                onSourceChanged: console.log(sourceSize.width, sourceSize.height)
            }

            ColorBar {
                id: colorBar

                width: 40
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                visible: calculationWindow.colorBarPresent
            }

            Image {
                id: arrows

                anchors.verticalCenter: parent.verticalCenter
                source: "Assets/arrows"
                        + (calculationWindow.colorBarPresent ? "Left" : "Right")
                        + ".png"

                Rectangle {
                    id: arrowsBackground

                    anchors.fill: parent
                    anchors.leftMargin: 3
                    anchors.rightMargin: 2
                    color: "blue"
                    opacity: 0.3
                    radius: 5
                    visible: arrowsArea.pressed
                }

                MouseArea {
                    id: arrowsArea

                    anchors.fill: parent

                    onClicked: {
                        calculationWindow.colorBarPresent = !calculationWindow.colorBarPresent
                    }
                }
            }
        }
    }
}
