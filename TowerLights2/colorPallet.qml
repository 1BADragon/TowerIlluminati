import QtQuick 2.3
import QtQuick.Controls 1.2

Rectangle {
    width: 511
    height: 61
    color: "#00000000"
    Grid{
        id: colorPallet
        rows: 2
        columns: 10
        spacing: 5
        Repeater{
            model: 20
            Rectangle{
                width: 25
                height: 25
                //color: defaultColor.getColor()
                border.width: 1
                border.color: "black"
            }
        }
    }
}

