import QtQuick 2.7

Item {
    id: root


ListView {
    id: colors

//    anchors.right: parent.horizontalCenter
//    anchors.left: parent.left
//    anchors.top: parent.top
//    anchors.bottom: parent.bottom
    anchors.fill: parent
    spacing: 10

    model: _sourceGUI.tsunamiManager.tsunamiData.plotData.colorBar
    delegate: Rectangle {
        width: 20
        height: 20
        border.color: "gray"
        color: modelData//repeaterColors.model.data
        Component.objectName: console.log(modelData)
    }
}
//    Column {
//        id: colors

////        Rectangle {

////        color: "red"
////        opacity: 0.5
////        }
//        anchors.right: parent.horizontalCenter
//        anchors.left: parent.left
//        anchors.top: parent.top
//        anchors.bottom: parent.bottom
//        spacing: 10

//        Repeater {
//            id: repeaterColors

//            model: (_sourceGUI.tsunamiManager.tsunamiData.plotData.colorBar)

//            Rectangle {
//                id: rec
//                width: 20
//                height: 20
//                border.color: "gray"
//                color: modelData;//repeaterColors.model.data
//            }
//        }
//    }


//    Column {
//        id: intervals

////        Rectangle {

////        color: "red"
////        opacity: 0.5
////        }
//        anchors.left: parent.horizontalCenter
//        anchors.right: parent.right
//        anchors.top: parent.top
//        anchors.bottom: parent.bottom
//        spacing: 10

//        Repeater {
//            id: repeaterIntervals

//            model: (_sourceGUI.tsunamiManager.tsunamiData.plotData.colorBarIntervals)

//            Text {

//                width: 20
//                height: 20
//                //border.color: "gray"
//                text: modelData;//repeaterColors.model.data
//            }
//        }
//    }
    Component.onCompleted: {
        var  a = _sourceGUI.tsunamiManager.tsunamiData.plotData.colorBarIntervals.length
        console.log(a)
        for(var i = 0; i < a; i++) {
            console.log(_sourceGUI.tsunamiManager.tsunamiData.plotData.colorBar[i].r)
        }
    }//console.log(_sourceGUI.tsunamiManager.tsunamiData.plotData.colorBar)
}
