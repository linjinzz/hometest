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

        QTime time = QTime::fromMSecsSinceStartOfDay(i * 1000);

        //qDebug() << "current point time" << time;

        totalPointList.push_back(PointData{time, value});
    }
}

void HistoryTrendBackend::filterData(int leftRange, int rightRange)
{

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

        if (targetList != currentList && currentList != nullptr
            && !currentList->linePointList.isEmpty()) {
            currentList->recWidth = currentList->linePointList.last().x()
                                    - currentList->linePointList.first().x();
            currentList->leftMargin = currentList->linePointList.first().x();

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
}

void HistoryTrendBackend::updatePlot(double scrolloffset)
{
    double interval = (scrolloffset / plotWidth) * 6 * 60 * 60;

    QTime leftRangeLimit{0, 0, 0, 0};
    QTime righRnageLimit{12, 0, 0, 0};

    int leftRangeTimeToSecond = leftRangeTime.msecsSinceStartOfDay() / 1000;

    int rightRangeTimeToSecond = rightRangeTime.msecsSinceStartOfDay() / 1000;

    if ((leftRangeTimeToSecond + interval) <= 0) {
        leftRangeTime = leftRangeLimit;
        rightRangeTime = rightRangeTime.addSecs(-leftRangeTimeToSecond);
    } else if ((rightRangeTimeToSecond + interval) >= righRnageLimit.msecsSinceStartOfDay() / 1000) {
        rightRangeTime = righRnageLimit;
        leftRangeTime = leftRangeTime.addSecs(rightRangeTime.secsTo(righRnageLimit));
    } else {
        leftRangeTime = leftRangeTime.addSecs(interval);
        rightRangeTime = rightRangeTime.addSecs(interval);
    }

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

        if (rightRangeTime <= totalPointList[i].x || i == totalPointList.length() - 1) {
            righRange = i;
            break;
        }
    }

    filterData(leftRange, righRange);

    //QTime lastTime = QTime::currentTime();
}
