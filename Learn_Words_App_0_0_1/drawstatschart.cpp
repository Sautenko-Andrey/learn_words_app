#include "drawstatschart.h"
#include "ui_drawstatschart.h"
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
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


void DrawStatsChart::drawOverallStats()
{
    // let's make a query
    auto connectDB = db.get_my_db();

    // query for english stats
    QSqlQuery eng_query(connectDB);
    if(!eng_query.exec("SELECT success FROM Stats WHERE mode = 'eng'")){
        QMessageBox::warning(this, "Error",
                             "Couldn't get data for the sessions stats");
        return;
    }

    // filling success container
    while(eng_query.next()){
        successContainer.push_back(eng_query.value(0).toDouble());
    }

    // creating series
    auto eng_series = new QLineSeries;
    for(int i{0}; i < successContainer.size(); ++i){
        eng_series->append(i + 1, successContainer[i]);
    }

    // clear container
    successContainer.clear();

    //query for swedish stats
    QSqlQuery swe_query(connectDB);
    if(!swe_query.exec("SELECT success FROM Stats WHERE mode = 'swe'")){
        QMessageBox::warning(this, "Error",
                             "Couldn't get data for the sessions stats");
        return;
    }

    // filling success container
    while(swe_query.next()){
        successContainer.push_back(swe_query.value(0).toDouble());
    }

    // creating series
    auto swe_series = new QLineSeries;
    for(int i{0}; i < successContainer.size(); ++i){
        swe_series->append(i + 1, successContainer[i]);
    }

    // creating a chart
    auto chart = new QChart;

    chart->addSeries(eng_series);
    chart->addSeries(swe_series);
    chart->createDefaultAxes();
    chart->setTitle("Overall stats");
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignmentFlag::AlignBottom);
    chart->setTheme(QChart::ChartTheme::ChartThemeDark);

    // creating a chartview
    auto chartview = new QChartView(chart);
    chartview->setParent(ui->horizontalFrame);
}


void DrawStatsChart::drawTodayStats() const
{

}


void DrawStatsChart::drawLastWeekStats() const
{

}


void DrawStatsChart::drawLastMonthStats() const
{

}
