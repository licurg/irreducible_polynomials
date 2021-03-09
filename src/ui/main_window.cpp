#include <QLabel>
#include <QDebug>

#include "polynomial_generator.h"

#include "ui/styles.h"
#include "ui/wrapper.h"
#include "ui/main_window.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    this->setWindowTitle("Детерминированный линейно-логарифмический "
                         "aлгоритм синтеза НП над GF(3)");
    this->setStyleSheet(MAIN_WINDOW_STYLE);
    this->setMinimumWidth(800);

    Wrapper* main_wrapper = new Wrapper(this, 10);
    setCentralWidget(main_wrapper);

    Wrapper* header_wrapper = new Wrapper(main_wrapper);
    main_wrapper->addElement(header_wrapper);

    Label* input_parameters_label =
            new Label("Входные параметры", LABEL_HEADING_STYLE);
    header_wrapper->addElementAt(input_parameters_label, 0, 0);

    Wrapper* settings_form_wrapper = new Wrapper(header_wrapper);
    header_wrapper->addElementAt(settings_form_wrapper, 1, 0);

    Label* polynomial_degree_label = new Label("Степень полинома:");
    settings_form_wrapper->addElementAt(polynomial_degree_label, 0, 0);

    this->polynomial_degree_input = new NumberInput;
    this->polynomial_degree_input->setMinimum(2);
    settings_form_wrapper->addElementAt(this->polynomial_degree_input, 0, 1);

    Label* results_label =
            new Label("Результаты просчёта", LABEL_HEADING_STYLE);
    header_wrapper->addElementAt(results_label, 0, 1);

    Wrapper* results_form_wrapper = new Wrapper(header_wrapper);
    header_wrapper->addElementAt(results_form_wrapper, 1, 1);

    Label* polynomial_count_label = new Label("Количество полиномов:");
    results_form_wrapper->addElementAt(polynomial_count_label, 0, 0);

    this->polynomial_count_value = new Label;
    results_form_wrapper->addElementAt(this->polynomial_count_value, 0, 1);

    this->time_spent_value = new Label;
    results_form_wrapper->addElementAt(this->time_spent_value, 1, 1);

    Label* time_spent_label = new Label("Затрачено времени:");
    results_form_wrapper->addElementAt(time_spent_label, 1, 0);

    Wrapper* button_wrapper = new Wrapper(main_wrapper);
    main_wrapper->addElement(button_wrapper);

    this->start_button = new Button("Старт");
    button_wrapper->addElementAt(this->start_button, 0, 0);
    connect(this->start_button, &QPushButton::released, this,
            &MainWindow::startButtonHandler);

    this->pause_button = new Button("Стоп");
    this->pause_button->setDisabled(true);
    button_wrapper->addElementAt(this->pause_button, 0, 1);
    connect(this->pause_button, &QPushButton::released, this,
            &MainWindow::pauseButtonHandler);

    this->resume_button = new Button("Продолжить");
    this->resume_button->setDisabled(true);
    button_wrapper->addElementAt(this->resume_button, 1, 0);
    connect(this->resume_button, &QPushButton::released, this,
            &MainWindow::resumeButtonHandler);

    this->stop_button = new Button("Финиш");
    this->stop_button->setDisabled(true);
    button_wrapper->addElementAt(this->stop_button, 1, 1);
    connect(this->stop_button, &QPushButton::released, this,
            &MainWindow::stopButtonHandler);

    this->progress = new ProgressBar;
    main_wrapper->addElement(this->progress);
}
MainWindow::~MainWindow() noexcept
{
    delete this->polynomial_degree_input;

    delete this->polynomial_count_value;
    delete this->time_spent_value;

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
    this->polynomial_degree_input->setDisabled(true);

    this->start_button->setDisabled(true);
    this->pause_button->setDisabled(false);
    this->resume_button->setDisabled(true);
    this->stop_button->setDisabled(false);

    this->polynomial_count = 0;

    PolynomialCounter polynomial_counter(3,
                                         this->polynomial_degree_input->value(),
                                         &this->polynomial_count);
    polynomial_counter.start();

    this->polynomial_count_value->setText(
            QString::number(this->polynomial_count));

    this->polynomial_degree_input->setDisabled(false);

    this->start_button->setDisabled(false);
    this->pause_button->setDisabled(true);
    this->resume_button->setDisabled(true);
    this->stop_button->setDisabled(true);
}
void MainWindow::pauseButtonHandler()
{
#ifdef DEBUG
    qDebug() << "Pause button pressed";
#endif
    this->polynomial_degree_input->setDisabled(true);

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
    this->polynomial_degree_input->setDisabled(true);

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
    this->polynomial_degree_input->setDisabled(false);

    this->start_button->setDisabled(false);
    this->pause_button->setDisabled(true);
    this->resume_button->setDisabled(true);
    this->stop_button->setDisabled(true);

    this->progress->setMaximum(1);
    this->progress->setValue(0);
}
