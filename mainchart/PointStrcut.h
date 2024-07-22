#ifndef PointStruct_H
#define PointStruct_H
#include <QGuiApplication>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QString>
#include <QVector>

struct PointStruct
{
    Q_GADGET
public:
    qreal xValue;
    qreal yValue;

    Q_PROPERTY(qreal xValue MEMBER xValue)
    Q_PROPERTY(qreal yValue MEMBER yValue)
};

#endif // PointStruct_H
