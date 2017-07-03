import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    id: root

    property variant win;

    visible: true
    width: 640
    height: 480
    title: qsTr("Tsunami Master")

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

//        MainPage {
//        }

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
            onClicked: {
                var component = Qt.createComponent("MainPage.qml");
                win = component.createObject(root);
                win.show();
            }
            text: qsTr("First")
        }
        TabButton {
            text: qsTr("Second")
        }
    }
}
