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
    //for plot
    QString lineColor{};
    QList<QPointF> linePointList{};

    double leftMargin{0};
    double recWidth{0};
};

class HistoryTrendBackend : public QObject
{
    enum Category { Category1, Category2, Category3, CategoryNone };

    struct PointData
    {
        QTime x{};
        qreal y{};
    };

    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(qreal plotWidth READ getPlotWidth FINAL CONSTANT)
    Q_PROPERTY(qreal plotHeight READ getPlotHeight FINAL CONSTANT)
    Q_PROPERTY(int timeInterval READ getTimeInterval NOTIFY timeIntervalChanged FINAL)
    Q_PROPERTY(const QList<PlotLine> &plotLineList READ getPlotLineList FINAL CONSTANT)

public:
    explicit HistoryTrendBackend(QObject *parent = nullptr);

signals:
    //void updatePlot(double offset);
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

    qreal widthOfPerSec{plotWidth / qreal(timeInteval * 60 * 60)};
    QList<PlotLine> plotLineList{};
    QList<QPoint> showedPointList{};
    QList<PointData> totalPointList{};

    //for canvas plot
    QTime leftRangeTime{0, 0, 0};
    QTime rightRangeTime{6, 0, 0};

    void generatingData();
    void filterData(int leftRange, int rightRange);
    Q_INVOKABLE void updatePlot(double scrolloffset);

    Category categorize(qreal y)
    {
        if (y < 80)
            return Category1;
        if (y < 100)
            return Category2;
        return Category3;
    }
};

#endif // HISTORYTRENDBACKEND_H
