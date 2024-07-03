#include "listwidget.h"
#include "ui_listwidget.h"
#include <QString>
#include <QSqlQuery>

ListWidget::ListWidget(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ListWidget)
{
    ui->setupUi(this);

    // Open a data base and read all data
    QSqlQuery get_all_words_query(db.get_my_db());
    // ATTENTION! Using global variable for getting knowladge about
    // what language mode user has choosen
    All_Languges USER_LANGUAGE_MODE = All_Languges::ENG;  // FIX IT!

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





//----------------------------------------------------------------------
// a new approach

// ListWidget::ListWidget(ChangeLessonMode *changeLessonMode, QWidget *parent)
//     : QDialog(parent)
//     , ui(new Ui::ListWidget)
// {
//     ui->setupUi(this);

//     // registering as observer
//     if(changeLessonMode != nullptr){
//         m_changeLessonMode = changeLessonMode;
//         m_changeLessonMode->registerObserver(this);
//     }

//     // Open a data base and read all data
//     QSqlQuery get_all_words_query(db.get_my_db());

//     if(m_languageMode == All_Languges::ENG){
//         get_all_words_query.exec("SELECT eng_word, rus_word FROM ENG_RUS_WORDS"
//                                  " ORDER BY rus_word ASC");
//     }
//     else{
//         get_all_words_query.exec("SELECT swe_word, rus_word FROM SWE_RUS_WORDS"
//                                  " ORDER BY rus_word ASC");
//     }

//     // fill the list widget
//     while(get_all_words_query.next()){
//         ui->listWidget->addItem(
//             get_all_words_query.value(1).toString() + "  ->  " +
//             get_all_words_query.value(0).toString()
//             );
//     }
// }


// ListWidget::~ListWidget()
// {
//     delete ui;
// }

// void ListWidget::update(){
//     m_languageMode = m_changeLessonMode->getMode();
// }

// void ListWidget::on_markButton_clicked()
// {
//     QListWidgetItem *item = ui->listWidget->currentItem();
//     item->setForeground(Qt::yellow);
//     item->setBackground(Qt::black);
// }

