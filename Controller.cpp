#include "Controller.h"

Controller::Controller(QObject* parent) : m_x(1512/2 - 50), m_y(952-50), xSpeed(10), minX(0), maxX(1512), bottomY(952-50)
{
    connect(&time, &QTimer::timeout, this, &Controller::updateState);
    time.start(16);

    connect(&time, &QTimer::timeout, this, &Controller::updateMovement);
    time.start(16);

    connect(&startE, &QTimer::timeout, this, &Controller::createEnemy);
    startE.start(1000 + rand() % 2000);
}

void Controller::moveLeft(){
    moveDirection = -1;
    if(!move.isActive())
    {
        move.start();
    }
    // setX(m_x - xSpeed);
    // if(m_x < minX)
    // {
    //     setX(minX);
    // }
}

void Controller::moveRight(){
    moveDirection = 1;
    if(!move.isActive())
    {
        move.start();
    }
    // setX(m_x + xSpeed);
    // if(m_x > maxX)
    // {
    //     setX(maxX);
    // }
}

void Controller::updateMovement()
{
    if(moveDirection == -1 && m_x > minX){
        setX(m_x - xSpeed);
    }
    if(moveDirection == 1 && m_x < maxX){
        setX(m_x + xSpeed);
    }
    if(moveDirection == 0){
        setX(m_x);
    }
}

void Controller::stopMovement()
{
    moveDirection = 0;
    move.stop();
}

QString Controller::showScore()
{
    return QString::number(score());
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
    connect(newBullet, &Bullet::bulletDestroyed, this, &Controller::deleteBullet);
    emit bulletChanged();
    qInfo() << "Fired Bullet";
}

void Controller::deleteBullet(Bullet *bullet)
{
    int index = bulletList.indexOf(bullet);
    if(index != -1){
        delete bulletList[index];
        bulletList.removeAt(index);
        emit bulletChanged();
        qInfo() << "Destroyed Bullet";
    }
}

void Controller::createEnemy()
{
    Enemy* newEnemy = new Enemy();
    newEnemy->setX(rand() % 1512);
    newEnemy->setY(0);
    enemyList.append(newEnemy);

    startE.start(1000 + rand() % 2000);
    emit enemyChanged();
    qInfo() << "Enemy Created";
}

void Controller::deleteEnemy(Enemy* enemy)
{
    int index = enemyList.indexOf(enemy);
    if(index != -1){
        delete enemyList[index];
        enemyList.removeAt(index);
        emit enemyChanged();
        qInfo() << "Destroyed Enemy";
    }
}

void Controller::checkCollision()
{
    for(int i = bulletList.size() - 1; i >= 0; i--)
    {
        Bullet* bullet = bulletList[i];

        for(int j = enemyList.size() - 1; j >= 0; j--)
        {
            Enemy* enemy = enemyList[j];

            double bulletLeft = bullet->x();
            double bulletRight = bullet->x() + 10;
            double bulletTop = bullet->y();
            double bulletBottom = bullet->y() + 30;

            double enemyLeft = enemy->x();
            double enemyRight = enemy->x() + 40;
            double enemyTop = enemy->y();
            double enemyBottom = enemy->y() + 40;

            if (bulletRight > enemyLeft &&
                bulletLeft < enemyRight &&
                bulletBottom > enemyTop &&
                bulletTop < enemyBottom)
            {
                deleteBullet(bullet);
                deleteEnemy(enemy);
                setScore(score() + 10);
                break;
            }
        }
    }
}

void Controller::updateState()
{
    m_y += ySpeed;
    ySpeed += gravity;

    if(m_y > bottomY)
    {
        m_y = bottomY;
    }

    checkCollision();
    emit yChanged();
}
