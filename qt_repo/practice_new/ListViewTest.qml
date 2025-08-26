import QtQuick

Item {
    width: 400
    height: 300

    ListModel {
        id: listmodel
        ListElement { name: "xx"; age: 11 }
        ListElement { name: "yy"; age: 12 }
        ListElement { name: "zz"; age: 13 }
    }

    ListView {
        id: listview
        spacing: 5
        anchors.fill: parent

        //model: ["a", "b", "c"]
        model: listmodel

        delegate: Rectangle {
            width: parent.width
            height: 50
            color: "gold"
            border {
                color: "cyan"
                width: 1
            }
            Text {
                //id: name
                // text: modelData
                text: model.name
                anchors.centerIn: parent
            }
        }
    }

}
