import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    id: root

    property variant win;

    visible: true
    width: 1350
    height: 690
    maximumHeight: height
    maximumWidth: width
    minimumHeight: height
    minimumWidth: width

    title: qsTr("Tsunami Master")

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        MainPage {
//            anchors.left: root
//            anchors.top: parent
        }

        Page {
            Label {
                text: qsTr("First page")
                anchors.centerIn: parent
            }
        }

        Page {
            Label {
                text: qsTr("Second page")
                anchors.centerIn: parent
            }
        }
    }

    header: TabBar {
        id: tabBar

        currentIndex: swipeView.currentIndex
        TabButton {
//            onClicked: {
//                var component = Qt.createComponent("MainPage.qml");
//                win = component.createObject(root);
//                win.show();
//            }
            text: qsTr("First")
        }
        TabButton {
            text: qsTr("Second")
        }
    }
}
