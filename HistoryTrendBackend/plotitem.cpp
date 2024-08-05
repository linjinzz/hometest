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

    qreal itemWidth = boundingRect().width();
    qreal itemHeight = boundingRect().height();

    // Draw a 1px height rectangle in the middle of the item
    QRect middleRect(0, itemHeight / 2, itemWidth, 1);
    painter->fillRect(middleRect, Qt::black);

    // Draw vertical rectangles every 20px next to the middle rectangle
    for (int i = 0; i < itemWidth; i += 20) {
        QRect verticalRect(i, itemHeight / 2 + 1, 1, 4);
        painter->fillRect(verticalRect, Qt::black);
    }

    // Draw text "123" below the middle rectangle
    QFont font = painter->font();
    font.setPixelSize(12); // Set font size
    painter->setFont(font);

    QRect textRect = QRect(-5, 0, 20,
                           20); // Position the text below the rectangles
    painter->drawText(textRect, Qt::AlignCenter, "123");
}
