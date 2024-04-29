#ifndef COMMON_H
#define COMMON_H

#include <QString>
#include <QDir>
#include <QSqlDatabase>
#include <QVector>
#include <QMessageBox>
#include <QPixmap>
#include <QLabel>



//Common data

// Modes for user session, adding/delete/setting words
enum All_Modes{RUS__ENG_RUS, ENG__ENG_RUS, SWE__SWE_RUS, RUS__SWE_RUS};

// Available foreign languages (assumed that user is rus/ukr speaker)
enum All_Languges{ENG, SWE};

const QVector<QString> MODES = {
    "rus (eng-rus mode)",
    "eng (eng-rus mode)",
    "swe (swe-rus mode)",
    "rus (swe-rus mode)"
};

const QVector<QString> LANGUAGES_DB = {
    "eng-rus",
    "swe-rus"
};

const QString BACKGROUND_COLOR = "background-color:lightGray;";

// Common classes

// Class for opening/closing sqlite3 data base
class OpenDB
{
    QSqlDatabase my_db = QSqlDatabase::addDatabase("QSQLITE","Connection");
    const QString path_to_db = QDir::homePath() + "/learn_words_app/Learn_Words_App_0_0_1/data.db";
public:
    OpenDB();
    ~OpenDB() { my_db.close(); }

    QSqlDatabase& get_my_db() { return my_db; }
};

// Function displays custom QMessagebox when it needs
void ShowTempMessage(const QString &title, const QString &message, unsigned milisecs);

// Function shows an icon you choose
QString& PathToIcon(QString &&file_name) noexcept;


void DrawLangLabel(QLabel *label, const QString &path);



#endif // COMMON_H
