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
    explicit ListWidget(QWidget *parent = nullptr);
    ~ListWidget();

private slots:
    void on_markButton_clicked();

private:
    Ui::ListWidget *ui;
    OpenDB db;
};

#endif // LISTWIDGET_H
