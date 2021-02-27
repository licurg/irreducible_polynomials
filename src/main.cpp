//
// Created by Bald on 27.02.2021.
//

#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow main_window;
    main_window.setWindowTitle("Irreducible polynomials");
    main_window.show();
    return QApplication::exec();
}