#ifndef DRAWSTATSCHART_H
#define DRAWSTATSCHART_H

#include <QDialog>
#include "common.h"
#include <QChart>
#include <QBarSet>

namespace Ui {
class DrawStatsChart;
}

class DrawStatsChart : public QDialog
{
    Q_OBJECT

public:
    explicit DrawStatsChart(QSqlDatabase &database, QWidget *parent = nullptr);
    ~DrawStatsChart();

    void drawOverallStats();
    void drawTodayStats();
    void drawLastWeekStats();
    void drawLastMonthStats();

private:
    Ui::DrawStatsChart *ui;

    void createAndAddLineSeries(QSqlDatabase *connection,
                                All_Languges lesson_mode, QChart *chart);

    void appendDatatoBarSet(QSqlDatabase *connection,
                            QBarSet *set, const QString &user_query);

    void drawBarChart(const QString &title,
                      const QString &eng_query, const QString &swe_query);

    QSqlDatabase *db;
};

#endif // DRAWSTATSCHART_H
