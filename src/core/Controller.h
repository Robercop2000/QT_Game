#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QTimer>
#include <Bullet.h>
#include <Enemy.h>
#include <QDebug>
#include <QQmlListProperty>

class Controller : public QObject
{
    Q_OBJECT

    Q_PROPERTY(float x READ x WRITE setX() NOTIFY xChanged)
    Q_PROPERTY(float y READ y WRITE setY() NOTIFY yChanged)
    Q_PROPERTY(QQmlListProperty<Bullet> bullets READ bullets NOTIFY bulletChanged)
    Q_PROPERTY(QQmlListProperty<Enemy> enemies READ enemies NOTIFY enemyChanged)
    Q_PROPERTY(uint score READ score WRITE setScore NOTIFY scoreChanged)

public:
    Controller(QObject* parent = nullptr);

public:
    float x()
    {
        return m_x;
    }

    void setX(float value)
    {
        if(m_x != value){
            m_x = value;
            emit xChanged();
        }
    }

    float y()
    {
        return m_y;
    } 

    void setY(float value)
    {
        if(m_y != value){
            m_y = value;
            emit yChanged();
        }
    }

    int score()
    {
        return m_score;
    }

    void setScore(int value)
    {
        if(m_score != value)
        {
            m_score = value;
            emit scoreChanged();
        }
    }

    Q_INVOKABLE void moveLeft();
    Q_INVOKABLE void moveRight();
    Q_INVOKABLE void applyThrust();
    Q_INVOKABLE void fireBullet();
    Q_INVOKABLE void createEnemy();
    Q_INVOKABLE void stopMovement();
    Q_INVOKABLE QString showScore();
    Q_INVOKABLE void restartGame();

    QQmlListProperty <Bullet> bullets(){
        return QQmlListProperty(this, &bulletList);
    }

    QQmlListProperty <Enemy> enemies(){
        return QQmlListProperty(this, &enemyList);
    }

public slots:
    void updateState();
    void deleteBullet(Bullet* bullet);
    void deleteEnemy(Enemy* enemy);
    void checkCollision();
    void updateMovement();

signals:
    void xChanged();
    void yChanged();
    void bulletChanged();
    void enemyChanged();
    void scoreChanged();
    void gameOver();

private:
    float m_x;
    float m_y;
    float xSpeed;
    float minX;
    float maxX;
    float bottomY;
    float ySpeed;
    float maxThrust = -10;
    float gravity = 0.5;
    QTimer time;
    QTimer startE;
    QList<Bullet*> bulletList;
    QList<Enemy*> enemyList;
    QTimer move;
    int moveDirection;
    uint m_score = 0;
};

#endif // CONTROLLER_H
