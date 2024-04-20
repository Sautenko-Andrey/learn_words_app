#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <map>

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

    void on_statsButton_clicked();

    void on_nextButton_clicked();

    void on_restartButton_clicked();

private:
    Ui::MainWindow *ui;

    std::map<std::string, std::string> data_base;  // probably unordered_map will be better

    void read_data_from_DB();

    void display_first_word();

    void answer_is_right(const QString &task, const QString &answer) noexcept;

    unsigned counter = 0;

    unsigned right_answers = 0;

    unsigned answers_counter = 0;

    double steps = 1.0;
};
#endif // MAINWINDOW_H
