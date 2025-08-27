import QtQuick

Rectangle {
    width: 300
    height: 50
    color: "pink"
    radius: 20

    PasswordInput {
        width: parent.width
        height: parent.height
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
