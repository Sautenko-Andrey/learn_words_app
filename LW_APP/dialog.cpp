#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>
#include <QVector>
#include <QDebug>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    // let's make focus on the second lineEdit by default
    ui->lineEdit_2->setFocus();

    // let's add modes to the combobox (modes for users)
    for(const auto &mode : modes){
        ui->comboBox->addItem(mode);
    }

    // when user pushes "Close" button
    connect(ui->exit_button, SIGNAL(clicked(bool)), SLOT(close()));

}

Dialog::~Dialog()
{
    delete ui;
}

//RUS_ENG, ENG_RUS, RUS_SWE, SWE_RUS
void Dialog::on_confirm_mode_clicked()
{

    // CHANGE qDebug() to the real logic!!!
    switch (ui->comboBox->currentIndex()) {
    case All_Modes::RUS_ENG:
        qDebug() << "RUS_ENG";
        break;
    case All_Modes::ENG_RUS:
        qDebug() << "ENG_RUS";
        break;
    case All_Modes::RUS_SWE:
        qDebug() << "RUS_SWE";
        break;
    case All_Modes::SWE_RUS:
        qDebug() << "SWE_RUS";
        break;
    }

    // let's return focus on the second lineEdit after closing dialog window
    ui->lineEdit_2->setFocus();
}


void Dialog::on_stats_button_clicked()
{
    QMessageBox::information(this, "Results", "Succesful answers: 100%");
    // let's return focus on the second lineEdit after closing dialog window
    ui->lineEdit_2->setFocus();
}

