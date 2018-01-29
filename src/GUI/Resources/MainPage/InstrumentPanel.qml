import QtQuick 2.7
import "qrc:/Resources/Common/InstrumentPanel/"

Item {
    id: root

    property bool showData: false
    property bool showPaths: false

    function itemPressed(pressed, item) {
        if(pressed) {
            item.itemColor = internal.pressedItemColor
            item.textColor = internal.pressedTextColor
        }
        else {
            item.itemColor = internal.defaultItemColor
            item.textColor = internal.defaultTextColor
        }
    }
    QtObject{
        id: internal

        property string defaultItemColor: "#1d11a8"
        property string pressedItemColor: "#a9a3fd"
        property string defaultTextColor: "#ffffff"
        property string pressedTextColor: "#000000"
    }

    Image {
        id: background

        anchors.fill: parent
        opacity: 0.6
        source: "qrc:/Resources/Common/InstrumentPanel/Assets/InstrumentalPanel.png"
    }

    Column {
        spacing: -1

        anchors.fill: parent
        anchors.bottomMargin: 1

        ItemColumn {
            id: openData
            textAction: _sourceGUI.tsunamiManager.tsunamiData.readed ? "Reopen" : "Open"
            textDescription: "bathymetry file"
            sourceIconLeft: "Assets/OpenIcon.png"
            pressed: mouseAreaOpenData.pressed
            checked: _sourceGUI.tsunamiManager.tsunamiData.readed
            MouseArea {
                id: mouseAreaOpenData
                anchors.fill: parent
                onClicked: {
                    openDatFileDialog.open()
                }
            }
        }

        ItemColumn {
            id: showDataItem

            sourceIconLeft: "Assets/eye-flat.png"
            textAction: "Show"
            textDescription: "map data"
            pressed: mouseAreaShowData.pressed
            MouseArea {
                id: mouseAreaShowData
                anchors.fill: parent
                onClicked: {
                    showDataItem.checked = !showDataItem.checked;
                    showDataItem.textAction = showDataItem.checked ? "Hide" : "Show"
                    showData = !showData
                }
            }
        }

        ItemColumn {
            id: showPathsItem

            sourceIconLeft: "Assets/showPaths.png"
            textAction: "Show"
            textDescription: " paths"
            pressed: mouseAreaShowPaths.pressed
            MouseArea {
                id: mouseAreaShowPaths
                anchors.fill: parent
                onClicked: {
                    showPathsItem.checked = !showPathsItem.checked;
                    showPathsItem.textAction = showPathsItem.checked ? "Hide" : "Show"
                    showPaths = !showPaths
                }
            }
        }
        ItemColumn {
            id: quickStart
            textAction: "Quick"
            textDescription: "start"
            sourceIconLeft: "Assets/quick.png"
            pressed: mouseAreaQuickStart.pressed

            MouseArea {
                id: mouseAreaQuickStart
                anchors.fill: parent
                onClicked: {
                    quickStart.checked = !openData.checked;
                    quickStart.textAction = openData.checked ? "Re" : "Quick "
                    _sourceGUI.tsunamiManager.quickStart()
                }
            }
        }
            ItemColumn {
                id: saveInitData
                textAction: "Save init data"
                textDescription: ""
                sourceIconLeft: "Assets/save.png"
                pressed: mouseAreaSaveInitData.pressed

                MouseArea {
                    id: mouseAreaSaveInitData
                    anchors.fill: parent
                    onClicked: {
                        _sourceGUI.tsunamiManager.saveInitDataToJson()
                    }
                }
            }
    }
    OpenDatFile {
    id: openDatFileDialog

    }
}
