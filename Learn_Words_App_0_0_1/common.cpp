#include "common.h"
#include <QtSql>
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

const QString BACKGROUND_COLOR = "background-color:#708090;";

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
    // Path to the icon ( assuming that file is in all_pics resources )
    file_name = QDir::homePath() + "/learn_words_app/Learn_Words_App_0_0_1/" + file_name;
    return file_name;
}

void DrawLangLabel(QLabel *label, const QString &path)
{
    if(label){
        QString full_path = QDir::homePath() + "/learn_words_app/Learn_Words_App_0_0_1/" + path;
        QPixmap curr_lang_pixmap(std::move(full_path));
        label->setPixmap(curr_lang_pixmap);
        label->setMask(curr_lang_pixmap.mask());
    }
}

void makeButtonIcon(const QString &img_path, const QString &tool_tip,
                    QAbstractButton *button){

    if(button){
        QIcon icon;
        icon.addPixmap(QPixmap(img_path), QIcon::Active, QIcon::On);
        button->setIcon(icon);
        button->setToolTip(tool_tip);
    }
}


void setTextEditCursor(int &font_size, QTextEdit *leftTextEdit,
               QTextEdit *rightTextEdit, QDialog *dialog,
               bool increase)
{
    if(leftTextEdit && rightTextEdit && dialog){
        // minimum and maximum font size
        int minimum = 5;
        int maximum = 35;

        // logic when user goes out of bounds
        if (font_size < minimum){
            QMessageBox::warning(dialog, "Warning", "You are out of minimal bound.");
            font_size = ++minimum;
            leftTextEdit->setFontPointSize(minimum);
            rightTextEdit->setFontPointSize(minimum);
        }
        else if (font_size > maximum){
            QMessageBox::warning(dialog, "Warning", "You are out of maximum bound.");
            font_size = --maximum;
            leftTextEdit->setFontPointSize(maximum);
            rightTextEdit->setFontPointSize(maximum);
        }

        QTextCursor cursor_left = leftTextEdit->textCursor();
        QTextCursor cursor_right = rightTextEdit->textCursor();
        leftTextEdit->selectAll();
        rightTextEdit->selectAll();

        increase ? ++font_size : --font_size;

        leftTextEdit->setFontPointSize(font_size);
        rightTextEdit->setFontPointSize(font_size);

        leftTextEdit->setTextCursor(cursor_left);
        rightTextEdit->setTextCursor(cursor_right);
    }
}


void setTextEditCursor(int &font_size, QTextEdit *textEdit,
                       QDialog *dialog, bool increase)
{
    if(textEdit && dialog){
        // minimum and maximum font size
        int minimum = 5;
        int maximum = 35;

        // logic when user goes out of bounds
        if (font_size < minimum){
            QMessageBox::warning(dialog, "Warning", "You are out of minimal bound.");
            font_size = ++minimum;
            textEdit->setFontPointSize(minimum);
        }
        else if (font_size > maximum){
            QMessageBox::warning(dialog, "Warning", "You are out of maximum bound.");
            font_size = --maximum;
            textEdit->setFontPointSize(maximum);
        }

        QTextCursor cursor_left = textEdit->textCursor();
        textEdit->selectAll();

        increase ? ++font_size : --font_size;

        textEdit->setFontPointSize(font_size);

        textEdit->setTextCursor(cursor_left);
    }
}
