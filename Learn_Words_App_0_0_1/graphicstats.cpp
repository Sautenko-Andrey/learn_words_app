#include "graphicstats.h"
#include "ui_graphicstats.h"
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>

GraphicStats::GraphicStats(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GraphicStats)
{
    ui->setupUi(this);

    auto series = new QLineSeries;
    series->append(10, 10);
    series->append(20, 20);
    series->append(30, 30);
    series->append(40, 40);
    series->append(50, 50);

    auto chart = new QChart;

    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Stats");

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignmentFlag::AlignBottom);

    auto chartview = new QChartView(chart);
    chartview->setParent(ui->horizontalFrame);
}

GraphicStats::~GraphicStats()
{
    delete ui;
}
