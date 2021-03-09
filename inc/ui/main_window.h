#ifndef IRREDUCIBLE_POLYNOMIALS_MAIN_WINDOW_H
#define IRREDUCIBLE_POLYNOMIALS_MAIN_WINDOW_H

#include <QMainWindow>

#include "ui/number_input.h"
#include "ui/label.h"
#include "ui/button.h"
#include "ui/progress_bar.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() noexcept;

private slots:
    void startButtonHandler();
    void pauseButtonHandler();
    void resumeButtonHandler();
    void stopButtonHandler();

private:
    uint8_t degree;
    uint64_t polynomial_count;
    uint64_t timestamp;

    NumberInput* polynomial_degree_input;

    Label* polynomial_count_value;
    Label* time_spent_value;

    Button* start_button;
    Button* pause_button;
    Button* resume_button;
    Button* stop_button;

    ProgressBar* progress;
};

#endif//IRREDUCIBLE_POLYNOMIALS_MAIN_WINDOW_H
