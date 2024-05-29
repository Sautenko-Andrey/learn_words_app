#include "drawstatschart.h"
#include "ui_drawstatschart.h"
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
#include <QBarSeries>
#include <QBarSet>
#include <QSqlQuery>
#include <QtSql>
#include <QMessageBox>

DrawStatsChart::DrawStatsChart(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DrawStatsChart)
{
    ui->setupUi(this);
}

DrawStatsChart::~DrawStatsChart()
{
    delete ui;
}

void DrawStatsChart::createAndAddLineSeries(const QSqlDatabase& connection,
                                        All_Languges lesson_mode, QChart *chart)
{
    QString mode{};
    (lesson_mode == All_Languges::ENG) ? mode = "eng" : mode = "swe";

    QSqlQuery query(connection);
    query.prepare("SELECT success FROM Stats WHERE mode = :user_mode");
    query.bindValue(":user_mode", mode);

    if(!query.exec()){
        QMessageBox::warning(this, "Error!",
                                 "Can't get statistics. Try one more time.");
        return;
    }

    // creating series
    auto series = new QLineSeries();
    series->setName(mode);

    int i{1};
    while(query.next()){
        series->append(i, query.value(0).toDouble());
        ++i;
    }

    chart->addSeries(series);
}


void DrawStatsChart::drawOverallStats()
{
    // let's make a query
    auto connectDB = db.get_my_db();

    // creating a chart
    auto chart = new QChart;

    // creating and adding series to chart
    createAndAddLineSeries(connectDB, All_Languges::ENG, chart);
    createAndAddLineSeries(connectDB, All_Languges::SWE, chart);

    chart->createDefaultAxes();
    chart->setTitle("Overall stats");
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignmentFlag::AlignBottom);
    chart->setTheme(QChart::ChartTheme::ChartThemeBlueCerulean);

    // creating a chartview
    auto chartview = new QChartView(chart);
    chartview->setParent(ui->horizontalFrame);
}

void DrawStatsChart::appendDatatoBarSet(const QSqlDatabase& connection,
                                        QBarSet *set, const QString &user_query)
{
    QSqlQuery query(connection);
    if(!query.exec(user_query)){
        QMessageBox::warning(this, "Error!",
                             "Can't get statistics. Try one more time.");
        return;
    }

    if(query.next()){
        *set << query.value(0).toDouble();
    }
}


void DrawStatsChart::drawTodayStats()
{
    auto eng_set = new QBarSet("ENG");
    auto swe_set = new QBarSet("SWE");

    // let's make a query
    auto connectDB = db.get_my_db();

    // appending data to BarSet
    appendDatatoBarSet(connectDB, eng_set,
                       "SELECT ROUND(success, 2) FROM Stats "
                       "WHERE mode = 'eng' and DATE(session_time) = DATE('now')");
    appendDatatoBarSet(connectDB, swe_set,
                       "SELECT ROUND(success, 2) FROM Stats "
                       "WHERE mode = 'swe' and DATE(session_time) = DATE('now')");

    QBarSeries *series = new QBarSeries;
    series->append(eng_set);
    series->append(swe_set);

    auto chart = new QChart;
    chart->addSeries(series);
    chart->setTitle("Today statistics");
    chart->createDefaultAxes();
    chart->setTheme(QChart::ChartTheme::ChartThemeBlueCerulean);

    QChartView *view = new QChartView(chart);
    view->setParent(ui->horizontalFrame);
}


void DrawStatsChart::drawLastWeekStats()
{

}


void DrawStatsChart::drawLastMonthStats()
{

}
