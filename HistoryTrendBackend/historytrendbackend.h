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
    double leftMargin{0};
    double recWidth{0};
    QList<QPointF> linePointList{};
};

class HistoryTrendBackend : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(qreal plotWidth READ getPlotWidth FINAL CONSTANT)
    Q_PROPERTY(qreal plotHeight READ getPlotHeight FINAL CONSTANT)
    Q_PROPERTY(int timeInterval READ getTimeInterval NOTIFY timeIntervalChanged FINAL)
    Q_PROPERTY(const QList<PlotLine> &plotLineList READ getPlotLineList FINAL CONSTANT)

public:
    explicit HistoryTrendBackend(QObject *parent = nullptr);

signals:
    void updatePlot(double offset);
    void timeIntervalChanged(int interval);

public slots:
    void timeIntervalChangedSlot(int interval) { timeInteval = interval; };

public:
    qreal getPlotWidth() const { return plotWidth; }
    qreal getPlotHeight() const { return plotHeight; }
    int getTimeInterval() { return timeInteval; }
    const QList<PlotLine> &getPlotLineList() const { return plotLineList; }

    //plot param
    const qreal plotWidth{669.396};
    const qreal plotHeight{59};
    //hours
    int timeInteval{6};

    double widthOfPerSec{timeInteval * 60 * 60 / plotWidth};
    QList<PlotLine> plotLineList;

    void generatingData();
};

#endif // HISTORYTRENDBACKEND_H
