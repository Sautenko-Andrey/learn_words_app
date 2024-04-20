#include "mainwindow.h"
#include <memory>
#include <QApplication>
#include "all_sizes.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::unique_ptr<MainWindow> window(new MainWindow);
    window->setWindowTitle("Learn Words App");
    window->resize(Sizes::MAIN_WINDOW_WIDTH / 1.5, Sizes::MAIN_WINDOW_HEIGHT / 1.5);
    window->setStyleSheet("background-color:gray;");
    window->setAutoFillBackground(true);
    window->show();
    return a.exec();
}
