#ifndef USERLEARNS_H
#define USERLEARNS_H

#include <QDialog>
#include "common.h"
#include <memory>
#include <QComboBox>
#include <QSqlQuery>
#include "observer.h"   // new
#include "changelessonmode.h"  // new


namespace Ui {
class UserLearns;
}

class UserLearns : public QDialog
{
    Q_OBJECT

public:
    explicit UserLearns(QWidget *parent = nullptr);
    ~UserLearns();

private slots:
    void on_statsButton_clicked();

    void on_restartButton_clicked();

    void on_finishButton_clicked();

    void on_showtasksButton_clicked();

    void on_nextButton_clicked();

    void modeChanged();

private:
    Ui::UserLearns *ui;

    OpenDB db;

    QHash<QString, QString> all_words;

    unsigned counter = 0;

    unsigned right_answers = 0;

    unsigned answers_counter = 0;

    double progress_steps = 1.0;

    void answer_is_right(const QString &task, const QString &answer) noexcept;

    void display_first_word();

    double get_stats() noexcept;

    void save_stats();

    void DrawLabel(QString &&path, QLabel *label);

    void waitingMovie();
};



// // a new approach
// class UserLearns : public QDialog, public Observer
// {
//     Q_OBJECT

// public:
//     explicit UserLearns(ChangeLessonMode *changeLessonMode, QWidget *parent = nullptr);

//     ~UserLearns();

//     virtual void update() override;

// private slots:
//     void on_statsButton_clicked();

//     void on_restartButton_clicked();

//     void on_finishButton_clicked();

//     void on_showtasksButton_clicked();

//     void on_nextButton_clicked();

// private:
//     Ui::UserLearns *ui;

//     OpenDB db;

//     QHash<QString, QString> all_words;

//     unsigned counter = 0;

//     unsigned right_answers = 0;

//     unsigned answers_counter = 0;

//     double progress_steps = 1.0;

//     void answer_is_right(const QString &task, const QString &answer) noexcept;

//     void display_first_word();

//     double get_stats() noexcept;

//     void save_stats();

//     void DrawLabel(QString &&path, QLabel *label);

//     void waitingMovie();

//     All_Languges m_languageMode = All_Languges::ENG;
//     //All_Languges m_languageMode;

//     ChangeLessonMode *m_changeLessonMode{nullptr};
// };

#endif // USERLEARNS_H
