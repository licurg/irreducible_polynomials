#include <QGridLayout>
#include <QPushButton>

#include "wrapper.h"

Wrapper::Wrapper(QWidget* parent, int margins) : QWidget(parent)
{
    this->grid = new QGridLayout;
    this->grid->setMargin(margins);
    this->setLayout(grid);
}
Wrapper::~Wrapper() noexcept
{
    delete this->grid;
}

void Wrapper::addElement(QWidget *element)
{
    this->grid->addWidget(element);
}
void Wrapper::addElementAt(QWidget* element, int row, int col,
                           Qt::Alignment alignment)
{
    this->grid->addWidget(element, row, col, alignment);
}