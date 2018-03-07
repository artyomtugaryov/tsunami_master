import QtQuick 2.7

DynamicItem {
    id: calculationWindow

    property bool colorBarPresent: false

    width: minWidth
    height: minHeight
    minWidth: visible
              ? plotImage.sourceSize.width
                + (calculationWindow.colorBarPresent ? colorBar.width : 0) + 10/*margins*/
                + arrows.width : 20
    minHeight: visible
               ? plotImage.sourceSize.height + 10/*margins*/ : 20

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
            source: "image://plot/" + (internal.postfix).toString()
        }

        ColorBar {
            id: colorBar

            width: 40
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            visible: calculationWindow.colorBarPresent
        }

        Item {
            id: panel

            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: checkSize.sourceSize.width

            Image {
                id: checkSize

                anchors.top: parent.top
                anchors.topMargin: 2
                source: "Assets/checkSize.png"

                Rectangle {
                    id: checkSizeBackground

                    anchors.fill: parent
                    color: "blue"
                    opacity: 0.3
                    radius: 5
                    visible: checkSizeArea.pressed
                }

                MouseArea {
                    id: checkSizeArea

                    anchors.fill: parent

                    onClicked: {
                        calculationWindow.width = calculationWindow.minWidth
                        calculationWindow.height = calculationWindow.minHeight
                    }
                }
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
                        if(!calculationWindow.colorBarPresent
                                && calculationWindow.width - colorBar.width <= calculationWindow.minWidth) {
                            calculationWindow.width -= colorBar.width
                        }
                    }
                }
            }
        }
    }
}
