import QtQuick
import QtQuick.Layouts

Window {
    width: 1512
    height: 982
    visible: true
    title: qsTr("Hello World")

    Rectangle
    {
        id: gameOverOverlay
        anchors.fill: parent
        visible: false
        color: "Black"
        opacity: 0.8
        z: 1001

        ColumnLayout
        {
            anchors.centerIn: parent
            spacing: 20

            Text{
                id: gameOver
                text: qsTr("GameOver")
                color: "White"
            }

            RowLayout
            {
                spacing: 20

                Rectangle
                {
                    id: closeBtn
                    width: 300
                    height: 35
                    color: "Gray"
                    radius: 20
                    Text{
                        text: qsTr("Close")
                        color: "White"
                        anchors.centerIn: parent
                    }

                    MouseArea{
                        hoverEnabled: true

                        anchors.fill: parent
                        onEntered:{
                            closeBtn.color = "Blue"
                        }

                        onExited:
                        {
                            closeBtn.color = "Grey"
                        }

                        onClicked:
                        {
                            Qt.quit()
                        }
                    }
                }
                Rectangle{
                    id: restartBtn
                    width: 300
                    height: 35

                    color: "Gray"
                    radius: 20
                    Text{
                        text: qsTr("Restart")
                        color: "White"
                        anchors.centerIn: parent
                    }

                    MouseArea{
                        hoverEnabled: true

                        anchors.fill: parent
                        onEntered:
                        {
                            restartBtn.color = "Blue"
                        }

                        onExited:
                        {
                            restartBtn.color = "Grey"
                        }

                        onClicked:
                        {
                            control.restartGame()
                        }
                    }
                }

            }
        }
    }
    Connections{
        target: control
        onGameOver:
        {
            gameOverOverlay.visible = true
        }
    }

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
                                control.moveLeft()
                            }
                            if(event.key === Qt.Key_Right){
                                control.moveRight()
                            }
                            if(event.key === Qt.Key_Up){
                                control.applyThrust()
                            }
                            if(event.key === Qt.Key_Space){
                                control.fireBullet()
                            }
                        }

        Keys.onReleased: (event) =>
                         {
                             if(event.key === Qt.Key_Left){
                                 control.stopMovement()
                             }
                             if(event.key === Qt.Key_Right){
                                 control.stopMovement()
                             }
                         }
    }

    Text{
        id: scoreBoard
        text: "Score: " + control.showScore()
        color: "black"
        x: 50
        y: 50

        Connections
        {
            target: control
            function onScoreChanged(){
                scoreBoard.text = "Score: " + control.showScore()
            }
        }
    }

    Repeater
    {
        model: control.bullets
        delegate: Bullet{}
    }

    Repeater
    {
        model: control.enemies
        delegate: Enemy{}
    }
}
