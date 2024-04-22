#ifndef USERSESSION_H
#define USERSESSION_H

#include <QDialog>

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

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::UserSession *ui;
};

#endif // USERSESSION_H
