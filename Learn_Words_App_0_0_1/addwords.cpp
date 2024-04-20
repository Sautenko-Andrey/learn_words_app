#include "addwords.h"
#include "ui_addword.h"

AddWords::AddWords(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddWords)
{
    ui->setupUi(this);
}

AddWords::~AddWords()
{
    delete ui;
}
