#ifndef USERLEARNS_H
#define USERLEARNS_H

#include <QDialog>
#include "common.h"
#include <memory>
#include <QComboBox>
#include <QSqlQuery>

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
};

#endif // USERLEARNS_H
