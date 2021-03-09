#include <QApplication>

#include "ui/main_window.h"

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication a(argc, argv);

    MainWindow main_window;
    main_window.show();

    return QApplication::exec();
}
