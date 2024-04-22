#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <all_sizes.h>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // when user pushes "finish lesson" we close the program
    // and show him his result
    connect(ui->actionFinish_lesson, SIGNAL(triggered(bool)), this, SLOT(close()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


// Function reads data from the file to the data_base (unordered_map)
//void MainWindow::read_data_from_DB()
//{
    // let's read data from DB
    //std::ifstream input_stream("/home/andrey/eng_words_temp_db.txt");
    // std::ifstream input_stream("../eng_rus_words.txt");
    // if(!input_stream){
    //     qDebug() << "Couldn't open a file for reading data from DB";
    //     return;
    // }

    //std::string temp_str;

    // reading a data from the file (temporary. data will be in DB soon)
    // while(std::getline(input_stream, temp_str)){
    //     constexpr int size = 2;
    //     std::vector<std::string> words(size);
    //     // split text by ':' via boost
    //     boost::split(words, temp_str, boost::is_any_of(":"));
    //     CommonFiles::data_base[words[0]] = words[1];
    // }

    // Reading data from the DB
//}

// Function activates the user learning session dialog
void MainWindow::on_actionStart_lesson_triggered()
{
    user_session = std::make_unique<UserSession>(this);
    user_session->show();
}


void MainWindow::on_actionAdd_word_triggered()
{
    // here we call add word widget
    add_one_word_session = std::make_unique<AddOneWord>(this);
    add_one_word_session->resize(Sizes::ADD_WORD_DIALOG_WIDTH, Sizes::ADD_WORD_DIALOG_HEIGHT);
    add_one_word_session->show();
}


void MainWindow::on_actionStats_triggered()
{
    // here we call a Message box with user's result
    // in percentes
    QMessageBox::information(this, "Result", "Successful answers: 100 %");
}


void MainWindow::on_actionSet_word_triggered()
{
    set_one_word_session = std::make_unique<SetWord>(this);
    set_one_word_session->show();
}


void MainWindow::on_actionDelete_word_triggered()
{
    // call the delete word dialog
    del_one_word_session = std::make_unique<DeleteOneWord>(this);
    del_one_word_session->show();
}

