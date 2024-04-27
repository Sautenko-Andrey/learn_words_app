#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "usersession.h"
//#include "addoneword.h"
#include "addword.h"
//#include "deleteoneword.h"
#include "deleteword.h"
#include "setword.h"
#include <memory>


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

private:
    Ui::MainWindow *ui;

    std::unique_ptr<UserSession> user_session;

    std::unique_ptr<AddWord> add_word_session;

    std::unique_ptr<SetWord> set_one_word_session;

    std::unique_ptr<DeleteWord> delete_word_session;


};
#endif // MAINWINDOW_H
