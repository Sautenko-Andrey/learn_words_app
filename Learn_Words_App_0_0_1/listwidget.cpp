#include "listwidget.h"
#include "ui_listwidget.h"
#include <QString>
#include <QSqlQuery>

ListWidget::ListWidget(QSqlDatabase &db, QWidget *parent, All_Languges lang_mode)
    : QDialog(parent)
    , ui(new Ui::ListWidget)
{
    ui->setupUi(this);

    // pointer on database
    database = &db;

    // pointer on language mode
    current_lang_mode = &lang_mode;

    // buttons settings
    // reload database button
    makeButtonIcon(":all_pics/restart.png", "Reload database", ui->reloadButton);

    // display all words from the database in widget
    prepareListData(database);
}

void ListWidget::prepareListData(const QSqlDatabase *db)
{
    if(db){
        // Open a data base and read all data
        QSqlQuery query(*db);

        if(*current_lang_mode == All_Languges::ENG){
            query.exec("SELECT eng_word, rus_word FROM ENG_RUS_WORDS"
                       " ORDER BY rus_word ASC");
        }
        else{
            query.exec("SELECT swe_word, rus_word FROM SWE_RUS_WORDS"
                       " ORDER BY rus_word ASC");
        }

        // fill the list widget
        while(query.next()){
            ui->listWidget->addItem(
                query.value(1).toString() + "  ->  " +
                query.value(0).toString()
                );
        }
    }
}


ListWidget::~ListWidget()
{
    delete ui;
}

void ListWidget::on_markButton_clicked()
{
    // Mark current line
    QListWidgetItem *item = ui->listWidget->currentItem();
    item->setForeground(Qt::yellow);
    item->setBackground(Qt::black);

    // add selected row to the collection for unmarking purpose in future
    selected_rows.append(item);
}

void ListWidget::on_unmarkButton_clicked()
{
    // Unmark current line
    QListWidgetItem *item = ui->listWidget->currentItem();
    item->setForeground(Qt::black);
    item->setBackground(QBrush(QColor("SlateGray")));
}


void ListWidget::on_unmarkAllButton_clicked()
{
    // umark all marked lines
    for(auto const &item : selected_rows){
        item->setForeground(Qt::black);
        item->setBackground(QBrush(QColor("SlateGray")));
    }
}

void ListWidget::on_reloadButton_clicked()
{
    // reload database
    // clean widget's pitch
    ui->listWidget->clear();

    prepareListData(database);
}
