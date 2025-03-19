#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "dashboardmanager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    // QObject::connect(
    //     &engine,
    //     &QQmlApplicationEngine::objectCreationFailed,
    //     &app,
    //     []() { QCoreApplication::exit(-1); },
    //     Qt::QueuedConnection);
    // engine.loadFromModule("car-dashboard", "Main");

    DashboardManager dashboardManager;
    engine.rootContext()->setContextProperty("dashboardManager", &dashboardManager);

    engine.load(QUrl("qrc:/CarDashboard/qml/Main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("car-dashboard", "Main");

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
