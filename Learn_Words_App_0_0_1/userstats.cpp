#include "userstats.h"
#include "ui_userstats.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>

UserStats::UserStats(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UserStats)
{
    ui->setupUi(this);

    // Open DB with stats
    QSqlQuery all_stats_query(db.get_my_db());

    if(!all_stats_query.exec("SELECT session_time, mode, success FROM Stats")){
        qDebug() << "Couldn't open DB for reading stats data!";
        return;
    }

    // Saving data in the container
    while(all_stats_query.next()){
        // Here will be data saving
        qDebug() << all_stats_query.value(0) <<
                " " << all_stats_query.value(1)
                 << " " << all_stats_query.value(2);
    }
}

UserStats::~UserStats()
{
    delete ui;
}

void UserStats::on_today_res_Button_clicked()
{
    QMessageBox::information(this, "Today's result", "100%");
}


void UserStats::on_last_week_res_Button_clicked()
{
    QMessageBox::information(this, "Last week result", "100%");
}


void UserStats::on_last_month_res_Button_clicked()
{
    QMessageBox::information(this, "Last month result", "100%");
}


void UserStats::on_overall_res_Button_clicked()
{
    QMessageBox::information(this, "Total result", "100%");
}

