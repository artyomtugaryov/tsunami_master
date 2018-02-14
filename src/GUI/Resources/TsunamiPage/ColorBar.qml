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
        spacing: 10

        Repeater {
            id: repeaterColors

            model: internal.colors.length
            //Item {
            //    property int i: index
            Rectangle {
                id: rec

                width: 25
                height: 25
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
                TextEdit {
                    id: edit

                    property int i: index
                    anchors.centerIn: parent
                    text: (internal.intervals[i])
                    horizontalAlignment: Text.AlignHCenter
                    onFocusChanged: focus ? selectAll() : 0
                    onTextChanged: {
                        console.log(Number(text), internal.intervals[i], i)

                        if(Number(text) > 99) {
                            text = internal.intervals[i]
                        }
                        else if(i > 0
                                && Number(text)
                                <= internal.intervals[i - 1]) {
                            console.log("1111111")
                            text = internal.intervals[i]
                        }
                        else if(i < internal.intervals.length - 1
                                && Number(text)
                                >= internal.intervals[i + 1]) {
                            text = internal.intervals[i]
                            console.log("22222222")
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
            }
        }
    }
}
