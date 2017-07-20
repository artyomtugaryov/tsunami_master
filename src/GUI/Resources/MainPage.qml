import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import "qrc:/Resources/InstrumentPanel/"

Item {
    id: root

    Image {
        id: background

        anchors.left: parent.left//instrumentPanel.right
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        source: "Assets/Wallpaper_Of_Ocean_Waves.jpg"
    }

    InstrumentPanel {
        id: instrumentPanel

        anchors.left: root.left
        anchors.top: root.top
        anchors.bottom: root.bottom
        width: 260

        onShowDataChanged: {
            mapDataAnimation.stop()
            mapDataAnimation.start()
        }
    }


    Row {
        id: topRow

        anchors.left: instrumentPanel.right
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.verticalCenter


    }

    MapData {
        id: mapData

        width: (root.width - instrumentPanel.width) / 3
        height: 210
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
