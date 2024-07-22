#include <QApplication>
#include <QDebug>
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

    int lastCategory = 0;

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

        qDebug() << "x:" << pStruct.x() << "y:" << pStruct.y();

        if (i == 0) {
            if (40 <= pStruct.y() && pStruct.y() < 80) {
                lastCategory = 1;
            } else if (80 <= pStruct.y() && pStruct.y() < 100) {
                lastCategory = 2;
            } else if (100 <= pStruct.y()) {
                lastCategory = 3;
            }
        }

        if (40 <= pStruct.y() && pStruct.y() < 80) {
            if (lastCategory == 1) {
                pArrayList1.linePoints.append(pStruct);
            } else {
                if (lastCategory == 2 && pArrayList2.linePoints.length() > 1) {
                    arrayList.append(pArrayList2);
                    pArrayList2.linePoints.clear();
                } else if (lastCategory == 3 && pArrayList3.linePoints.length() > 1) {
                    arrayList.append(pArrayList3);
                    pArrayList3.linePoints.clear();
                }
                pArrayList1.linePoints.append(pStruct);
                lastCategory = 1;
            }
        } else if (80 <= pStruct.y() && pStruct.y() < 100) {
            if (lastCategory == 2) {
                pArrayList2.linePoints.append(pStruct);
            } else {
                if (lastCategory == 1 && pArrayList1.linePoints.length() > 1) {
                    arrayList.append(pArrayList1);
                    pArrayList1.linePoints.clear();
                } else if (lastCategory == 3 && pArrayList3.linePoints.length() > 1) {
                    arrayList.append(pArrayList3);
                    pArrayList3.linePoints.clear();
                }
                pArrayList2.linePoints.append(pStruct);
                lastCategory = 2;
            }
        } else if (100 <= pStruct.y()) {
            if (lastCategory == 3) {
                pArrayList3.linePoints.append(pStruct);
            } else {
                if (lastCategory == 1 && pArrayList1.linePoints.length() > 1) {
                    arrayList.append(pArrayList1);
                    pArrayList1.linePoints.clear();
                } else if (lastCategory == 2 && pArrayList2.linePoints.length() > 1) {
                    arrayList.append(pArrayList2);
                    pArrayList2.linePoints.clear();
                }
                pArrayList3.linePoints.append(pStruct);
                lastCategory = 3;
            }
        }
    }

    // 添加最后一组点到 arrayList
    if (lastCategory == 1 && pArrayList1.linePoints.length() > 1) {
        arrayList.append(pArrayList1);
    } else if (lastCategory == 2 && pArrayList2.linePoints.length() > 1) {
        arrayList.append(pArrayList2);
    } else if (lastCategory == 3 && pArrayList3.linePoints.length() > 1) {
        arrayList.append(pArrayList3);
    }

    qDebug() << "size:" << arrayList.length();

    for (int i{0}; i < arrayList.length(); i++) {
        qDebug() << "color:" << arrayList[i].lineColor;
        qDebug() << "child list size:" << arrayList[i].linePoints.length();
    }

    QQmlApplicationEngine engine;

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
