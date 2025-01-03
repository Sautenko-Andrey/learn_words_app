#include "userlearns.h"
#include "ui_userlearns.h"
#include <QMessageBox>
#include <QtSql>
#include <QTimer>
#include <QHash>
#include <QPixmap>
#include "listwidget.h"
#include <QMovie>
#include <algorithm>



enum class Restrinctions {
    None = 0, Fifty = 50, Hundred = 100, TwoHundred = 200, FiveHundred = 500
};

UserLearns::UserLearns(QSqlDatabase &database, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UserLearns)
{
    ui->setupUi(this);

    // pointer on the database
    db = &database;

    // add words numbers modes
    ui->wordsNumberComboBox->addItems(
        {"All" ,"50", "100", "200", "500"}
    );

    ui->engModeRadioButton->setChecked(true);

    QSqlQuery get_all_words_query(*db);


    prepareData("SELECT lower(eng_word), rus_word FROM ENG_RUS_WORDS",
                "eng_flag.png", get_all_words_query);


    // Show to user what he has type in edit line
    ui->userTextEdit->setPlaceholderText(QString("type your answer"));

    // Make task line read only
    ui->taskTextEdit->setReadOnly(true);

    // Let's make focus on user's edit line
    ui->userTextEdit->setFocus();

    // Let's set progress bar value equal to null
    ui->progressBar->setValue(0);

    // Make buttons "Stats" closed before user inputs the first answer
    ui->statsButton->setDisabled(true);

    // Minimum width for the progress bar
    ui->progressBar->setMinimumWidth(500);

    // making icons for buttons
    // stats button
    makeButtonIcon(":all_pics/stats.png", "Getting current stats", ui->statsButton);

    // restart button
    makeButtonIcon(":all_pics/restart_lesson.png", "Restart current lesson",
                   ui->restartButton);

    // finish button
    makeButtonIcon(":all_pics/finish_lesson.png", "Finish current lesson",
                   ui->finishButton);

    // tasks button
    makeButtonIcon(":all_pics/task_list.png", "Getting all tasks and answers",
                   ui->showtasksButton);

    // next button
    makeButtonIcon(":all_pics/next.png", "Go to the next task", ui->nextButton);

    // reload database button
    makeButtonIcon(":all_pics/restart.png", "Reload database", ui->reloadDataButton);

    // help button
    makeButtonIcon(":all_pics/help.png", "Show the right answer", ui->helpButton);

    // clear button
    makeButtonIcon(":all_pics/clear_all.png", "Clear user's input text", ui->clearButton);

    // font up button
    makeButtonIcon(":all_pics/font_up.png", "Make text bigger", ui->fontUpButton);

    // font down button
    makeButtonIcon(":all_pics/font_down.png", "Make text smaller", ui->fontDownButton);

    // connections
    connect(ui->engModeRadioButton, SIGNAL(toggled(bool)), this, SLOT(modeChanged()));

    connect(ui->wordsNumberComboBox, SIGNAL(currentTextChanged(QString)),
            this, SLOT(wordsRangeComboChanged()));
}

UserLearns::~UserLearns()
{
    delete ui;
}


void UserLearns::prepareData(const QString &request_msg,
                             const QString &path_to_flag,
                             QSqlQuery &query){

    if(!query.exec(request_msg)){
        QMessageBox::warning(this, "Error!",
            "Couldn't load data when preparing.");
    }

    // Set language flag
    DrawLangLabel(ui->current_languageLabel, path_to_flag);

    // let's clear data
    all_words.clear();
    ui->taskTextEdit->clear();

    ui->progressBar->setValue(0);

    // drop all counters
    counter = 0;

    right_answers = 0;

    answers_counter = 0;

    progress_steps = 1.0;

    // fill with a new words
    while(query.next()){
        all_words.insert(query.value(0).toString(),
                         query.value(1).toString());
    }


    // let's show the very first word(rus) to user
    QString first_word = all_words.cbegin().value();
    ui->taskTextEdit->setText(first_word);
    ++counter;

    // draw a result label with loading animation
    waitingMovie();
}


void UserLearns::modeChanged(){

    QSqlQuery get_all_words_query(*db);

    if(ui->engModeRadioButton->isChecked()){
        prepareData("SELECT lower(eng_word), rus_word FROM ENG_RUS_WORDS",
                    "eng_flag.png", get_all_words_query);
    }
    else{
        prepareData("SELECT lower(swe_word), rus_word FROM SWE_RUS_WORDS",
                    "swe_flag.png", get_all_words_query);
    }
}


void UserLearns::on_reloadDataButton_clicked()
{
    // when user made changes in database and wants to continue lesson
    // with updating data without reloading app

    QSqlQuery support_query(*db);


    if(ui->engModeRadioButton->isChecked()){
        prepareData("SELECT lower(eng_word), rus_word FROM ENG_RUS_WORDS",
                    "eng_flag.png", support_query);
    }
    else{
        prepareData("SELECT lower(swe_word), rus_word FROM SWE_RUS_WORDS",
                    "swe_flag.png", support_query);
    }
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
    if(label){
        QPixmap pixmap(PathToIcon(std::move(path)));
        label->setPixmap(pixmap);
        label->setMask(pixmap.mask());
    }
}


// Function checks if the user answer is right
void UserLearns::answerIsRight(const QString &task, const QString &answer) noexcept
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
void UserLearns::displayFirstWord()
{
    auto iter = all_words.cbegin();
    std::advance(iter, counter);

    // displays word for the user
    ui->taskTextEdit->setText(iter.value());

    ++counter;
}


double UserLearns::getStats() noexcept
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
    getStats();

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
    displayFirstWord();
}


void UserLearns::on_finishButton_clicked()
{
    // save stats and exit
    saveStats();

    QDialog::accept();
}


void UserLearns::on_showtasksButton_clicked()
{
    // show all tasks and right answers
    // create and show up a list widget
    ListWidget *list_widget{nullptr};
    if(ui->engModeRadioButton->isChecked()){
        list_widget = new ListWidget(*db, this, All_Languges::ENG);
    }
    else{
        list_widget = new ListWidget(*db, this, All_Languges::SWE);
    }
    list_widget->show();
}


void UserLearns::on_nextButton_clicked()
{
    // We display user's progress through progress bar
    unsigned user_progress{0};

    // make range mode button unaccessable
    ui->wordsNumberComboBox->setDisabled(true);

    if (restrictionValue == static_cast<int>(Restrinctions::None)){
        user_progress = (progress_steps / all_words.size()) * 100;
    }
    else if (restrictionValue == static_cast<int>(Restrinctions::Fifty)){
        user_progress = (progress_steps / restrictionValue) * 100;
    }
    else if (restrictionValue == static_cast<int>(Restrinctions::Hundred)){
        user_progress = (progress_steps / restrictionValue) * 100;
    }
    else if (restrictionValue == static_cast<int>(Restrinctions::TwoHundred)){
        user_progress = (progress_steps / restrictionValue) * 100;
    }
    else{
        user_progress = (progress_steps / static_cast<int>(Restrinctions::FiveHundred)) * 100;
    }
    // unsigned user_progress = (progress_steps / all_words.size()) * 100;

    ui->progressBar->setValue(user_progress);
    progress_steps += 1.0;

    // Make "Stats" button available
    ui->statsButton->setDisabled(false);

    // first of all let's check if counter less then words we have in the data base
    if(restrictionValue == static_cast<int>(Restrinctions::None) &&
        counter == all_words.size()){
        prepareCustomRange(all_words.size() - 1);
    }
    else if(restrictionValue == static_cast<int>(Restrinctions::Fifty)
            && counter == restrictionValue){
        prepareCustomRange(restrictionValue);
    }
    else if(restrictionValue == static_cast<int>(Restrinctions::Hundred)
            && counter == restrictionValue){
        prepareCustomRange(restrictionValue);
    }
    else if(restrictionValue == static_cast<int>(Restrinctions::TwoHundred)
            && counter == restrictionValue){
        prepareCustomRange(restrictionValue);
    }
    else if(restrictionValue == static_cast<int>(Restrinctions::FiveHundred)
            && counter == restrictionValue){
        prepareCustomRange(restrictionValue);
    }

    // let's read user's answer from the line
    // and get rid of unwanted leading and trailing spaces
    QString user_answer = (ui->userTextEdit->toPlainText()).trimmed();

    // let's clear line
    ui->userTextEdit->clear();

    // focus on userTextEdit
    ui->userTextEdit->setFocus();

    // show a word for the user
    displayFirstWord();

    // let's check user answer
    auto task = all_words.cbegin();
    std::advance(task, answers_counter);
    answerIsRight(task.key(), std::move(user_answer));
}


void UserLearns::prepareCustomRange(const int restrictionValue)
{
    // save the last user's answer
    QString last_user_answer = (ui->userTextEdit->toPlainText()).trimmed();

    // we have to check the very last user answer as well
    auto last_it = all_words.cbegin();
    std::advance(last_it, restrictionValue);

    //answer_is_right(last_task, last_user_answer);
    answerIsRight(last_it.key(), last_user_answer);

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
    saveStats();

    // draw a result label with loading animation
    waitingMovie();

    QDialog::accept();
}


void UserLearns::saveStats()
{
    // Get the final stats in the end
    auto user_stats = getStats();

    // make a query
    QSqlQuery save_result_query(*db);

    if(ui->engModeRadioButton->isChecked()){
        save_result_query.prepare("INSERT INTO Stats(mode, success) "
                                  "VALUES('eng', :user_success)");
    }
    else{
        save_result_query.prepare("INSERT INTO Stats(mode, success) "
                                  "VALUES('swe', :user_success)");
    }

    save_result_query.bindValue(":user_success", user_stats);

    if(!save_result_query.exec()){
        QMessageBox::warning(this,
                             "Warning",
                             "Error while adding a new stats to the data base!");
        return;
    }
}

void UserLearns::on_helpButton_clicked()
{
    // show the right answer

    auto it = all_words.cbegin();

    std::advance(it, answers_counter);

    QMessageBox::information(this, "Hint", "<b>" + it.key() + "</b>");

}


void UserLearns::on_clearButton_clicked()
{
    // clear user's answer
    ui->userTextEdit->clear();
}


void UserLearns::on_fontUpButton_clicked()
{
    // increase font
    setTextEditCursor(font_size, ui->taskTextEdit, ui->userTextEdit, this);
}


void UserLearns::on_fontDownButton_clicked()
{
    //decrease font
    setTextEditCursor(font_size, ui->taskTextEdit, ui->userTextEdit, this, false);
}

void UserLearns::wordsRangeComboChanged()
{
    QString currentRange = ui->wordsNumberComboBox->currentText();

    if(currentRange == "All"){
        restrictionValue = 0;
    }
    else if(currentRange == "50"){
        restrictionValue = 50;
    }
    else if(currentRange == "100"){
        restrictionValue = 100;
    }
    else if(currentRange == "200"){
        restrictionValue = 200;
    }
    else{
        restrictionValue = 500;
    }
}
