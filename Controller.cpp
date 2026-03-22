#include "Controller.h"

Controller::Controller(QObject* parent) : m_x(1512/2 - 50), m_y(952-50), xSpeed(10), minX(0), maxX(1512), bottomY(952-50)
{
    connect(&time, &QTimer::timeout, this, &Controller::updateState);
    time.start(16);
}

void Controller::moveLeft(){
    setX(m_x - xSpeed);
    if(m_x < minX)
    {
        setX(minX);
    }
}

void Controller::moveRight(){
    setX(m_x + xSpeed);
    if(m_x > maxX)
    {
        setX(maxX);
    }
}

void Controller::applyThrust()
{
    ySpeed = maxThrust;
    if(m_y < bottomY/1.5)
    {
        ySpeed = 0;
    }
}

void Controller::fireBullet()
{
    Bullet* newBullet = new Bullet();
    newBullet->setX(m_x + 25);
    newBullet->setY(m_y - 25);
    bulletList.append(newBullet);
    emit bulletChanged();
    qInfo() << "Fired Bullet";
}

void Controller::updateState()
{
    m_y += ySpeed;
    ySpeed += gravity;

    if(m_y > bottomY)
    {
        m_y = bottomY;
    }

    emit yChanged();
}
