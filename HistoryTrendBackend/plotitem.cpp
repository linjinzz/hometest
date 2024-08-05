#include "plotitem.h"
#include <QPainterPath>

PlotItem::PlotItem() {}

void PlotItem::setData(const QList<PlotLine> &lineList)
{
    plotLineList = lineList;
    update();
}

void PlotItem::paint(QPainter *painter)
{
    painter->fillRect(boundingRect(), Qt::white);
    painter->setRenderHint(QPainter::Antialiasing);

    for (auto line : plotLineList) {
        QPen pen;
        pen.setColor(line.lineColor); // 设置颜色
        pen.setWidth(4);

        QPainterPath path;

        if (!line.linePointList.isEmpty()) {
            path.moveTo(line.linePointList[0]);
            for (int i = 1; i < line.linePointList.size(); ++i) {
                path.lineTo(line.linePointList[i]);
            }
        }

        painter->drawPath(path);
    }
}
