import QtQuick

Rectangle {
    width: 300
    height: 300
    color: "lightgray"

    Column {
        id: columnLayout
        spacing: 10   // 子项之间的间距
        anchors.centerIn: parent

        Rectangle {
            width: 200
            height: 40
            color: "red"
        }

        Rectangle {
            width: 200
            height: 40
            color: "green"
        }

        Rectangle {
            width: 200
            height: 40
            color: "blue"
        }
    }
}
