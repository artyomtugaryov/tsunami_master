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
        x: 320
        y: 20

        width: 650
        height: 350

        Image {
            id: plotImage
            anchors.fill: parent
            anchors.margins: 5
            source: "image://plot/" + (internal.postfix).toString()
        }
    }
}
