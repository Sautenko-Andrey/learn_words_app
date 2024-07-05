#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QDialog>
#include "common.h"
#include <QString>

namespace Ui {
class ListWidget;
}

class ListWidget : public QDialog
{
    Q_OBJECT

public:

    explicit ListWidget(QSqlDatabase &db,
                        QWidget *parent = nullptr,
                        All_Languges lang_mode = All_Languges::ENG);
    ~ListWidget();

private slots:
    void on_markButton_clicked();

private:
    Ui::ListWidget *ui;
};

#endif // LISTWIDGET_H
