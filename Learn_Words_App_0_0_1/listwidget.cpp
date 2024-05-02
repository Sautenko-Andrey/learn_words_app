#include "listwidget.h"
#include "ui_listwidget.h"
#include <QString>
#include <QSqlQuery>

ListWidget::ListWidget(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ListWidget)
{
    ui->setupUi(this);

    // Opena data base and read all data
    QSqlQuery get_all_words_query(db.get_my_db());
    // ATTENTION! Using global variable for getting knowladge about
    // what language mode user has choosen
    extern All_Languges USER_LANGUAGE_MODE;

    if(USER_LANGUAGE_MODE == All_Languges::ENG){
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

