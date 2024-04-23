#ifndef USERSESSION_H
#define USERSESSION_H

#include <QDialog>
#include "opendb.h"

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

private:
    Ui::UserSession *ui;

    OpenDB db;

    double progress_steps = 1.0;

    // offset -> for the db queryes when using SELECT with OFFSET
    // for skiping rows in the table
    unsigned offset = 1;

};

#endif // USERSESSION_H
