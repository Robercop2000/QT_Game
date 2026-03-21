#include "Controller.h"

Controller::Controller(QObject* parent) : m_x(1512/2 - 50), m_y(952-50), xSpeed(10), minX(0), maxX(1512), bottomY(952-50)
{
    connect(&time, &QTimer::timeout, this, &Controller::updateState);
    time.start(16);
}
