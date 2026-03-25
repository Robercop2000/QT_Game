#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "core/Controller.h"

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    Controller control;
    engine.rootContext()->setContextProperty("control", &control);

    engine.loadFromModule("GameQT", "main");

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
