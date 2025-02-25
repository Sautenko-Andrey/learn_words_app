#include "drawstatschart.h"
#include "ui_drawstatschart.h"
#include <QtCharts>
#include <QLineSeries>
#include <QtSql>
#include <QMessageBox>


DrawStatsChart::DrawStatsChart(QSqlDatabase &database, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DrawStatsChart)
{
    ui->setupUi(this);

    // pointer on the database
    db = &database;
}

DrawStatsChart::~DrawStatsChart()
{
    delete ui;
}


void DrawStatsChart::createAndAddLineSeries(QSqlDatabase *connection,
                                            All_Languges lesson_mode, QChart *chart)
{
    if(connection && chart){
        QString mode{};
        (lesson_mode == All_Languges::ENG) ? mode = "eng" : mode = "swe";

        QSqlQuery query(*connection);
        query.prepare("SELECT success FROM Stats WHERE mode = :user_mode");
        query.bindValue(":user_mode", mode);

        if(!query.exec()){
            QMessageBox::warning(this, "Error!",
                                 "Can't get statistics. Try one more time.");
            return;
        }

        // creating series
        auto series = new QLineSeries();
        series->setName(std::move(mode));

        int i{1};
        while(query.next()){
            series->append(i, query.value(0).toDouble());
            ++i;
        }

        chart->addSeries(series);
    }
}


void DrawStatsChart::drawOverallStats()
{
    // creating a chart
    auto chart = new QChart;

    // creating and adding series to chart
    createAndAddLineSeries(db, All_Languges::ENG, chart);
    createAndAddLineSeries(db, All_Languges::SWE, chart);

    chart->createDefaultAxes();
    chart->setTitle("Overall stats");
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignmentFlag::AlignBottom);
    chart->setTheme(QChart::ChartTheme::ChartThemeBlueCerulean);

    // creating a chartview
    auto chartview = new QChartView(chart);
    chartview->setParent(ui->horizontalFrame);
}


void DrawStatsChart::drawTodayStats()
{
    drawBarChart(
        QString("Today stats"),

        QString("SELECT round(avg(success), 2) FROM Stats "
                       "WHERE mode = 'eng' and DATE(session_time) = DATE('now')"),

        QString("SELECT round(avg(success), 2) FROM Stats "
                       "WHERE mode = 'swe' and DATE(session_time) = DATE('now')")
    );
}


void DrawStatsChart::drawLastWeekStats()
{
    drawBarChart(
        QString("Last week stats"),

        QString("SELECT round(avg(success), 2) FROM Stats "
        "WHERE mode = 'eng' AND session_time BETWEEN datetime('now', '-6 days') "
                       "AND datetime('now', 'localtime')"),

        QString("SELECT round(avg(success), 2) FROM Stats "
        "WHERE mode = 'swe' AND session_time BETWEEN datetime('now', '-6 days') "
                       "AND datetime('now', 'localtime')")
    );
}


void DrawStatsChart::drawLastMonthStats()
{
    drawBarChart(
        QString("Last month stats"),

        QString("SELECT round(avg(success), 2) FROM Stats "
        "WHERE mode = 'eng' AND session_time BETWEEN datetime('now', 'start of month') "
                       "AND datetime('now', 'localtime')"),

        QString("SELECT round(avg(success), 2) FROM Stats "
        "WHERE mode = 'swe' AND session_time BETWEEN datetime('now', 'start of month') "
                       "AND datetime('now', 'localtime')")
    );
}
