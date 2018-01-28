import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

TabButton {
    id: root

    property string label: ""
    property string colorLabel: "black"

    Image {
        id: background

        anchors.fill: parent
        opacity: 0.5
        //source: "/Resources/InstrumentPanel/Assets/InstrumentalPanel.png"
        source: "/Resources/Assets/buttonTab.png"
    }

    Text {
        id: itemLabel
        anchors.centerIn: parent
        text: label
        font.family: "MV Boli"
        font.bold: true
        color: root.focus ? "black" : "white"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pointSize: 16
    }
}
