import QtQuick

Rectangle
{
    id: enemy
    width: 40
    height: 40
    color: "blue"
    x: model.x
    y: model.y
}