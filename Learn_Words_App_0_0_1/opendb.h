#ifndef OPENDB_H
#define OPENDB_H

#include <QString>
#include <QDir>
#include <QSqlDatabase>

// Class for opening/closing sqlite3 data base
class OpenDB
{
    QSqlDatabase my_db = QSqlDatabase::addDatabase("QSQLITE","Connection");
    QString path_to_db = QDir::homePath() + "/learn_words_app/Learn_Words_App_0_0_1/data.db";
public:
    OpenDB();
    ~OpenDB() { my_db.close(); }

    QSqlDatabase& get_my_db() { return my_db; }
};

#endif // OPENDB_H
