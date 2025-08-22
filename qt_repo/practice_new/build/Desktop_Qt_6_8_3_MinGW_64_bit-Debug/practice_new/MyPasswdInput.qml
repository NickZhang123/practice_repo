import QtQuick
import QtQuick.Controls

Rectangle {
    id: myinput
    radius: 5
    color: "gray"
    border.color: "#cce6ff"
    border.width: 1
    width: 300
    height: 40

    Rectangle {
        id: leftRect
        anchors.left: parent.left
        anchors.leftMargin: 5
        width:  parent.width - 40
        height: parent.height
        color: "transparent"

        TextField {
            id: passwordField
            anchors.fill: parent
            placeholderText: "input text hear"
            echoMode: TextInput.Password // 默认隐藏密码
            font {
                pixelSize: 16
                family: "黑体"
            }
            background: Rectangle {
                color: "transparent"
            }
        }
    }

    Rectangle {
        id: rightRect
        color: "transparent"
        anchors.left: leftRect.right
        anchors.right: parent.right
        width:  40
        height: parent.height
        //border.width: 1
        //border.color: "red"
        Image {
            id: eyeIcon
            anchors.centerIn: parent
            width: 24
            height: 24
            source: "qrc:/icon/visibility_on.png"
            fillMode: Image.PreserveAspectFit

            // MouseArea {
            //     anchors.fill: parent
            //     onClicked: {
            //         console.log("xxx")
            //     }
            // }
        }
    }
}





