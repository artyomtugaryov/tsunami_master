import QtQuick 2.7

import QtQuick.Dialogs 1.0

Item {
    id: root

    QtObject {
        id: internal

        property var colors: _sourceGUI.tsunamiManager.tsunamiData.plotData.colors
        property var intervals: _sourceGUI.tsunamiManager.tsunamiData.plotData.colorBarIntervals
    }

    Column {
        id: colors

        anchors.centerIn: parent
        spacing: 5

        Rectangle {
            id: reset

            width: 22
            height: 22
            border.color: "gray"
            color: resetArea.pressed ? "blue" : "transparent";
            MouseArea {
                id: resetArea

                anchors.fill: parent

                onClicked: {
                    for(var i = 0; i < internal.colors.length; i++) {
                        var item = repeaterColors.itemAt(i)
                        item.color = internal.colors[i]
                        item.setText((internal.intervals[i]).toString())
                    }
                }
            }
            Image {
                id: resetColorBar

                anchors.centerIn: parent
                source: "Assets/resetColorBar.png"
            }
        }

        Repeater {
            id: repeaterColors

            model: internal.colors.length

            Rectangle {
                id: rec

                width: 22
                height: 22
                border.color: "gray"
                color: internal.colors[index];
                MouseArea {
                    id: area

                    property int i: index
                    anchors.fill: parent

                    onClicked: {
                        colorDialog.i = i
                        colorDialog.visible = true
                    }
                }
                TextInput {
                    id: edit

                    property int i: index
                    anchors.centerIn: parent
                    text: (internal.intervals[i])
                    horizontalAlignment: Text.AlignHCenter
                    onFocusChanged: focus ? selectAll() : 0
                    onTextChanged: {

                        if(Number(text) > 99) {
                            text = internal.intervals[i]
                        }
                        else if(i > 0
                                && Number(text)
                                <= internal.intervals[i - 1]) {
                            text = internal.intervals[i]
                        }
                        else if(i < internal.intervals.length - 1
                                && Number(text)
                                >= internal.intervals[i + 1]) {
                            text = internal.intervals[i]
                        }
                    }
                }

                ColorDialog {
                    id: colorDialog

                    property int i: 0
                    title: "Please choose a color"
                    onAccepted: {
                        console.log("You chose: " + colorDialog.color)
                        rec.color = colorDialog.color
                        Qt.quit()
                    }
                    onRejected: {
                        console.log("Canceled")
                        Qt.quit()
                    }
                }

                function setText(t) {
                    edit.text = t
                }
                function getText() {
                    return edit.text
                }
            }
        }
        Rectangle {
            id: apply

            width: 22
            height: 22
            border.color: "gray"
            color: applyArea.pressed ? "blue" : "transparent";
            MouseArea {
                id: applyArea

                anchors.fill: parent

                onClicked: {
                    for(var i = 0; i < internal.colors.length; i++) {
                        var item = repeaterColors.itemAt(i)
                        _sourceGUI.tsunamiManager.tsunamiData.plotData.setColorIntervalByIndex(item.color, Number(item.getText()), i)
                    }
                    _sourceGUI.tsunamiManager.tsunamiData.plotData.setColorBarMap();
                }
            }
            Image {
                id: applyColorBar

                anchors.centerIn: parent
                source: "Assets/checkColorBar.png"
            }
        }
    }
}
