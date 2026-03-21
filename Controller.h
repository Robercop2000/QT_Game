#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QTimer>

class Controller : public QObject
{
    Q_OBJECT

    Q_PROPERTY(double x READ x WRITE setX() NOTIFY xChanged)
    Q_PROPERTY(double y READ y WRITE setY() NOTIFY yChanged)

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

    Q_INVOKABLE void moveLeft(){
        setX(m_x - xSpeed);
        if(m_x < minX)
        {
            setX(minX);
        }
    }

    Q_INVOKABLE void moveRight(){
        setX(m_x + xSpeed);
        if(m_x > maxX)
        {
            setX(maxX);
        }
    }

    Q_INVOKABLE void applyThrust()
    {
        ySpeed = maxThrust;
    }

public slots:
    void updateState()
    {
        m_y += ySpeed;
        ySpeed += gravity;

        if(m_y > bottomY)
        {
            m_y = bottomY;
        }

        emit yChanged();
    }

signals:
    void xChanged();
    void yChanged();

private:
    double m_x;
    double m_y;
    double xSpeed;
    double minX;
    double maxX;
    double bottomY;
    double ySpeed;
    double maxThrust = -30;
    double gravity = 0.5;
    QTimer time;
};

#endif // CONTROLLER_H
