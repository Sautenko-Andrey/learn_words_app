#include "common.h"
#include <QtSql>
#include <QDebug>
#include "sizes.h"
#include <QStringList>

const QStringList MODES = {
    "rus (eng-rus mode)",
    "eng (eng-rus mode)",
    "swe (swe-rus mode)",
    "rus (swe-rus mode)"
};

const QStringList LANGUAGES_DB = {
    "eng-rus",
    "swe-rus"
};

const QString BACKGROUND_COLOR = "background-color:lightGray;";


// Constructor for the class OpenDB
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

void ShowTempMessage(const QString &title, const QString &message, unsigned milisecs)
{
    // show to user information window with the correct answer
    QMessageBox *mbox = new QMessageBox();
    mbox->resize(static_cast<int>(Sizes::TEMP_MESSAGE_BOX_WIDTH),
                 static_cast<int>(Sizes::TEMP_MESSAGE_BOX_HEIGHT));
    mbox->setWindowTitle(title);
    mbox->setText(message);
    mbox->setStyleSheet(BACKGROUND_COLOR);
    mbox->show();
    QTimer::singleShot(milisecs, mbox, SLOT(hide()));
}


QString& PathToIcon(QString &&file_name) noexcept
{
    // Path to the icaon ( assuming that file is in all_pics resources )
    file_name = QDir::homePath() + "/learn_words_app/Learn_Words_App_0_0_1/" + file_name;
    return file_name;
}

void DrawLangLabel(QLabel *label, const QString &path)
{
    QString full_path = QDir::homePath() + "/learn_words_app/Learn_Words_App_0_0_1/" + path;
    QPixmap curr_lang_pixmap(full_path);
    label->setPixmap(curr_lang_pixmap);
    label->setMask(curr_lang_pixmap.mask());
}
