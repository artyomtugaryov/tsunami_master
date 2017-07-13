import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item {
    id: root

    property variant win;

    visible: true

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: 0

        MainPage {
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
}
