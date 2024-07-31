#include <QApplication>
#include <QDebug>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "PointList.h"
#include <cmath>

enum Category { Category1, Category2, Category3, CategoryNone };

Category categorize(qreal y)
{
    if (y < 80)
        return Category1;
    if (y < 100)
        return Category2;
    return Category3;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    const int DATA_POINTS = 10000;
    const qreal X_MIN = 0;
    const qreal X_MAX = 100;
    const qreal Y_MIN = 40;
    const qreal Y_MAX = 120;

    const qreal x_step = (X_MAX - X_MIN) / (DATA_POINTS - 1);
    const qreal amplitude = (Y_MAX - Y_MIN) / 2;
    const qreal offset = Y_MIN + amplitude;

    QList<PointList> arrayList;

    PointList pArrayList1;
    pArrayList1.lineColor = "#787878";
    PointList pArrayList2;
    pArrayList2.lineColor = "#FAB700";
    PointList pArrayList3;
    pArrayList3.lineColor = "#DE3835";
    PointList *currentList = nullptr;

    Category lastCategory = CategoryNone;

    for (int i = 0; i < DATA_POINTS; ++i) {
        QPointF point;
        point.setX(X_MIN + i * x_step);
        point.setY(amplitude * sin(2 * M_PI * point.x() / (X_MAX / 2)) + offset);

        Category currentCategory = categorize(point.y());
        PointList *targetList = nullptr;

        switch (currentCategory) {
        case Category1:
            targetList = &pArrayList1;
            break;
        case Category2:
            targetList = &pArrayList2;
            break;
        case Category3:
            targetList = &pArrayList3;
            break;
        default:
            break;
        }

        if (targetList != currentList && currentList != nullptr
            && !currentList->linePoints.isEmpty()) {
            arrayList.append(*currentList);
            currentList->linePoints.clear();
        }

        if (targetList != nullptr) {
            targetList->linePoints.append(point);
        }

        currentList = targetList;
        lastCategory = currentCategory;
    }

    if (currentList != nullptr && !currentList->linePoints.isEmpty()) {
        arrayList.append(*currentList);
    }

    qDebug() << "Total categories:" << arrayList.length();
    for (const auto &list : arrayList) {
        qDebug() << "Color:" << list.lineColor << ", Points:" << list.linePoints.length();
    }

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("myList", QVariant::fromValue(arrayList));
    engine.load(QUrl(QStringLiteral("qrc:/mainchart/Main.qml")));

    return app.exec();
}
