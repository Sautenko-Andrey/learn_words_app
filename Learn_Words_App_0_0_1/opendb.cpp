#include "opendb.h"
#include <QtSql>
#include <QDebug>

OpenDB::OpenDB()
{
    // Specify the path to the db
    my_db.setDatabaseName(path_to_db);

    // Checking is data base opened
    if(!my_db.open()){
        qDebug() << "Error!";
        qDebug() << my_db.lastError().text();
        exit(1);
    }
}
