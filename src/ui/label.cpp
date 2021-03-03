#include "ui/label.h"

Label::Label(const QString& text, const QString& stylesheet, QWidget* parent)
    : QLabel(text, parent)
{
    this->setStyleSheet(stylesheet);
}