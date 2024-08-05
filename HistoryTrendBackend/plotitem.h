#ifndef PLOTITEM_H
#define PLOTITEM_H
#include <QColor>
#include <QPainter>
#include <QtQuick/QQuickPaintedItem>
#include "historytrendbackend.h"
class PlotItem : public QQuickPaintedItem
{
    Q_OBJECT
    QML_ELEMENT
public:
    PlotItem();

public:
    Q_INVOKABLE void setData(const QList<PlotLine> &lineList);
    void paint(QPainter *painter) override;

private:
    QList<PlotLine> plotLineList;
};

#endif // PLOTITEM_H
