#include "userstats.h"
#include "ui_userstats.h"
#include <QSqlQuery>
#include <QMessageBox>

UserStats::UserStats(QSqlDatabase &database, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UserStats)
{
    ui->setupUi(this);

    // pointer on the databse
    db = &database;

    // initializing DrawStatsChart class object
    stats_chart = std::make_unique<DrawStatsChart>(database, this);

}

UserStats::~UserStats()
{
    delete ui;
}

void UserStats::createChart(statsMode mode)
{
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

void UserStats::on_dropStatsButton_clicked()
{
    // drop all stats

    QMessageBox::StandardButton reply;

    reply = QMessageBox::question(this, "Confirmation", "Wanna delete all stats?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes){

        QSqlQuery deleteAllQuery(*db);

        if(!deleteAllQuery.exec("DELETE FROM Stats")){
            QMessageBox::warning(this, "Error",
                                 "Error occured when deleting all stats from thr database");
            close();
        }

        QMessageBox::information(this, "Report", "All statistic has been removed.");

        close();
    }
}

