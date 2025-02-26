#ifndef COMMON_H
#define COMMON_H

#include <QString>
#include <QDir>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QPixmap>
#include <QLabel>
#include <QAbstractButton>
#include <QTextEdit>
#include <QListWidgetItem>
#include "sizes.h"
#include <QTimer>


//Common data

// Modes for user session, adding/delete/setting words
enum class All_Modes {RUS__ENG_RUS, ENG__ENG_RUS, SWE__SWE_RUS, RUS__SWE_RUS};

// Available foreign languages (assumed that user is rus/ukr speaker)
enum class All_Languges {ENG, SWE};

// Stats modes
enum class statsMode{TODAY, LAST_WEEK, LAST_MONTH, OVERALL};

extern const QVector<QString> MODES;

extern const QVector<QString> LANGUAGES_DB;

extern const QString BACKGROUND_COLOR;

static const QString app_path_name = "/learn_words_app/Learn_Words_App_0_0_1/";

// Common classes

// Class for opening/closing sqlite3 data base
class OpenDB
{
    QSqlDatabase my_db = QSqlDatabase::addDatabase("QSQLITE","Connection");
    const QString path_to_db = QDir::homePath() + app_path_name + "data.db";
public:
    OpenDB();
    ~OpenDB() { my_db.close(); }

    QSqlDatabase& get_my_db() { return my_db; }
};


template<typename T>
void showTempMessage(T &&title, T &&message, unsigned milisecs){

    auto mbox = std::make_unique<QMessageBox>();
    mbox->resize(static_cast<int>(Sizes::TEMP_MESSAGE_BOX_WIDTH),
                 static_cast<int>(Sizes::TEMP_MESSAGE_BOX_HEIGHT));

    mbox->setWindowTitle(std::forward<T>(title));
    mbox->setText(std::forward<T>(message));
    mbox->setStyleSheet(BACKGROUND_COLOR);
    mbox->show();

    QTimer::singleShot(milisecs, mbox.get(), SLOT(hide()));

    // Release a memory
    QTimer::singleShot(milisecs + 10, [mbox = std::move(mbox)]() mutable {
        mbox.reset();
    });
}



// Function shows an icon you choose
template<typename T>
QString pathToIcon(T &&file_name){
    // Path to the icon ( assuming that file is in all_pics resources )
    QString path = QDir::homePath() +
                app_path_name +
                std::forward<T>(file_name);
    return path;
}


template<typename T>
void drawLangLabel(QLabel *label, T &&path){
    if(label){
        QString full_path = QDir::homePath() +
                            app_path_name +
                            std::forward<T>(path);

        QPixmap curr_lang_pixmap(std::move(full_path));
        label->setPixmap(curr_lang_pixmap);
        label->setMask(curr_lang_pixmap.mask());
    }
}


template<typename T>
void makeButtonIcon(T &&img_path,
                    T &&tool_tip,
                    QAbstractButton *button)
{
    if(button){
        QIcon icon;
        icon.addPixmap(QPixmap(std::forward<T>(img_path)), QIcon::Active, QIcon::On);
        button->setIcon(icon);
        button->setToolTip(std::forward<T>(tool_tip));
    }
}

void setTextEditCursor(int &font_size, QTextEdit *leftTextEdit,
               QTextEdit *rightTextEdit, QDialog *dialog,
               bool increase = true);

void setTextEditCursor(int &font_size, QTextEdit *textEdit,
                       QDialog *dialog, bool increase = true);

#endif // COMMON_H
