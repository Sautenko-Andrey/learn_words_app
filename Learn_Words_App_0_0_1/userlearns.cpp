#include "userlearns.h"
#include "ui_userlearns.h"
#include <QMessageBox>
#include <QDebug>
#include <QtSql>
#include <QTimer>
#include <QHash>
#include <QPixmap>
#include "listwidget.h"
#include <QMovie>

UserLearns::UserLearns(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UserLearns)
{
    ui->setupUi(this);

    // Read all data from the DB and save in the container
    // Assuming ENG_RUS data base as default
    //---------------------------------------------------------------------------OLD
    QSqlQuery get_all_words_query(db.get_my_db());

    // ATTENTION! Using global variable for getting knowladge about
    // what language mode user has choosen
    extern All_Languges USER_LANGUAGE_MODE;
    if(USER_LANGUAGE_MODE == All_Languges::ENG){
        get_all_words_query.exec("SELECT eng_word, rus_word FROM ENG_RUS_WORDS");
        // Set language flag
        DrawLangLabel(ui->current_languageLabel, "eng_flag.png");
    }
    else{
        get_all_words_query.exec("SELECT swe_word, rus_word FROM SWE_RUS_WORDS");
        DrawLangLabel(ui->current_languageLabel, "swe_flag.png");
    }

    // fill the container
    while(get_all_words_query.next()){
        all_words.insert(get_all_words_query.value(0).toString(),
                         get_all_words_query.value(1).toString());
    }

    // let's show the very first word(rus) to user
    QString first_word = all_words.cbegin().value();
    ui->taskTextEdit->setText(first_word);
    ++counter;

    // Show to user what he has type in edit line
    ui->userTextEdit->setPlaceholderText(QString("type your answer"));

    // Let's make focus on user's edit line
    ui->userTextEdit->setFocus();

    // Let's set progress bar value equal to null
    ui->progressBar->setValue(0);

    // Make buttons "Stats" closed before user inputs the first answer
    ui->statsButton->setDisabled(true);

    // draw a result label with loading animation
    waitingMovie();
}

UserLearns::~UserLearns()
{
    delete ui;
}

void UserLearns::waitingMovie()
{
    // draw a result label with loading animation
    QMovie *movie = new QMovie(":/all_pics/loading_animation.gif");
    movie->setScaledSize(QSize(25, 25));
    ui->resultLabel->setMovie(movie);
    movie->start();
}


void UserLearns::DrawLabel(QString &&path, QLabel *label)
{
    QPixmap pixmap(PathToIcon(std::move(path)));
    label->setPixmap(pixmap);
    label->setMask(pixmap.mask());
}


// Function checks if the user answer is right
void UserLearns::answer_is_right(const QString &task, const QString &answer) noexcept
{
    ++answers_counter;
    if(task == answer)
    {
        ++right_answers;
        DrawLabel("done.png", ui->resultLabel);
    }
    else{
        DrawLabel("fail.png", ui->resultLabel);

        // show to user information window with the correct answer
        ShowTempMessage("Fail!",
                        "Correct answer: <b><u>" + task + "</u></b>"
                                                          ", yours was: <b><i>" + answer + "</i></b>", 5000);
    }

    // let's hide the result label after 2 seconds
    ui->resultLabel->setVisible(true);
}

// Function displays on edit line word (rus) from the DB
void UserLearns::display_first_word()
{
    auto iter = all_words.cbegin();
    std::advance(iter, counter);

    // displays word for the user
    ui->taskTextEdit->setText(iter.value());

    ++counter;
}


double UserLearns::get_stats() noexcept
{
    double result = (static_cast<double>(right_answers) / answers_counter) * 100;

    // we show user results
    QMessageBox::information(this, "Results",
                             "Successful answers: "
                                 + QString::number(result, 'f', 2) + " %");

    return result;
}


void UserLearns::on_statsButton_clicked()
{
    get_stats();

    // return focus on user's edit line
    ui->userTextEdit->setFocus();
}


void UserLearns::on_restartButton_clicked()
{
    // Show warning message to the user
    // if he tryes to restart session in the middle
    if(progress_steps < all_words.size()){
        QMessageBox::warning(this, "Warning!", "Your progress will be losen");
    }

    // Let's unlock user edit line and next button
    ui->userTextEdit->setDisabled(false);
    ui->nextButton->setDisabled(false);

    // Make "Stats" button closed before the first click "Next"
    ui->statsButton->setDisabled(true);

    // let's make focus to user line edit
    ui->userTextEdit->setFocus();

    // let's make progress bar value as it was from the start
    ui->progressBar->setValue(0);

    // let's make progress steps as it was from the start
    progress_steps = 1.0;

    // counter must starts from the scratch
    counter = 0;

    // answers counter starts from the scratch as well
    answers_counter = 0;

    // right answers starts from the scratch as well
    right_answers = 0;

    // let's show the very first word(task) to the user
    display_first_word();
}


void UserLearns::on_finishButton_clicked()
{
    // save stats and exit
    save_stats();

    QDialog::accept();
}


void UserLearns::on_showtasksButton_clicked()
{
    // show all tasks and right answers
    // create and show up a list widget
    ListWidget *list_widget = new ListWidget(this);
    list_widget->show();
}


void UserLearns::on_nextButton_clicked()
{
    // We display user's progress through progress bar
    unsigned user_progress = (progress_steps / all_words.size()) * 100;
    ui->progressBar->setValue(user_progress);
    progress_steps += 1.0;

    // Make "Stats" button available
    ui->statsButton->setDisabled(false);

    // first of all let's check if counter less then words we have in the data base
    if(counter == all_words.size()){
        // save the last user's answer
        QString last_user_answer = (ui->userTextEdit->toPlainText()).trimmed();

        // we have to check the very last user answer as well
        auto last_it = all_words.cbegin();
        std::advance(last_it, all_words.size() - 1);

        //answer_is_right(last_task, last_user_answer);
        answer_is_right(last_it.key(), last_user_answer);

        // let's clear user's line
        ui->userTextEdit->clear();

        // let's block user's line while user pushes restart
        ui->userTextEdit->setDisabled(true);

        // let's make button "Next" unaccessable
        ui->nextButton->setDisabled(true);

        // make focus on the "Restart" button
        ui->restartButton->setFocus();

        // clear the task line
        ui->taskTextEdit->clear();

        // saving statistics
        save_stats();

        // draw a result label with loading animation
        waitingMovie();

        QDialog::accept();
    }

    // let's read user's answer from the line
    // and get rid of unwanted leading and trailing spaces
    QString user_answer = (ui->userTextEdit->toPlainText()).trimmed();

    // let's clear line
    ui->userTextEdit->clear();

    // focus on userTextEdit
    ui->userTextEdit->setFocus();

    // show a word for the user
    display_first_word();

    // let's check user answer
    auto task = all_words.cbegin();
    std::advance(task, answers_counter);

    answer_is_right(task.key(), user_answer);
}


void UserLearns::save_stats()
{
    // Get the final stats in the end
    auto user_stats = get_stats();

    // make query
    QSqlQuery save_result_query(db.get_my_db());

    // ATTENTION! Using global variable for getting knowladge about
    // what language mode user has choosen
    extern All_Languges USER_LANGUAGE_MODE;
    if(USER_LANGUAGE_MODE == All_Languges::ENG){
        save_result_query.prepare("INSERT INTO Stats(mode, success) "
                                  "VALUES('eng', :user_success)");
    }
    else{
        save_result_query.prepare("INSERT INTO Stats(mode, success) "
                                  "VALUES('swe', :user_success)");
    }

    save_result_query.bindValue(":user_success", user_stats);

    if(!save_result_query.exec()){
        qDebug() << "Error while adding a new stats to the data base!";
        return;
    }
}
