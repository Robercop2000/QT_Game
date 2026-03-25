import QtQuick
import QtQuick.Layouts

Window {
    width: 1200
    height: 720
    visible: true
    title: qsTr("Hello World")

    FontLoader
    {
        id: pMedium
        source: "qrc:/fonts/Doto-Bold.ttf"
    }

    Rectangle{
        id: gameArea
        anchors.fill: parent
        visible: true
        gradient: Gradient{
            GradientStop { position: 0.0; color: "Darkblue"}
            GradientStop { position: 1.0; color: "Black"}
        }

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
                    text: qsTr("Game Over\n " + scoreBoard.text)
                    font.family: pMedium.font.family
                    font.weight: pMedium.font.weight
                    font.styleName: pMedium.font.styleName
                    font.pixelSize: 60
                    Layout.alignment: Qt.AlignCenter
                    color: "White"
                }

                RowLayout
                {
                    spacing: 20

                    Rectangle
                    {
                        id: closeBtn
                        width: 250
                        height: 45
                        color: "Gray"
                        radius: 20
                        Text{
                            text: qsTr("Close")
                            font.family: pMedium.font.family
                            font.weight: pMedium.font.weight
                            font.styleName: pMedium.font.styleName
                            font.pixelSize: 35
                            color: "White"
                            anchors.centerIn: parent
                        }

                        MouseArea{
                            hoverEnabled: true

                            anchors.fill: parent
                            onEntered:{
                                closeBtn.color = "Red"
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
                        width: 250
                        height: 45

                        color: "Gray"
                        radius: 20
                        Text{
                            text: qsTr("Restart")
                            font.family: pMedium.font.family
                            font.weight: pMedium.font.weight
                            font.styleName: pMedium.font.styleName
                            font.pixelSize: 35
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
                                gameOverOverlay.visible = false
                            }
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
        width: 85
        height: 85
        color: "Transparent"
        x: control.x
        y: control.y
        focus: true

        Image{
            id: rocket
            source: "qrc:/player/rocket.png"
            width: 55
            height: 55
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
        }

        AnimatedImage
        {
            id: thruster
            source: "qrc:/player/thruster.gif"
            width: 30
            height: 30
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: rocket.bottom
            playing: true
        }

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

                            thruster.playing = true
                        }

        Keys.onReleased: (event) =>
                         {
                             if(event.key === Qt.Key_Left ||  Qt.Key_Right){
                                 control.stopMovement()
                             }
                             thruster.playing = false
                         }

        Component.onCompleted:
        {
            move.forceActiveFocus()
            thruster.playing = true
        }
    }

    Text{
        id: scoreBoard
        text: "Score: " + control.showScore()
        font.family: pMedium.font.family
        font.weight: pMedium.font.weight
        font.styleName: pMedium.font.styleName
        font.pixelSize: 40
        color: "White"
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
