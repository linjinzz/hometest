#ifndef HISTORYTRENDBACKEND_H
#define HISTORYTRENDBACKEND_H
#include <QObject>
#include <QPointF>
#include <QQmlEngine>

class PlotPoint : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit PlotPoint(QObject *parent = nullptr);

    Q_PROPERTY(QString lineColor READ GetLineColor CONSTANT)
    Q_PROPERTY(type linePointList READ GetLinePointList FINAL CONSTANT)

private:
    QString &GetLineColor() { return lineColor; };
    QList<QPointF> &GetLinePointList() { return linePointList; };

    QString lineColor;
    QList<QPointF> linePointList;
};

class HistoryTrendBackend : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(qreal plotWidth READ GetPlotWidth FINAL CONSTANT)
    Q_PROPERTY(qreal plotHeight READ GetPlotHeidth FINAL CONSTANT)
    Q_PROPERTY(QList<PlotPoint> plotLineList READ GetPlotLineList FINAL CONSTANT)

public:
    explicit HistoryTrendBackend(QObject *parent = nullptr);

signals:
    void updatePlot(double offset);

public:
    qreal GetPlotWidth() const { return plotWidth; };
    qreal GetPlotHeidth() const { return plotHeight; };
    QList<PlotPoint> &GetPlotLineList() { return plotLineList; };

private:
    const qreal plotWidth{0};
    const qreal plotHeight{0};
    QList<PlotPoint> plotLineList{};
};

#endif // HISTORYTRENDBACKEND_H
