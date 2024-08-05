#include "plotitem.h"
#include <QPainterPath>
#include <QTime>
PlotItem::PlotItem() {}

void PlotItem::setData(const QList<PlotLine> &lineList)
{
    QTime lastTime = QTime::currentTime();

    plotLineList = lineList;

    QTime secondTime = QTime::currentTime();
    qDebug() << "setData 花费时间: " << lastTime.msecsTo(secondTime);

    update();

    // QTime thirdTime = QTime::currentTime();
    // qDebug() << "paint 花费时间: " << secondTime.msecsTo(thirdTime);
}

void PlotItem::paint(QPainter *painter)
{
    //QColor backgroundColor = QColor("#E8E8E8").darker(30); // 100 + 30% = 130
    painter->fillRect(boundingRect(), QColor("#E8E8E8"));
    painter->setRenderHint(QPainter::Antialiasing); // 只需设置一次

    QPen pen;
    pen.setWidth(4); // 假设所有线宽都一样，如果不同，可以在循环内设置

    for (const auto &line : plotLineList) {
        pen.setColor(line.lineColor); // 设置颜色
        painter->setPen(pen);         // 将笔设置给 QPainter

        QPainterPath path;
        path.moveTo(line.linePointList[0]);
        for (int i = 1; i < line.linePointList.size(); ++i) {
            path.lineTo(line.linePointList[i]);
        }

        painter->drawPath(path);
    }
}
