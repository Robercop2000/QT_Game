import QtQuick

Item
{
    property var ePng:[
        "qrc:/enemy/enemy1.png",
        "qrc:/enemy/enemy2.png",
        "qrc:/enemy/enemy3.png",
        "qrc:/enemy/enemy4.png",
        "qrc:/enemy/enemy5.png"
    ]

    property int eIndex: Math.floor(Math.random() * ePng.length)

    id: enemy
    width: 40
    height: 40
    x: model.x
    y: model.y

    Image
    {
        id: enemies
        anchors.fill: parent
        source: ePng[model.index]
    }
}