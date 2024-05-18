#include "mainwindow.h"
#include <memory>
#include "common.h"
#include <QApplication>
#include "sizes.h"
#include <QIcon>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto window = std::make_unique<MainWindow>();
    window->setWindowTitle("Learn Words App");
    window->setFixedSize(static_cast<int>(Sizes::MAIN_WINDOW_WIDTH),
                         static_cast<int>(Sizes::MAIN_WINDOW_HEIGHT));
    window->setStyleSheet(BACKGROUND_COLOR);
    window->setAutoFillBackground(true);
    window->setWindowIcon(QIcon(":/all_pics/icon.jpeg"));
    window->show();
    return a.exec();
}
