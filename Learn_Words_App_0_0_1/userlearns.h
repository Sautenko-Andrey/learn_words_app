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
    // explicit UserLearns(QWidget *parent = nullptr);
    explicit UserLearns(QSqlDatabase &database, QWidget *parent = nullptr);
    ~UserLearns();

private slots:
    void on_statsButton_clicked();

    void on_restartButton_clicked();

    void on_finishButton_clicked();

    void on_showtasksButton_clicked();

    void on_nextButton_clicked();

    void modeChanged();

    void on_reloadDataButton_clicked();

    void on_helpButton_clicked();

    void on_clearButton_clicked();

    void on_fontUpButton_clicked();

    void on_fontDownButton_clicked();

    void wordsRangeComboChanged();


private:
    Ui::UserLearns *ui;

    QSqlDatabase *db{nullptr};

    QHash<QString, QString> all_words;

    unsigned counter{0};

    unsigned right_answers{0};

    unsigned answers_counter{0};

    double progress_steps{1.0};

    int font_size{14};

    unsigned restriction_value{0};

    void answerIsRight(const QString &task,
                       const QString &answer);

    void displayFirstWord();

    double getStats() noexcept;

    void saveStats();

    void drawLabel(QString &&path, QLabel *label);

    void waitingMovie();

    void prepareData(const QString &request_msg,
                     const QString &path_to_flag,
                     QSqlQuery &query);

    void prepareCustomRange(const int restrictionValue);

    constexpr unsigned computeUserProgress(double progress_steps,
                                         int restriction_value);

};

#endif // USERLEARNS_H
