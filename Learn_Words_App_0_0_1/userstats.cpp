#include "userstats.h"
#include "ui_userstats.h"

UserStats::UserStats(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UserStats)
{
    ui->setupUi(this);
}

UserStats::~UserStats()
{
    delete ui;
}

void UserStats::createChart(statsMode mode)
{
    stats_chart = std::make_unique<DrawStatsChart>(this);
    stats_chart->setGeometry(0, 0,
                             static_cast<int>(Sizes::STATS_CHART_WIDTH),
                             static_cast<int>(Sizes::STATS_CHART_HEIGHT));

    switch (mode) {
    case statsMode::TODAY:
        stats_chart->drawTodayStats();
        break;

    case statsMode::LAST_WEEK:
        stats_chart->drawLastWeekStats();
        break;

    case statsMode::LAST_MONTH:
        stats_chart->drawLastMonthStats();
        break;

    case statsMode::OVERALL:
        stats_chart->drawOverallStats();
        break;

    }

    stats_chart->show();
}

void UserStats::on_today_res_Button_clicked()
{
    // creating a chart
    createChart(statsMode::TODAY);
}


void UserStats::on_last_week_res_Button_clicked()
{
    // creating a chart
    createChart(statsMode::LAST_WEEK);
}


void UserStats::on_last_month_res_Button_clicked()
{
    // creating a chart
    createChart(statsMode::LAST_MONTH);
}


// Method shows total success
void UserStats::on_overall_res_Button_clicked()
{
    // creating a chart
    createChart(statsMode::OVERALL);
}
