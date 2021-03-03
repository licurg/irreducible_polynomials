#ifndef IRREDUCIBLE_POLYNOMIALS_BUTTON_H
#define IRREDUCIBLE_POLYNOMIALS_BUTTON_H

#include <QPushButton>

#include "ui/styles.h"

namespace Ui
{
    class Button;
}

class Button : public QPushButton
{
    Q_OBJECT
public:
    explicit Button(const QString& text,
                    const QString& stylesheet = BUTTON_GENERAL_STYLE,
                    QWidget* parent = nullptr);
};

#endif //IRREDUCIBLE_POLYNOMIALS_BUTTON_H
