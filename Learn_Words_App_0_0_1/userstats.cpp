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
    // make query for the both modes
    QSqlQuery today_stats_query_eng(db.get_my_db());
    QSqlQuery today_stats_query_swe(db.get_my_db());

    if(!today_stats_query_eng.exec("SELECT round(avg(success), 2) FROM Stats "
                                  "WHERE mode = 'eng' AND DATE(session_time) = DATE('now')")){
        qDebug() << "Couldn't open DB for reading eng stats today data!";
        return;
    }

    if(!today_stats_query_swe.exec("SELECT round(avg(success), 2) FROM Stats "
                                  "WHERE mode = 'swe' AND DATE(session_time) = DATE('now')")){
        qDebug() << "Couldn't open DB for reading swe stats today data!";
        return;
    }

    if(today_stats_query_eng.next() && today_stats_query_swe.next()){
        QMessageBox::information(this, "Total result",
        "English: " + today_stats_query_eng.value(0).toString() + " %,"
        "\nSwedish: " + today_stats_query_swe.value(0).toString() + " %");
    }

}


void UserStats::on_last_week_res_Button_clicked()
{
    // make query for the both modes
    QSqlQuery last_week_stats_query_eng(db.get_my_db());
    QSqlQuery last_week_stats_query_swe(db.get_my_db());

    if(!last_week_stats_query_eng.exec("SELECT round(avg(success), 2) FROM Stats "
        "WHERE mode = 'eng' AND "
        "session_time BETWEEN datetime('now', '-6 days') "
        "AND datetime('now', 'localtime')")){
        qDebug() << "Couldn't open DB for reading eng stats last week data!";
        return;
    }

    if(!last_week_stats_query_swe.exec("SELECT round(avg(success), 2) FROM Stats "
        "WHERE mode = 'swe' AND "
        "session_time BETWEEN datetime('now', '-6 days') "
        "AND datetime('now', 'localtime')")){
            qDebug() << "Couldn't open DB for reading swe stats last week data!";
            return;
    }

    if(last_week_stats_query_eng.next() && last_week_stats_query_swe.next()){
        QMessageBox::information(this, "Total result",
        "English: " + last_week_stats_query_eng.value(0).toString() + " %,"
        "\nSwedish: " + last_week_stats_query_swe.value(0).toString() + " %");
    }
}


void UserStats::on_last_month_res_Button_clicked()
{
    // make query for the both modes
    QSqlQuery last_month_stats_query_eng(db.get_my_db());
    QSqlQuery last_month_stats_query_swe(db.get_my_db());

    if(!last_month_stats_query_eng.exec("SELECT round(avg(success), 2) FROM Stats "
        "WHERE mode = 'eng' AND "
        "session_time BETWEEN datetime('now', 'start of month') "
        "AND datetime('now', 'localtime')")){
            qDebug() << "Couldn't open DB for reading eng stats last month data!";
            return;
    }

    if(!last_month_stats_query_swe.exec("SELECT round(avg(success), 2) FROM Stats "
        "WHERE mode = 'swe' AND "
        "session_time BETWEEN datetime('now', 'start of months') "
        "AND datetime('now', 'localtime')")){
            qDebug() << "Couldn't open DB for reading swe stats last month data!";
            return;
    }

    if(last_month_stats_query_eng.next() && last_month_stats_query_swe.next()){
        QMessageBox::information(this, "Total result",
        "English: " + last_month_stats_query_eng.value(0).toString() + " %,"
        "\nSwedish: " + last_month_stats_query_swe.value(0).toString() + " %");
    }
}


// Method shows total success
void UserStats::on_overall_res_Button_clicked()
{
    // // Making query for each mode
    // QSqlQuery all_stats_query_eng(db.get_my_db());
    // QSqlQuery all_stats_query_swe(db.get_my_db());

    // if(!all_stats_query_eng.exec("SELECT round(avg(success), 2) FROM Stats "
    //                               "WHERE mode = 'eng'")){
    //     qDebug() << "Couldn't open DB for reading eng stats data!";
    //     return;
    // }

    // if(!all_stats_query_swe.exec("SELECT round(avg(success), 2) FROM Stats "
    //                               "WHERE mode = 'swe'")){
    //     qDebug() << "Couldn't open DB for reading swe stats data!";
    //     return;
    // }

    // if(all_stats_query_eng.next() && all_stats_query_swe.next()){
    //     QMessageBox::information(this, "Total result",
    //     "English: " + all_stats_query_eng.value(0).toString() + " %,"
    //     "\nSwedish: " + all_stats_query_swe.value(0).toString() + " %");
    // }

    // creating a chart
    stats_chart = std::make_unique<DrawStatsChart>(this);
    stats_chart->setGeometry(0, 0, 660, 500);
    stats_chart->drawOverallStats();
    stats_chart->show();
}
