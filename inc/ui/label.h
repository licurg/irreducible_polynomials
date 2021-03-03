#ifndef IRREDUCIBLE_POLYNOMIALS_LABEL_H
#define IRREDUCIBLE_POLYNOMIALS_LABEL_H

#include <QLabel>

#include "ui/styles.h"

namespace Ui
{
    class Label;
}

class Label : public QLabel
{
    Q_OBJECT
public:
    explicit Label(const QString& text = "",
                   const QString& stylesheet = LABEL_GENERAL_STYLE,
                   QWidget* parent = nullptr);
};

#endif //IRREDUCIBLE_POLYNOMIALS_LABEL_H
