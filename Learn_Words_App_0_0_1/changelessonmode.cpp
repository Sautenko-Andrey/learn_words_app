#include "changelessonmode.h"
#include "ui_changelessonmode.h"
#include "common.h"
#include <QIcon>

// ATTENTION! POTENTIAL DANGEROUS GLOBAL VARIABLE!
extern All_Languges USER_LANGUAGE_MODE = All_Languges::ENG;

ChangeLessonMode::ChangeLessonMode(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChangeLessonMode)
{
    ui->setupUi(this);

    // Make theeng mode by default
    ui->eng_radioButton->setChecked(true);

    // Add icons to the both radio buttons
    auto eng_icon = QIcon(PathToIcon("eng_flag_2.png"));
    ui->eng_radioButton->setIcon(eng_icon);
    auto swe_icon = QIcon(PathToIcon("swe_flag_2.png"));
    ui->swe_radioButton->setIcon(swe_icon);
}

ChangeLessonMode::~ChangeLessonMode()
{
    delete ui;
}

void ChangeLessonMode::on_okButton_clicked()
{
    if(ui->eng_radioButton->isChecked()){
        USER_LANGUAGE_MODE = All_Languges::ENG;
    }
    else{
        USER_LANGUAGE_MODE = All_Languges::SWE;
    }

    // close it when user selected mode
    QDialog::accept();
}

