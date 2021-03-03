#include <QPushButton>
#include <QProgressBar>
#include <QDebug>

#include "wrapper.h"
#include "main_window.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    this->setWindowTitle("Детерминированный линейно-логарифмический "
                         "aлгоритм синтеза НП над GF(3)");

    this->setMinimumWidth(800);

    Wrapper* main_wrapper = new Wrapper(this, 10);
    setCentralWidget(main_wrapper);

    Wrapper* button_wrapper = new Wrapper(main_wrapper);
    main_wrapper->addElement(button_wrapper);

    this->start_button = new QPushButton("Старт");
    button_wrapper->addElementAt(this->start_button, 0, 0);
    connect(this->start_button, &QPushButton::released, this,
            &MainWindow::startButtonHandler);

    this->pause_button = new QPushButton("Стоп");
    this->pause_button->setDisabled(true);
    button_wrapper->addElementAt(this->pause_button, 0, 1);
    connect(this->pause_button, &QPushButton::released, this,
            &MainWindow::pauseButtonHandler);

    this->resume_button = new QPushButton("Продолжить");
    this->resume_button->setDisabled(true);
    button_wrapper->addElementAt(this->resume_button, 1, 0);
    connect(this->resume_button, &QPushButton::released, this,
            &MainWindow::resumeButtonHandler);

    this->stop_button = new QPushButton("Финиш");
    this->stop_button->setDisabled(true);
    button_wrapper->addElementAt(this->stop_button, 1, 1);
    connect(this->stop_button, &QPushButton::released, this,
            &MainWindow::stopButtonHandler);

    this->progress = new QProgressBar;
    this->progress->setTextVisible(false);
    main_wrapper->addElement(this->progress);
}
MainWindow::~MainWindow() noexcept
{
    delete this->start_button;
    delete this->pause_button;
    delete this->resume_button;
    delete this->stop_button;
    delete this->progress;
}

void MainWindow::startButtonHandler()
{
#ifdef DEBUG
    qDebug() << "Start button pressed";
#endif
    this->start_button->setDisabled(true);
    this->pause_button->setDisabled(false);
    this->resume_button->setDisabled(true);
    this->stop_button->setDisabled(false);
}
void MainWindow::pauseButtonHandler()
{
#ifdef DEBUG
    qDebug() << "Pause button pressed";
#endif
    this->start_button->setDisabled(true);
    this->pause_button->setDisabled(true);
    this->resume_button->setDisabled(false);
    this->stop_button->setDisabled(false);
}
void MainWindow::resumeButtonHandler()
{
#ifdef DEBUG
    qDebug() << "Resume button pressed";
#endif
    this->start_button->setDisabled(true);
    this->pause_button->setDisabled(false);
    this->resume_button->setDisabled(true);
    this->stop_button->setDisabled(false);
}
void MainWindow::stopButtonHandler()
{
#ifdef DEBUG
    qDebug() << "Stop button pressed";
#endif
    this->start_button->setDisabled(false);
    this->pause_button->setDisabled(true);
    this->resume_button->setDisabled(true);
    this->stop_button->setDisabled(true);

    this->progress->setMaximum(1);
    this->progress->setValue(0);
}
