import QtQuick

Rectangle
{
    id: enemy
    width: 10
    height: 30
    color: "blue"
    x: model.x
    y: model.y
}