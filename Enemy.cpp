#include "Enemy.h"

Enemy::Enemy(QObject* parent) : m_x(rand() % 1512), m_y(0), ySpeed(3)
{
    connect(&eTime, &QTimer::timeout, this, &Enemy::updateEnemy);
    eTime.start(150);
}

void Enemy::updateEnemy(){
    setY(m_y + ySpeed);
}