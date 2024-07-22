#ifndef POINTLIST_H
#define POINTLIST_H

#include <QGuiApplication>
#include <QList>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QString>
#include <QVector>
//#include "PointStrcut.h"
struct PointList
{
    Q_GADGET
public:
    QList<QPointF> linePoints;
    QString lineColor;

    Q_PROPERTY(QList<QPointF> linePoints MEMBER linePoints)
    Q_PROPERTY(QString lineColor MEMBER lineColor)
};

#endif // POINTLIST_H
