#include "usersession.h"
#include "ui_usersession.h"

UserSession::UserSession(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UserSession)
{
    ui->setupUi(this);
}

UserSession::~UserSession()
{
    delete ui;
}

void UserSession::on_nextButton_clicked()
{

}


void UserSession::on_pushButton_2_clicked()
{

}


void UserSession::on_pushButton_3_clicked()
{

}


void UserSession::on_pushButton_4_clicked()
{

}

