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
    window->resize(Sizes::MAIN_WINDOW_WIDTH / 1.5, Sizes::MAIN_WINDOW_HEIGHT / 1.5);
    window->setStyleSheet(BACKGROUND_COLOR);
    window->setAutoFillBackground(true);
    window->show();
    return a.exec();
}
