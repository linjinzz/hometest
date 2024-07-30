#ifndef HISTORYTRENDBACKEND_H
#define HISTORYTRENDBACKEND_H

#include <QObject>
#include <QPointF>
#include <QQmlEngine>

class PlotLine : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit PlotLine(QObject *parent = nullptr){};

    Q_PROPERTY(QString lineColor READ GetLineColor CONSTANT)
    Q_PROPERTY(QList<QPointF> linePointList READ GetLinePointList FINAL CONSTANT)

    QString GetLineColor() const { return lineColor; }
    QList<QPointF> GetLinePointList() const { return linePointList; }

private:
    QString lineColor;
    QList<QPointF> linePointList;
};

class HistoryTrendBackend : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(qreal plotWidth READ GetPlotWidth FINAL CONSTANT)
    Q_PROPERTY(qreal plotHeight READ GetPlotHeight FINAL CONSTANT)
    Q_PROPERTY(QList<PlotLine> plotLineList READ GetPlotLineList FINAL CONSTANT)

public:
    explicit HistoryTrendBackend(QObject *parent = nullptr);

signals:
    void updatePlot(double offset);

public:
    qreal GetPlotWidth() const { return plotWidth; }
    qreal GetPlotHeight() const { return plotHeight; }
    QList<PlotLine> GetPlotLineList() const { return plotLineList; }

private:
    const qreal plotWidth{669.396};
    const qreal plotHeight{59};
    QList<PlotLine> plotLineList;
};

#endif // HISTORYTRENDBACKEND_H
