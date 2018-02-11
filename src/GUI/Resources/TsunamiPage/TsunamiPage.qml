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

        width: 850
        height: 350

        minWidth: 850
        minHeight: 350

        Row {

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
            }

            ColorBar {
                id: colorBar

                width: 100
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                visible: calculationWindow.colorBarPresent
            }

            Image {
                id: arrows

                anchors.verticalCenter: parent.verticalCenter
                width: 30
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
