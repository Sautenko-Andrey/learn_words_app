#ifndef USERSESSION_H
#define USERSESSION_H

#include <QDialog>
#include "common.h"
#include <memory>
#include <QComboBox>

namespace Ui {
class UserSession;
}

class UserSession : public QDialog
{
    Q_OBJECT

public:
    explicit UserSession(QWidget *parent = nullptr);
    ~UserSession();

private slots:


    void on_nextButton_clicked();

    void on_restartButton_clicked();

    void on_statsButton_clicked();

private:
    Ui::UserSession *ui;

    OpenDB db;

    QHash<QString, QString> all_words;

    unsigned counter = 0;

    unsigned right_answers = 0;

    unsigned answers_counter = 0;

    double progress_steps = 1.0;

    void answer_is_right(const QString &task, const QString &answer) noexcept;

    void display_first_word();

    void get_stats() noexcept;



};

#endif // USERSESSION_H
