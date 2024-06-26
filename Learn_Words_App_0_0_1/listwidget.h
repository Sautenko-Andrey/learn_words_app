#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QDialog>
#include "common.h"
#include <QString>
#include "observer.h"   // new
#include "changelessonmode.h"  // new

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



//----------------------------------------------------------------------------
// a new approach

// class ListWidget : public QDialog, public Observer
// {
//     Q_OBJECT

// public:
//     explicit ListWidget(ChangeLessonMode *changeLessonMode, QWidget *parent = nullptr);

//     ~ListWidget();

//     virtual void update() override;

// private slots:
//     void on_markButton_clicked();

// private:
//     Ui::ListWidget *ui;

//     OpenDB db;

//     // All_Languges m_languageMode = All_Languges::ENG;
//     All_Languges m_languageMode;

//     ChangeLessonMode *m_changeLessonMode{nullptr};
// };

#endif // LISTWIDGET_H
