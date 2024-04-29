#ifndef CHANGELESSONMODE_H
#define CHANGELESSONMODE_H

#include <QDialog>


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

#endif // CHANGELESSONMODE_H
