#include "historytrendbackend.h"

HistoryTrendBackend::HistoryTrendBackend(QObject *parent)
    : QObject{parent}
{
    generatingData();
    updatePlot(0);
}

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
        double xPos = static_cast<double>(i); // 每秒一个数据点
        double angle = 2 * PI * FREQUENCY * xPos;
        double value = AMPLITUDE * std::sin(angle) + OFFSET;

        QTime time{i / (60 * 60), (i % (60 * 60)) / 60, i % 60, 0};

        //qDebug() << "time: " << time << " y: " << value;

        totalPointList.push_back(PointData{time, value});
    }
}

void HistoryTrendBackend::filterData(int leftRange, int rightRange)
{
    //qDebug() << "每秒间隔宽度" << widthOfPerSec;\

    QTime firstTime = QTime::currentTime();

    plotLineList.clear();

    PlotLine pArrayList1;
    pArrayList1.lineColor = "#787878";

    PlotLine pArrayList2;
    pArrayList2.lineColor = "#FAB700";

    PlotLine pArrayList3;
    pArrayList3.lineColor = "#DE3835";

    PlotLine *currentList = nullptr;

    Category lastCategory = CategoryNone;

    for (int i = leftRange; i <= rightRange; ++i) {
        PointData &pointData = totalPointList[i];

        Category currentCategory = categorize(pointData.y);
        PlotLine *targetList = nullptr;

        switch (currentCategory) {
        case Category1:
            targetList = &pArrayList1;
            break;
        case Category2:
            targetList = &pArrayList2;
            break;
        case Category3:
            targetList = &pArrayList3;
            break;
        default:
            break;
        }

        qreal secon = leftRangeTime.secsTo(pointData.x);

        qreal xPos = secon * widthOfPerSec;
        qreal yPos = plotHeight - (pointData.y - 40) / (120 - 40) * plotHeight;

        //qDebug() << "x: " << xPos << "y: " << yPos;

        //qDebug() << "x: " << xPos << "y: " << yPos;

        if (targetList != currentList && currentList != nullptr
            && !currentList->linePointList.isEmpty()) {
            plotLineList.append(*currentList);
            currentList->linePointList.clear();
        }

        if (targetList != nullptr) {
            targetList->linePointList.append({xPos, yPos});
        }

        currentList = targetList;
        //lastCategory = currentCategory;
    }

    if (currentList != nullptr && !currentList->linePointList.isEmpty()) {
        plotLineList.append(*currentList);
    }

    QTime lastTime = QTime::currentTime();

    // qDebug() << "firstTime" << firstTime;
    // qDebug() << "lastTime" << lastTime;

    // qDebug() << "花费时间" << firstTime.msecsTo(lastTime);
}

void HistoryTrendBackend::updatePlot(double scrolloffset)
{
    QTime firstTime = QTime::currentTime();
    double interval = (std::abs(scrolloffset) / plotWidth) * 6 * 60 * 60;

    //qDebug() << "当前移动秒数: " << interval;

    leftRangeTime = leftRangeTime.addSecs(interval);
    rightRangeTime = rightRangeTime.addSecs(interval);

    // // if (QTime{0, 0, 0, 0} < leftRangeTime.addSecs(interval)) {
    //     leftRangeTime = QTime{0, 0, 0, 0};
    // // } else {
    //     leftRangeTime = leftRangeTime.addSecs(interval);
    // }

    // if (QTime{12, 0, 0, 0} < rightRangeTime.addSecs(interval)) {
    //     rightRangeTime = QTime{12, 0, 0, 0};
    // } else {
    //     rightRangeTime = rightRangeTime.addSecs(interval);
    // }

    int leftRange{0};
    int righRange{0};
    bool leftInit{false};

    for (int i = 0; i < totalPointList.length(); ++i) {
        if (leftRangeTime > totalPointList[i].x) {
            continue;
        } else {
            if (!leftInit) {
                leftInit = true;
                leftRange = i;
            }
        }

        if (rightRangeTime < totalPointList[i].x) {
            righRange = i;
            break;
        }
    }

    //qDebug() << leftRange << righRange;

    filterData(leftRange, righRange);

    QTime lastTime = QTime::currentTime();

    // qDebug() << "firstTime" << firstTime;
    // qDebug() << "lastTime" << lastTime;

    // qDebug() << "花费时间" << firstTime.msecsTo(lastTime);
}
