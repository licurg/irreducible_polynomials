//
// Created by Bald on 27.02.2021.
//

#include <QDebug>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
#ifdef DEBUG
    qDebug() << "Main window creation";
#endif
}