#include "setword.h"
#include "ui_setword.h"

SetWord::SetWord(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SetWord)
{
    ui->setupUi(this);
}

SetWord::~SetWord()
{
    delete ui;
}

void SetWord::on_pushButton_clicked()
{

}

