#ifndef COMMON_H
#define COMMON_H

#include <QString>
#include <QDir>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QPixmap>
#include <QLabel>
#include <QAbstractButton>


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

void makeButtonIcon(const QString &img_path, const QString &tool_tip,
                    QAbstractButton *button);


#endif // COMMON_H
