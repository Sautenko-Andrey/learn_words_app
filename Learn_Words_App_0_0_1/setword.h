#ifndef SETWORD_H
#define SETWORD_H

#include <QDialog>
#include "opendb.h"

namespace Ui {
class SetWord;
}

class SetWord : public QDialog
{
    Q_OBJECT

public:
    explicit SetWord(QWidget *parent = nullptr);
    ~SetWord();

private slots:
    void on_pushButton_clicked();

private:
    Ui::SetWord *ui;
    OpenDB db;
};

#endif // SETWORD_H
