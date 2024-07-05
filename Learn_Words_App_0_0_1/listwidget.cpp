#include "listwidget.h"
#include "ui_listwidget.h"
#include <QString>
#include <QSqlQuery>

ListWidget::ListWidget(QSqlDatabase &db, QWidget *parent, All_Languges lang_mode)
    : QDialog(parent)
    , ui(new Ui::ListWidget)
{
    ui->setupUi(this);

    // Open a data base and read all data
    QSqlQuery get_all_words_query(db);

    if(lang_mode == All_Languges::ENG){
        get_all_words_query.exec("SELECT eng_word, rus_word FROM ENG_RUS_WORDS"
                                 " ORDER BY rus_word ASC");
    }
    else{
        get_all_words_query.exec("SELECT swe_word, rus_word FROM SWE_RUS_WORDS"
                                 " ORDER BY rus_word ASC");
    }

    // fill the list widget
    while(get_all_words_query.next()){
        ui->listWidget->addItem(
            get_all_words_query.value(1).toString() + "  ->  " +
            get_all_words_query.value(0).toString()
        );
    }
}


ListWidget::~ListWidget()
{
    delete ui;
}

void ListWidget::on_markButton_clicked()
{
    QListWidgetItem *item = ui->listWidget->currentItem();
    item->setForeground(Qt::yellow);
    item->setBackground(Qt::black);
}
