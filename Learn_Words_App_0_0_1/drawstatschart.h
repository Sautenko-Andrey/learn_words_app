#ifndef DRAWSTATSCHART_H
#define DRAWSTATSCHART_H

#include <QDialog>
#include "common.h"
#include <QVector>

namespace Ui {
class DrawStatsChart;
}

class DrawStatsChart : public QDialog
{
    Q_OBJECT

public:
    explicit DrawStatsChart(QWidget *parent = nullptr);
    ~DrawStatsChart();

    void drawOverallStats();
    void drawTodayStats() const;
    void drawLastWeekStats() const;
    void drawLastMonthStats() const;

private:
    Ui::DrawStatsChart *ui;
    OpenDB db;
    QVector<double> successContainer;
};

#endif // DRAWSTATSCHART_H
