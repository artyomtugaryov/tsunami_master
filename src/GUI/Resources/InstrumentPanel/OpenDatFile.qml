import QtQuick 2.7
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.1
import QtQuick.Layouts 1.1
import QtQuick.Window 2.0

FileDialog {
    id: root

    modality: Qt.WindowModal
    title: "Please choose a data file"
    selectExisting: true
    selectMultiple: false
    selectFolder: false
    nameFilters: [ "Data files (*.dat)" ]
    selectedNameFilter: "Data files (*.dat)"
    sidebarVisible: true
    onAccepted: {
        console.log("Accepted: " + fileUrls)
        _sourceGUI.startReadFromFile(fileUrls)
    }
    onRejected: { console.log("Rejected") }
}
