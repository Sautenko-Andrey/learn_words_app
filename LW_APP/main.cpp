#include "dialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Dialog window;
    window.setWindowTitle("Learn words app");

    window.show();
    return app.exec();
}
