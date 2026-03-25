#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QTimer>

class Bullet : public QObject
{
    Q_OBJECT

    Q_PROPERTY(float x READ x WRITE setX() NOTIFY xChanged)
    Q_PROPERTY(float y READ y WRITE setY() NOTIFY yChanged)

public:
    Bullet(QObject* parent = nullptr);

public:
    float x()
    {
        return m_x;
    }

    float y()
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

public slots:
    void updateBullet();

signals:
    void xChanged();
    void yChanged();
    void bulletDestroyed(Bullet* bullet);

private:
    float m_x;
    float m_y;
    float ySpeed;
    QTimer bTime;
};

#endif // BULLET_H
