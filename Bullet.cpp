#include "Bullet.h"

Bullet::Bullet(QObject* parent) : m_x(50/2), m_y(0), ySpeed(-10)
{
    connect(&bTime, &QTimer::timeout, this, &Bullet::updateBullet);
    bTime.start(16);
}

void Bullet::updateBullet(){
    setY(m_y + ySpeed);

    if(m_y < 0){
        emit bulletDestroyed(this);
    }
}