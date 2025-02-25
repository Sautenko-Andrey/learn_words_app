#ifndef DRAWSTATSCHART_H
#define DRAWSTATSCHART_H

#include <QDialog>
#include "common.h"
#include <QChart>
#include <QBarSet>
#include <QBarSeries>
#include <QChartView>
#include <QSqlQuery>
#include "ui_drawstatschart.h"


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

    template<typename T>
    void appendDataToBarSet(QSqlDatabase *connection,
                            QBarSet *set,
                            T &&user_query);

    template<typename T>
    void drawBarChart(T &&title, T &&eng_query, T &&swe_query);

    QSqlDatabase *db;
};


template<typename T>
void DrawStatsChart::drawBarChart(T &&title, T &&eng_query, T &&swe_query)
{
    auto eng_set = new QBarSet("ENG");
    auto swe_set = new QBarSet("SWE");

    appendDataToBarSet(db, eng_set, std::forward<T>(eng_query));
    appendDataToBarSet(db, swe_set, std::forward<T>(swe_query));

    QBarSeries *series = new QBarSeries;
    series->append(eng_set);
    series->append(swe_set);

    auto chart = new QChart;
    chart->addSeries(series);
    chart->setTitle(std::forward<T>(title));
    chart->createDefaultAxes();
    chart->setTheme(QChart::ChartTheme::ChartThemeBlueCerulean);
    chart->legend()->setAlignment(Qt::AlignmentFlag::AlignBottom);

    QChartView *view = new QChartView(chart);
    view->setParent(ui->horizontalFrame);
}


template<typename T>
void DrawStatsChart::appendDataToBarSet(QSqlDatabase *connection,
                                        QBarSet *set,
                                        T &&user_query)
{
    if(connection && set){
        QSqlQuery query(*connection);
        if(!query.exec(std::forward<T>(user_query))){
            QMessageBox::warning(this, "Error!",
                                     "Can't get statistics. Try one more time.");
            return;
        }

        if(query.next()){
            *set << query.value(0).toDouble();
        }
    }
}

#endif // DRAWSTATSCHART_H
