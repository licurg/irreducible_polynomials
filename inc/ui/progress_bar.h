#ifndef IRREDUCIBLE_POLYNOMIALS_PROGRESS_BAR_H
#define IRREDUCIBLE_POLYNOMIALS_PROGRESS_BAR_H

#include <QProgressBar>

#include "ui/styles.h"

namespace Ui
{
    class ProgressBar;
}

class ProgressBar : public QProgressBar
{
    Q_OBJECT
public:
    explicit ProgressBar(const QString& stylesheet = PROGRESS_BAR_GENERAL_STYLE,
                         QWidget* parent = nullptr);
};

#endif //IRREDUCIBLE_POLYNOMIALS_PROGRESS_BAR_H
