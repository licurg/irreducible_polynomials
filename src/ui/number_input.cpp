#include "ui/number_input.h"

NumberInput::NumberInput(const QString& stylesheet, QWidget* parent)
    : QSpinBox(parent)
{
    this->setStyleSheet(stylesheet);
}