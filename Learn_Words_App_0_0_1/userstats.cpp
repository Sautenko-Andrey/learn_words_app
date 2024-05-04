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


// Method shows total success
void UserStats::on_overall_res_Button_clicked()
{
    QSqlQuery all_stats_query(db.get_my_db());
    // Select both english and swedish lessons stats
    if(!all_stats_query.exec("SELECT round(avg(success), 2) FROM Stats GROUP BY mode")){
        qDebug() << "Couldn't open DB for reading stats data!";
        return;
    }

    if(all_stats_query.next()){
        QMessageBox::information(this, "Total result",
        "English: " + all_stats_query.value(0).toString() + " %,"
        "\nSwedish: " + all_stats_query.value(1).toString() + " %");
    }
}
