#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QTimer>

class Enemy : public QObject
{
    Q_OBJECT

    Q_PROPERTY(float x READ x WRITE setX() NOTIFY xChanged)
    Q_PROPERTY(float y READ y WRITE setY() NOTIFY yChanged)
    Q_PROPERTY(int m_index READ index WRITE setIndex NOTIFY indexChanged)

public:
    Enemy(QObject* parent = nullptr);

public:
    int index()
    {
        return m_index;
    }

    void setIndex(int value)
    {
        if(m_index != value)
        {
            m_index = value;
            emit indexChanged();
        }
    }

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
    void updateEnemy();

signals:
    void xChanged();
    void yChanged();
    void indexChanged();

private:
    float m_x;
    float m_y;
    int m_index;
    float ySpeed;
    QTimer eTime;
};

#endif // ENEMY_H
