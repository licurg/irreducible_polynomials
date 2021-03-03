#include "ui/progress_bar.h"

ProgressBar::ProgressBar(const QString& stylesheet, QWidget* parent)
    : QProgressBar(parent)
{
    this->setTextVisible(false);
    this->setStyleSheet(stylesheet);
}