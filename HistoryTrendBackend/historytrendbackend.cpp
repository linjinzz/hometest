#include "historytrendbackend.h"

HistoryTrendBackend::HistoryTrendBackend(QObject *parent)
    : QObject{parent}
{}

void HistoryTrendBackend::generatingData()
{
    const double PI = 3.14159265358979323846;
    const int SECONDS_PER_HOUR = 3600;
    const int TOTAL_HOURS = 12;
    const double AMPLITUDE = 40.0;
    const double OFFSET = 80.0;
    const double FREQUENCY = 1.0 / SECONDS_PER_HOUR;

    int totalDataPoints = SECONDS_PER_HOUR * TOTAL_HOURS;

    for (int i = 0; i < totalDataPoints; ++i) {
        double time = static_cast<double>(i); // 每秒一个数据点
        double angle = 2 * PI * FREQUENCY * time;
        double value = AMPLITUDE * std::sin(angle) + OFFSET;

        totalPointList.push_back(QPointF(time, value));
    }
}

void HistoryTrendBackend::filterData() {}

void HistoryTrendBackend::updatePlot(double scrolloffset)
{
    if (scrolloffset < 0) {
        scrolloffset = std::abs(scrolloffset);
    } else {
    }

    double interval = scrolloffset * widthOfPerSec;

    auto it = std::lower_bound(totalPointList.begin(),
                               totalPointList.end(),
                               interval,
                               [](const QPointF &p, double val) { return p.y() < val; });
}
