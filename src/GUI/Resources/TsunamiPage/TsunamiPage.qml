import QtQuick 2.7

import "qrc:/Resources/Common/InstrumentPanel/"

Item {
    id: root

    property int currentCalculationTime: 0

    function imageUpdate() {
        if (!internal.plotSwap) {
            internal.postfix1 = internal.postfix2 + 1
        }
        else {
            internal.postfix2 = internal.postfix1 + 1
        }
        internal.plotSwap = !internal.plotSwap
    }
    QtObject {
        id: internal

        property int postfix1: 0
        property int postfix2: 0
        property bool plotSwap: true
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

    TsunamiAreaItem {
        id: tsunamiArea

        x: 320
        y: 20
    }
}
