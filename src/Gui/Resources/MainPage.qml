import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import "qrc:/Resources/InstrumentPanel/"

Item {
    id: root



    InstrumentPanel {
        id: instrumentPanel

        anchors.left: root.left
        anchors.top: root.top
        anchors.bottom: root.bottom
        width: 220

        onShowDataChanged: {
            mapDataAnimation.stop()
            mapDataAnimation.start()
        }
    }
    Image {
        id: background

        anchors.left: instrumentPanel.right
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        source: "Assets/Wallpaper_Of_Ocean_Waves.jpg"
    }

    MapData {
        id: mapData

        anchors.left: instrumentPanel.right
        anchors.top: parent.top
        opacity: 0
        OpacityAnimator {
            id: mapDataAnimation
            target: mapData
            from: instrumentPanel.showData ? 1 : 0
            to: instrumentPanel.showData ? 0 : 1
            duration: 500
        }
    }


}
