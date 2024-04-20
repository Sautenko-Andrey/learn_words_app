#ifndef ADDWORDS_H
#define ADDWORDS_H

#include <QDialog>

namespace Ui {
class AddWords;
}

class AddWords : public QDialog
{
    Q_OBJECT

public:
    explicit AddWords(QWidget *parent = nullptr);
    ~AddWords();

private:
    Ui::AddWords *ui;
};

#endif // ADDWORDS_H
