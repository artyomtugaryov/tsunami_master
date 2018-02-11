import QtQuick 2.7

Item {
    id: root

    property int maxWidth: 0
    property int maxHeight: 0
    property int minWidth: 0
    property int minHeight: 0

    x: 20
    y: 20

    width: 650
    height: 350

    onWidthChanged: {
        if (maxWidth > 0) {
            if (width > maxWidth) width = maxWidth
        }
        if (minWidth > 0) {
            if (width < minWidth) width = minWidth
        }
    }

    onHeightChanged: {
        if (maxHeight > 0) {
            if (height > maxHeight) height = maxHeight
        }
        if (minHeight > 0) {
            if (height < minHeight) height = minHeight
        }
    }

    Rectangle {
        id: selComp
        anchors.fill: parent
        border {
            width: 2
            color: "gray"
        }
        color: "#354682B4"

        property int rulersSize: 18

        MouseArea {
            anchors.fill: parent
            drag {
                target: parent
                minimumX: 0
                minimumY: 0
                maximumX: parent.parent.width - parent.width
                maximumY: parent.parent.height - parent.height
                smoothed: true
            }
        }

        Rectangle {
            width: selComp.rulersSize
            height: selComp.rulersSize
            radius: selComp.rulersSize
            color: "gray"
            anchors.horizontalCenter: parent.left
            anchors.verticalCenter: parent.verticalCenter

            MouseArea {
                anchors.fill: parent
                drag{ target: parent; axis: Drag.XAxis }
                onMouseXChanged: {
                    if(drag.active) {
                        root.width = root.width - mouseX
                        root.x = root.x + mouseX
                        if(root.width < 30)
                            root.width = 30
                    }
                }
            }
        }

        Rectangle {
            width: selComp.rulersSize
            height: selComp.rulersSize
            radius: selComp.rulersSize
            color: "gray"
            anchors.horizontalCenter: parent.right
            anchors.verticalCenter: parent.verticalCenter

            MouseArea {
                anchors.fill: parent
                drag{ target: parent; axis: Drag.XAxis }
                onMouseXChanged: {
                    if(drag.active){
                        root.width = root.width + mouseX
                        if(root.width < 50)
                            root.width = 50
                    }
                }
            }
        }

        Rectangle {
            width: selComp.rulersSize
            height: selComp.rulersSize
            radius: selComp.rulersSize
            x: parent.x / 2
            y: 0
            color: "gray"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.top

            MouseArea {
                anchors.fill: parent
                drag{ target: parent; axis: Drag.YAxis }
                onMouseYChanged: {
                    if(drag.active){
                        root.height = root.height - mouseY
                        root.y = root.y + mouseY
                        if(root.height < 50)
                            root.height = 50
                    }
                }
            }
        }


        Rectangle {
            width: selComp.rulersSize
            height: selComp.rulersSize
            radius: selComp.rulersSize
            x: parent.x / 2
            y: parent.y
            color: "gray"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.bottom

            MouseArea {
                anchors.fill: parent
                drag{ target: parent; axis: Drag.YAxis }
                onMouseYChanged: {
                    if(drag.active){
                        root.height = root.height + mouseY
                        if(root.height < 50)
                            root.height = 50
                    }
                }
            }
        }
    }

    Image {
        anchors.fill: parent
        source: "Assets/InstrumentalPanel.png"
        opacity: 0.85
    }

    Drag.active: dragArea.drag.active
    Drag.hotSpot.x: 10
    Drag.hotSpot.y: 10
    MouseArea {
        id: dragArea
        anchors.fill: parent
        drag.target: parent
    }
}
