import QtQuick 2.7
import QtQuick.Dialogs 1.1
import "qrc:/Resources/Common/InstrumentPanel/"

Item {
    id: root

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
            id: runCalculation

            sourceIconLeft: "Assets/start.png"
            textAction: "Start"
            textDescription: "calculation"
            pressed: mouseAreaShowData.pressed
            MouseArea {
                id: mouseAreaShowData
                anchors.fill: parent
                onClicked: {
                    runCalculation.checked = !runCalculation.checked;
                    runCalculation.textAction = runCalculation.checked ? "Stop" : "Start"
                    _sourceGUI.tsunamiManager.startCalculation()
                }
            }
        }

        ItemColumn {
            id: pauseCalculation

            sourceIconLeft: "Assets/pause.png"
            textAction: "Pause"
            textDescription: ""
            pressed: mousePauseCalculation.pressed
            MouseArea {
                id: mousePauseCalculation
                anchors.fill: parent
                onClicked: {
                    pauseCalculation.checked = !pauseCalculation.checked;
                    pauseCalculation.textAction = pauseCalculation.checked ? "Continue" : "Pause"
                }
            }
        }
        ItemColumn {
            id: setImagePath
            textAction: "Set"
            textDescription: " image save path"
            sourceIconLeft: "Assets/image.png"
            pressed: mouseAreaSetImagePath.pressed
            checked: _sourceGUI.tsunamiManager.tsunamiData.imageSavePath
                     !== "None"

            MouseArea {
                id: mouseAreaSetImagePath
                anchors.fill: parent
                onClicked: {
                    setImageFolderPath.open()
                }
            }
        }
        ItemColumn {
            id: setDistributionPath
            textAction: "Set"
            textDescription: " distribution path"
            sourceIconLeft: "Assets/distribution.png"
            pressed: mouseAreaSetDistributionPath.pressed
            checked: _sourceGUI.tsunamiManager.tsunamiData.maxDistributionSavePath
                     !== "None"

            MouseArea {
                id: mouseAreaSetDistributionPath
                anchors.fill: parent
                onClicked: {
                    setDistributionFolderPath.open()
                }
            }
        }
        ItemColumn {
            id: setMareographsPath
            textAction: "Set"
            textDescription: " mareographs path"
            sourceIconLeft: "Assets/saveMareographs.png"
            pressed: mouseAreaSetMareographsPath.pressed
            checked: _sourceGUI.tsunamiManager.tsunamiData.MareographsSavePath
                     !== "None"

            MouseArea {
                id: mouseAreaSetMareographsPath
                anchors.fill: parent
                onClicked: {
                    setMareographsFolderPath.open()
                }
            }
        }
        ItemColumn {
            id: openMareographsFile
            textAction: "Open"
            textDescription: "mareographs file"
            sourceIconLeft: "Assets/openMareographs.png"
            pressed: mouseAreaOpenMareographs.pressed

            MouseArea {
                id: mouseAreaOpenMareographs
                anchors.fill: parent
                onClicked: {
                    openMareographsFile.textAction = openMareographsFile.checked ? "Reopen" : "Open"
                    openMareographs.open()
                }
            }
        }
        ItemColumn {
            id: openBrickFile
            textAction: "Open"
            textDescription: "brick file"
            sourceIconLeft: "Assets/openBrick.png"
            pressed: mouseAreaBrickFile.pressed

            MouseArea {
                id: mouseAreaBrickFile
                anchors.fill: parent
                onClicked: {
                    openBrickFile.checked = !openBrickFile.checked;
                    openBrickFile.textAction = openBrickFile.checked ? "Reopen" : "Open"
                    openBrick.open()
                }
            }
        }
        ItemColumn {
            id: mareographsUpdating
            textAction: "Mareographs"
            textDescription: "updating"
            sourceIconLeft: "Assets/updatingMareographs.png"
            pressed: mouseMareographsUpdating.pressed
            checked: _sourceGUI.tsunamiManager.tsunamiData.mareographsUpdating

            MouseArea {
                id: mouseMareographsUpdating
                anchors.fill: parent
                onClicked: {
                    _sourceGUI.tsunamiManager.setMareographsUpdating(!mareographsUpdating.checked)
                }
            }
        }
    }

    FileDialog {
        id: setImageFolderPath

        modality: Qt.WindowModal
        title: "Please choose the image path save"
        selectExisting: true
        selectMultiple: false
        selectFolder: true
        sidebarVisible: true
        onAccepted: {
            console.log("Accepted: " + fileUrls)
            _sourceGUI.tsunamiManager.tsunamiData.setImageSavePath(fileUrls)
        }
    }
    FileDialog {
        id: setDistributionFolderPath

        modality: Qt.WindowModal
        title: "Please choose the distribution path save"
        selectExisting: true
        selectMultiple: false
        selectFolder: true
        sidebarVisible: true
        onAccepted: {
            console.log("Accepted: " + fileUrls)
            _sourceGUI.tsunamiManager.tsunamiData.setMaxDistributionSavePath(fileUrls)
        }
    }
    FileDialog {
        id: setMareographsFolderPath

        modality: Qt.WindowModal
        title: "Please choose the distribution path save"
        selectExisting: true
        selectMultiple: false
        selectFolder: true
        sidebarVisible: true
        onAccepted: {
            console.log("Accepted: " + fileUrls)
            _sourceGUI.tsunamiManager.tsunamiData.setMareographsSavePath(fileUrls)
        }
    }
    FileDialog {
        id: openBrick

        modality: Qt.WindowModal
        title: "Please choose a data file"
        selectExisting: true
        selectMultiple: false
        selectFolder: false
        nameFilters: [ "Text files (*.txt)", "Brick files (*.brc)" ]
        selectedNameFilter: "Text files (*.txt)"
        sidebarVisible: true
        onAccepted: {
            console.log("Accepted: " + fileUrls)
            _sourceGUI.tsunamiManager.readBrickDataFromFile(fileUrls)
        }
    }
    FileDialog {
        id: openMareographs

        modality: Qt.WindowModal
        title: "Please choose a data file"
        selectExisting: true
        selectMultiple: false
        selectFolder: false
        nameFilters: [ "Text files (*.txt)", "Mareographs files (*.mrg)" ]
        selectedNameFilter: "Mareographs files (*.mrg)"
        sidebarVisible: true
        onAccepted: {
            console.log("Accepted: " + fileUrls)
            _sourceGUI.tsunamiManager.readMareographsFromFile(fileUrls)
            openMareographsFile.checked = true
        }
    }
}
