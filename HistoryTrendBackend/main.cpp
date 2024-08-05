#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "historytrendbackend.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    HistoryTrendBackend backend{};

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("historyTrendBackend", &backend);
    const QUrl url(QStringLiteral("qrc:/HistoryTrendBackend/Main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
