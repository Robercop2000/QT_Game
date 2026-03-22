#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QTimer>
#include <Bullet.h>
#include <QDebug>
#include <QQmlListProperty>

class Controller : public QObject
{
    Q_OBJECT

    Q_PROPERTY(double x READ x WRITE setX() NOTIFY xChanged)
    Q_PROPERTY(double y READ y WRITE setY() NOTIFY yChanged)
    Q_PROPERTY(QQmlListProperty<Bullet> bullets READ bullets NOTIFY bulletChanged)

public:
    Controller(QObject* parent = nullptr);

public:
    double x()
    {
        return m_x;
    }

    double y()
    {
        return m_y;
    }

    void setX(double value)
    {
        if(m_x != value){
            m_x = value;
            emit xChanged();
        }
    }

    void setY(double value)
    {
        if(m_y != value){
            m_y = value;
            emit yChanged();
        }
    }

    Q_INVOKABLE void moveLeft();
    Q_INVOKABLE void moveRight();
    Q_INVOKABLE void applyThrust();
    Q_INVOKABLE void fireBullet();

    QQmlListProperty <Bullet> bullets(){
        return QQmlListProperty(this, &bulletList);
    }

public slots:
    void updateState();

signals:
    void xChanged();
    void yChanged();
    void bulletChanged();

private:
    double m_x;
    double m_y;
    double xSpeed;
    double minX;
    double maxX;
    double bottomY;
    double ySpeed;
    double maxThrust = -10;
    double gravity = 0.5;
    QTimer time;
    QList<Bullet*> bulletList;
};

#endif // CONTROLLER_H
