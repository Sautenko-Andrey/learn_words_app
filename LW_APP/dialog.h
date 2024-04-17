#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QString>
#include <string>
#include <map>

enum All_Modes{RUS_ENG, ENG_RUS, RUS_SWE, SWE_RUS};

QT_BEGIN_NAMESPACE
namespace Ui {
class Dialog;
}
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();


private slots:
    void on_stats_button_clicked();
    void on_confirm_mode_clicked();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Dialog *ui;
    const QVector<QString> modes = {
        "rus - eng",
        "eng - rus",
        "rus - swe",
        "swe - rus"
    };

    std::map<std::string, std::string> data_base;  // probably unordered_map will be better

    void read_data_from_DB();
    void display_first_word();
    void answer_is_right(const QString &task, const QString &answer) noexcept;
    unsigned counter = 0;
    unsigned right_answers = 0;
    unsigned answers_counter = 0;

};

#endif // DIALOG_H
