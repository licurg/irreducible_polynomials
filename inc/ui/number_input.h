#ifndef IRREDUCIBLE_POLYNOMIALS_NUMBER_INPUT_H
#define IRREDUCIBLE_POLYNOMIALS_NUMBER_INPUT_H

#include <QSpinBox>

#include "ui/styles.h"

namespace Ui
{
    class NumberInput;
}

class NumberInput : public QSpinBox
{
    Q_OBJECT
public:
    explicit NumberInput(const QString& stylesheet = INPUT_GENERAL_STYLE,
                         QWidget* parent = nullptr);
};

#endif //IRREDUCIBLE_POLYNOMIALS_NUMBER_INPUT_H
