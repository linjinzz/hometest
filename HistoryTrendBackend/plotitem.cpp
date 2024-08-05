#include "plotitem.h"
#include <QPainterPath>
#include <QTime>
PlotItem::PlotItem() {}

void PlotItem::setData(const QList<PlotLine> &lineList)
{
    plotLineList = lineList;

    QTime lastTime = QTime::currentTime();
    update();

    QTime secondTime = QTime::currentTime();
    qDebug() << "paint 花费时间: " << lastTime.msecsTo(secondTime);
    qDebug() << "      ";
}

void PlotItem::paint(QPainter *painter)
{
    static const QColor backgroundColor = QColor(
        "#E8E8E8"); // Set background color as static for efficiency
    static const QPen defaultPen(QColor(Qt::black), 4); // Default pen with color and width

    painter->fillRect(boundingRect(), backgroundColor);
    painter->setRenderHint(QPainter::Antialiasing);

    for (const auto &line : plotLineList) {
        QPen pen = defaultPen;        // Use the default pen
        pen.setColor(line.lineColor); // Set line color

        painter->setPen(pen);

        QPainterPath path;
        path.addPolygon(QPolygonF(line.linePointList)); // Construct path with all points at once

        painter->drawPath(path);
    }
}
