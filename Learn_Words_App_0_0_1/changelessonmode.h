#ifndef CHANGELESSONMODE_H
#define CHANGELESSONMODE_H

#include <QDialog>
#include "subject.h"   // new
#include "observer.h"
#include "common.h"
#include <QVector>


namespace Ui {
class ChangeLessonMode;
}

class ChangeLessonMode : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeLessonMode(QWidget *parent = nullptr);
    ~ChangeLessonMode();

private slots:
    void on_okButton_clicked();

private:
    Ui::ChangeLessonMode *ui;
};


//----------------------------------------------------------------------------
// a new approach

// class ChangeLessonMode : public QDialog, public Subject
// {
//     Q_OBJECT

// public:
//     explicit ChangeLessonMode(QWidget *parent = nullptr);

//     ~ChangeLessonMode();

//     virtual void registerObserver(Observer *observer) override;

//     virtual void removeObserver(Observer *observer) override;

//     virtual void notifyObservers() override;

//     void languageModeChanged();

//     All_Languges getMode() const;

// private slots:
//     void on_okButton_clicked();

// private:
//     Ui::ChangeLessonMode *ui;

//     QVector<Observer *> m_observers;

//     // All_Languges userLanguageMode = All_Languges::ENG;
//     All_Languges userLanguageMode;
// };


#endif // CHANGELESSONMODE_H
