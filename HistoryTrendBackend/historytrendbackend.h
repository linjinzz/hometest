#ifndef HISTORYTRENDBACKEND_H
#define HISTORYTRENDBACKEND_H

#include <QObject>
#include <QPointF>
#include <QQmlEngine>

struct PlotLine
{
    Q_GADGET

public:
    Q_PROPERTY(QString lineColor READ GetLineColor CONSTANT)
    Q_PROPERTY(QList<QPointF> linePointList READ GetLinePointList FINAL CONSTANT)

    QString GetLineColor() const { return lineColor; }
    QList<QPointF> GetLinePointList() const { return linePointList; }

public:
    QString lineColor{};
    QList<QPointF> linePointList{};
};

class HistoryTrendBackend : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(qreal plotWidth READ GetPlotWidth FINAL CONSTANT)
    Q_PROPERTY(qreal plotHeight READ GetPlotHeight FINAL CONSTANT)
    Q_PROPERTY(const QList<PlotLine> &plotLineList READ GetPlotLineList FINAL CONSTANT)

public:
    explicit HistoryTrendBackend(QObject *parent = nullptr);

signals:
    void updatePlot(double offset);

public:
    qreal GetPlotWidth() const { return plotWidth; }
    qreal GetPlotHeight() const { return plotHeight; }
    const QList<PlotLine> &GetPlotLineList() const { return plotLineList; }

public:
    const qreal plotWidth{669.396};
    const qreal plotHeight{59};
    QList<PlotLine> plotLineList;
};

#endif // HISTORYTRENDBACKEND_H
