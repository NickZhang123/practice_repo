import QtQuick

Item {
    width: parent.width
    height: parent.height
    visible: true

    // 数据模型
    ListModel {
        id: mymodel
        ListElement { name: "项目 1"; color: "#e74c3c" }
        ListElement { name: "项目 2"; color: "#3498db" }
        ListElement { name: "项目 3"; color: "#2ecc71" }
        ListElement { name: "项目 4"; color: "#f39c12" }
        ListElement { name: "项目 5"; color: "#9b59b6" }
        ListElement { name: "项目 6"; color: "#1abc9c" }
        ListElement { name: "项目 7"; color: "#d35400" }
        ListElement { name: "项目 8"; color: "#34495e" }
        ListElement { name: "项目 9"; color: "#16a085" }
    }

    // 委托组件
    Component {
        id: delegate

        Rectangle {
            width: 100
            height: 160
            radius: 10
            color: model.color
            opacity: 0.9

            // 应用路径属性
            z: iconZ  // Z序控制叠放层次
            scale: iconScale  // 缩放控制大小

            // 阴影效果
            layer.enabled: true
            // layer.effect: DropShadow {
            //     transparentBorder: true
            //     radius: 8
            //     samples: 16
            //     color: "#80000000"
            // }

            Text {
                text: model.name
                color: "white"
                font.bold: true
                font.pixelSize: 16
                anchors.centerIn: parent
            }

            // 当前项高亮效果
            border.width: PathView.isCurrentItem ? 3 : 0
            border.color: "gold"

            // 平滑动画
            Behavior on scale { NumberAnimation { duration: 200 } }
            Behavior on opacity { NumberAnimation { duration: 200 } }
        }
    }

    PathView {
        id: view
        anchors.fill: parent
        width: parent.width
        height: parent.height
        model: mymodel
        delegate: delegate
        flickDeceleration: 300
        preferredHighlightBegin: 0.5
        preferredHighlightEnd: 0.5
        pathItemCount: 7  // 同时显示7个项目
        clip: true
        enabled: opacity == 1.0

        path: Path {
            id: path
            startX: 0
            startY: view.height * 0.5

            PathAttribute{name:"iconZ";value: 0}
            PathAttribute{name:"iconScale";value: 0.7}
            PathLine{x:view.width/2; y: path.startY}

            PathAttribute{name:"iconZ";value: 200}
            PathAttribute{name:"iconScale";value: 1.0}

            PathLine{x:view.width; y: path.startY}
            PathAttribute{name:"iconZ";value: 0}
            PathAttribute{name:"iconScale";value: 0.7}
        }

        // 键盘导航支持
        focus: true
        Keys.onLeftPressed: decrementCurrentIndex()
        Keys.onRightPressed: incrementCurrentIndex()
    }

    // 控制面板
    Rectangle {
        width: parent.width
        height: 60
        anchors.bottom: parent.bottom
        color: "#34495e"
        opacity: 0.8

        Row {
            spacing: 10
            anchors.centerIn: parent

            Text {
                text: "当前项: " + (view.currentIndex + 1) + " / " + view.count
                color: "white"
                font.pixelSize: 16
                anchors.verticalCenter: parent.verticalCenter
            }

            Rectangle {
                width: 100
                height: 40
                color: "#3498db"
                radius: 5

                Text {
                    text: "上一项"
                    color: "white"
                    anchors.centerIn: parent
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: view.decrementCurrentIndex()
                }
            }

            Rectangle {
                width: 100
                height: 40
                color: "#3498db"
                radius: 5

                Text {
                    text: "下一项"
                    color: "white"
                    anchors.centerIn: parent
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: view.incrementCurrentIndex()
                }
            }
        }
    }

    // 说明文本
    Text {
        text: "水平滑动或使用键盘左右键导航"
        color: "white"
        font.pixelSize: 14
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 10
    }
}
