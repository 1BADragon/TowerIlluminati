import QtQuick 2.3
import QtQuick.Controls 1.2

Rectangle {
    width: 511
    height: 61
    color: "#00000000"
    Grid{
        id: colorPallet
        rows: 2
        columns: 8
        spacing: 5
        Repeater{
            model: 16
            Rectangle{
                width: 25
                height: 25
                color: paletteColors.getColor()
                border.width: 1
                border.color: "black"
                MouseArea
                {
                    anchors.fill: parent
                    acceptedButtons: Qt.RightButton | Qt.LeftButton
                    onClicked: {
                        if(mouse.button == Qt.RightButton){
                            parent.color = currentColor.colorToString();
                        }else if(mouse.button == Qt.LeftButton){
                            currentColor.setColor(parent.color)
                        }
                    }

                }
            }
        }
    }
}

