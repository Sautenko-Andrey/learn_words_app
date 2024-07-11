#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QDialog>
#include "common.h"
#include <QString>
#include <QListWidgetItem>

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

    void on_unmarkButton_clicked();

    void on_unmarkAllButton_clicked();

    void on_reloadButton_clicked();

private:
    Ui::ListWidget *ui;

    void prepareListData(const QSqlDatabase *db);

    QList<QListWidgetItem *> selected_rows;

    QSqlDatabase *database{nullptr};

    All_Languges *current_lang_mode{nullptr};

};

#endif // LISTWIDGET_H
