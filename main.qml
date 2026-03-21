import QtQuick

Window {
    width: 1512
    height: 982
    visible: true
    title: qsTr("Hello World")

    Rectangle
    {
        id: move
        width: 50
        height: 50
        color: "red"
        x: control.x
        y: control.y
        focus: true

        Keys.onPressed: (event) =>
                        {
                            if(event.key === Qt.Key_Left){
                                control.moveLeft();
                            }
                            if(event.key === Qt.Key_Right){
                                control.moveRight();
                            }
                        }
    }
}
