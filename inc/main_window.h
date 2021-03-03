#ifndef IRREDUCIBLE_POLYNOMIALS_MAIN_WINDOW_H
#define IRREDUCIBLE_POLYNOMIALS_MAIN_WINDOW_H

#include <QPushButton>
#include <QProgressBar>
#include <QMainWindow>

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
    QPushButton* start_button;
    QPushButton* pause_button;
    QPushButton* resume_button;
    QPushButton* stop_button;

    QProgressBar* progress;
};

#endif//IRREDUCIBLE_POLYNOMIALS_MAIN_WINDOW_H
