import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item {
    id: root

    Image {
        id: background

        anchors.left: parent.left
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

        onShowPathsChanged: {
            pathsAnimation.stop()
            pathsAnimation.start()
        }

        onShowEditDataChanged: {
            editDataAnimation.stop()
            editDataAnimation.start()
        }

    }

    Grid {
        id: topRow

        anchors.left: instrumentPanel.right
        anchors.top: parent.top
        rows: 3
        columns: 3
        spacing: 5
        property int itemWidth: (root.width - instrumentPanel.width) / 3 - 15
        MapData {
            id: mapData

            width: topRow.itemWidth
            height: 210
            opacity: 0
            visible: instrumentPanel.showData || mapDataAnimation.running
            sizeX: _sourceGUI.tsunamiManager ? _sourceGUI.tsunamiManager.tsunamiData.sizeX : 0
            sizeY: _sourceGUI.tsunamiManager ? _sourceGUI.tsunamiManager.tsunamiData.sizeY : 0
            stepX: _sourceGUI.tsunamiManager ? (_sourceGUI.tsunamiManager.tsunamiData.stepX).toFixed(3) : 0
            stepY: _sourceGUI.tsunamiManager ? (_sourceGUI.tsunamiManager.tsunamiData.stepY).toFixed(3) : 0
            startX: _sourceGUI.tsunamiManager ? (_sourceGUI.tsunamiManager.tsunamiData.startX).toFixed(3) : 0
            startY: _sourceGUI.tsunamiManager ? (_sourceGUI.tsunamiManager.tsunamiData.startY).toFixed(3) : 0
            endX: _sourceGUI.tsunamiManager ? (_sourceGUI.tsunamiManager.tsunamiData.endX).toFixed(3) : 0
            endY: _sourceGUI.tsunamiManager ? (_sourceGUI.tsunamiManager.tsunamiData.endY).toFixed(3) : 0

            OpacityAnimator {
                id: mapDataAnimation
                target: mapData
                from: instrumentPanel.showData ? 1 : 0
                to: instrumentPanel.showData ? 0 : 1
                duration: 500
            }
        }

        PathsWindow {
            id: paths

            width: topRow.itemWidth
            height: 210
            opacity: 0
            visible: instrumentPanel.showPaths || pathsAnimation.running

            bathymetryPath: _sourceGUI.tsunamiManager
                            ? _sourceGUI.tsunamiManager.tsunamiData.bathymetryPath : "None"
            brickPath: _sourceGUI.tsunamiManager
                       ? _sourceGUI.tsunamiManager.tsunamiData.brickPath : "None"
            imageSavePath: _sourceGUI.tsunamiManager
                           ? _sourceGUI.tsunamiManager.tsunamiData.imageSavePath : "None"
            maxDistributionPath: _sourceGUI.tsunamiManager
                                 ? _sourceGUI.tsunamiManager.tsunamiData.maxDistributionSavePath : "None"
            OpacityAnimator {
                id: pathsAnimation
                target: paths
                from: instrumentPanel.showPaths ? 1 : 0
                to: instrumentPanel.showPaths ? 0 : 1
                duration: 500
            }
        }

        EditData {
            id: editData

            isobath: _sourceGUI.tsunamiManager.tsunamiData.isobath
            updateImage: _sourceGUI.tsunamiManager.tsunamiData.timeUpdate
            updateMareographs: _sourceGUI.tsunamiManager.tsunamiData.mareographsTimeUpdate
            calculationTime: _sourceGUI.tsunamiManager.tsunamiData.calculationTime
            width: topRow.itemWidth
            height: 210
            opacity: 0
            visible: instrumentPanel.showEditData || editDataAnimation.running

            OpacityAnimator {
                id: editDataAnimation
                target: editData
                from: instrumentPanel.showEditData ? 1 : 0
                to: instrumentPanel.showEditData ? 0 : 1
                duration: 500
            }

        }
        move: Transition {
                NumberAnimation { properties: "x,y"; duration: 400; easing.type: Easing.OutBounce }
            }
    }

}
