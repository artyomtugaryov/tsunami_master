import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import "qrc:/Resources/MainPage/"
import "qrc:/Resources/TsunamiPage/"

Item {
    id: root

    property variant win;

    visible: true

    objectName: "_sourceGUI"
    function onImageUpdate() {
        tsunamiPage.imageUpdate();
    }

    TabBar {
        id: tabBar
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        currentIndex: swipeView.currentIndex

        TabBarItem {
        label: "Home"
        }

        TabBarItem {
            label: "Calculation"
        }

        TabBarItem {
            label: "Mareographs"
        }
    }

    SwipeView {
        id: swipeView

        anchors.top: tabBar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        currentIndex: tabBar.currentIndex

        MainPage {
        }

        TsunamiPage {
        id: tsunamiPage
        currentCalculationTime: _sourceGUI.tsunamiManager.currentCalculationTime

        }

        Page {
            Label {
                text: qsTr("Second page")
                anchors.centerIn: parent
            }
        }
    }


}
