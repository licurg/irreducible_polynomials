#include "ui/button.h"

Button::Button(const QString& text, const QString& stylesheet, QWidget* parent)
    : QPushButton(text, parent)
{
    this->setStyleSheet(stylesheet);
}