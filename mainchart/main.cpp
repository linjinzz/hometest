#include <QApplication>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "PointList.h"
#include "PointStrcut.h"
#include <cmath>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    const int DATA_POINTS = 10000;
    const qreal X_MIN = 0;
    const qreal X_MAX = 100;

    const qreal Y_MIN = 40;
    const qreal Y_MAX = 120;

    qreal x_step = (X_MAX - X_MIN) / (DATA_POINTS - 1);
    qreal amplitude = (Y_MAX - Y_MIN) / 2;
    qreal offset = Y_MIN + amplitude;

    QList<PointList> arrayList;

    PointList pArrayList1;
    pArrayList1.lineColor = "#787878";

    PointList pArrayList2;
    pArrayList2.lineColor = "#FAB700";

    PointList pArrayList3;
    pArrayList3.lineColor = "#DE3835";

    for (int i = 0; i < DATA_POINTS; ++i) {
        QPointF pStruct;

        pStruct.setX(X_MIN + i * x_step);
        pStruct.setY(amplitude * sin(2 * M_PI * pStruct.x() / (X_MAX / 2)) + offset);

        if (i < 3000) {
            pArrayList1.linePoints.append(pStruct);
        }

        if (3000 < i && i < 6000) {
            pArrayList2.linePoints.append(pStruct);
        }

        if (6000 < i) {
            pArrayList3.linePoints.append(pStruct);
        }
    }

    QQmlApplicationEngine engine;
    arrayList.append(pArrayList1);
    arrayList.append(pArrayList2);
    arrayList.append(pArrayList3);

    engine.rootContext()->setContextProperty("myList", QVariant::fromValue(arrayList));

    const QUrl url(QStringLiteral("qrc:/mainchart/Main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
