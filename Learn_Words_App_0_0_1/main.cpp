#include "mainwindow.h"
#include <memory>
#include "common.h"
#include <QApplication>
#include "sizes.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto window = std::make_unique<MainWindow>();
    window->setWindowTitle("Learn Words App");
    window->setFixedSize(Sizes::MAIN_WINDOW_WIDTH, Sizes::MAIN_WINDOW_HEIGHT);
    window->setStyleSheet(BACKGROUND_COLOR);
    window->setAutoFillBackground(true);
    window->show();
    return a.exec();
}
