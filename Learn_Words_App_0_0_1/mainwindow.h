#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "usersession.h"
#include "addword.h"
#include "deleteword.h"
#include "setword.h"
#include "changelessonmode.h"
#include "userstats.h"
#include "userlearns.h"
#include <memory>
#include "sizes.h"
#include "common.h"
#include "ui_drawstatschart.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionStart_lesson_triggered();

    void on_actionAdd_word_triggered();

    void on_actionStats_triggered();

    void on_actionSet_word_triggered();

    void on_actionDelete_word_triggered();

    void on_actionFinish_lesson_triggered();

    void on_actionAdd_words_from_file_triggered();

private:
    Ui::MainWindow *ui;

    std::unique_ptr<AddWord> add_word_session{nullptr};

    std::unique_ptr<SetWord> set_one_word_session{nullptr};

    std::unique_ptr<DeleteWord> delete_word_session{nullptr};

    std::unique_ptr<UserStats> user_stats_session{nullptr};

    std::unique_ptr<UserLearns> user_learns_session{nullptr};

    OpenDB db;

};
#endif // MAINWINDOW_H
