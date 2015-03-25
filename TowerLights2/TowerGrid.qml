import QtQuick 2.3
import QtQuick.Controls 1.2

Rectangle{
    id: gridArea
    width: 415
    height: 995
    color: "#00000000"
    signal towerClicked()
    signal towerReleased()
    Grid {
        objectName: "towerGrid"
        rows: 20
        columns: 12
        spacing: 5
        Repeater {
            objectName: "windows"
            model: 240
            Rectangle {
                width: 25
                height: 25
                color: "grey"
                border.width: 1
                border.color: "black"
                MouseArea {
                    preventStealing: false
                    hoverEnabled: true
                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                    anchors.fill: parent
                    /*
                    onContainsMouseChanged:
                    {
                        if (mouse.button == Qt.RightButton)
                            parent.color = "grey";
                        else if (mouse.button == Qt.LeftButton)
                            parent.color = currentColor.colorToString();
                    }
                    */
                    onPressed: towerClicked();
                    onReleased: towerReleased();
                }
            }
        }
    }
    Rectangle {
        objectName: "Tower Outline"
        y:145
        x:115
        height: 305
        width: 125
        color: "transparent"
        border.color: "black"
        border.width: 5
    }
}
