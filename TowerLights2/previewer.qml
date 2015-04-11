import QtQuick 2.0

Rectangle {
    width: 300
    height: 570
    Row {
        objectName: "rows"
        spacing: 46
        Repeater {
            model: 4
            Column {
                objectName: "colums"
                spacing: 13
                Repeater {
                    model: 10
                    Rectangle {
                        objectName: "windows"
                        border.color: "black"
                        border.width: 2
                        width: 40
                        height: 45
                    }
                }
            }
        }
    }
}

